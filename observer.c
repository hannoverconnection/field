/********************************************************************************************
*
*   Contains all functions that are necessary to observe the evolution of the field
*
*   Function:
*       clear_screen()
*       munch_the_field()
*
*********************************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "field_works.h"
#include "observer.h"


void clear_screen(void)
{
   system("clear");
}


void munch_the_field(SDL_Surface* screen, field_of_arrows* field)
{

    uint32_t x_index, y_index;
    uint8_t dir = 0;
    // Setting the background screen to a white color
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));

    SDL_Surface* bmp_right = SDL_LoadBMP("arrow_right.bmp");
    if (!bmp_right){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    SDL_Surface* bmp_left = SDL_LoadBMP("arrow_left.bmp");
    if (!bmp_left){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    SDL_Surface* bmp_up = SDL_LoadBMP("arrow_up.bmp");
    if (!bmp_up){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    SDL_Surface* bmp_down = SDL_LoadBMP("arrow_down.bmp");
    if (!bmp_down){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }

    SDL_Rect dstrect;
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = bmp_right->w;
    dstrect.h = bmp_right->h;

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = bmp_right->w;
    src.h = bmp_right->h;
    for( y_index = 0; y_index < field->max_y; y_index++){
        for( x_index = 0; x_index < field->max_x; x_index++){
            //printf( " %d  ", *field);


            dstrect.x = x_index * 16;
            dstrect.y = y_index * 16;
            // draw bitmap
            dir = *(field->dyn_field + y_index *field->max_x + x_index);

            switch(dir)
                {
                case 0:
                    SDL_BlitSurface(bmp_up, &src, screen, &dstrect);
                    break;
                case 1:
                    SDL_BlitSurface(bmp_right, &src, screen, &dstrect);
                    break;
                case 2:
                    SDL_BlitSurface(bmp_down, &src, screen, &dstrect);
                    break;
                case 3:
                    SDL_BlitSurface(bmp_left, &src, screen, &dstrect);
                    break;
                default:
                    printf("Unexpected value found\n");
                }

            }

    }

    SDL_FreeSurface(bmp_right);
    SDL_FreeSurface(bmp_left);
    SDL_FreeSurface(bmp_up);
    SDL_FreeSurface(bmp_down);

}


void plot_history(SDL_Surface* screen, field_of_arrows* field)
{

    static uint8_t first_time = 1;
    int index = 0;
    // Define a array which saves the history of the changes.
    // The array shall consists of struct which is containing
    // the lastest x and y position.
    // Description of the array

    // history[0] = newest change value
    // history[1] = one step older
    // ....
    // history[k] = last remembered change.
    struct pos
    {
        uint32_t x;
        uint32_t y;
    };
    // Define the array as static so that the values don't get lost
    // after the function call. The Makro CAPACITY_OF_REMEMBERING is
    // defining how many values will be considered.
    static struct pos history[CAPACITY_OF_REMEMBERING];

    // Initroutine which only initialize once the array. This is when the
    // function is called for the first time.
    if(first_time == 1)
    {
        for(index = 0; index < (sizeof(history)/sizeof(history[0])); index++)
        {
            history[index].x = field->last_changed_x;
            history[index].y = field->last_changed_y;
        }
        first_time=0;
    }

    // Except for the init routine above this part of the code will be called every
    // functioncall.
    // When field is updated a new arrow had been rotated. The memory (variable history)
    // will save this new turned arrow at its first element (history[0]). But before this
    // can be done all the history values have to be moved by one position. This function
    // need to start with the second oldest value and store this in the last element. If
    // part would be called the other way arround it would overwrite the values with need
    // to be moved next.
    // After the for loop the newest changed arrow is saved in the first position.
    for(index = (sizeof(history)/sizeof(history[0]) -1); index > 0; index--)
    {
        history[index] = history[index -1];
    }
    history[0].x = field->last_changed_x;
    history[0].y = field->last_changed_y;

  // Now comes the part history shall be printed to the screen. At first all surfaces need
  // to be loaded. The following part loads the four different arrows that can be printed.
  SDL_Surface* bmp_right = SDL_LoadBMP("arrow_right.bmp");
    if (!bmp_right){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    SDL_Surface* bmp_left = SDL_LoadBMP("arrow_left.bmp");
    if (!bmp_left){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    SDL_Surface* bmp_up = SDL_LoadBMP("arrow_up.bmp");
    if (!bmp_up){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    SDL_Surface* bmp_down = SDL_LoadBMP("arrow_down.bmp");
    if (!bmp_down){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }

    // The arrows shall be printed but not with a white background as before. Instead they
    // shall be printed on a colored background. To do that the white part of the arrow picture
    // need to be made transperent. To do this the colorkey option is used. This option replaced
    // the defined color (255,255,255 = white) and make all this pixels transperat.
    uint32_t colorkey = SDL_MapRGB(bmp_right->format,255,255,255);
    SDL_SetColorKey(bmp_right, SDL_SRCCOLORKEY, colorkey);
    SDL_SetColorKey(bmp_left, SDL_SRCCOLORKEY, colorkey);
    SDL_SetColorKey(bmp_up, SDL_SRCCOLORKEY, colorkey);
    SDL_SetColorKey(bmp_down, SDL_SRCCOLORKEY, colorkey);

    // A surface is created which will be used as the background color. It has the same size as
    // the picture of the arrows. (16x16 pixel). The 24 inside the argument list is defining the
    // colordepth. The line afterwards is filling the surface in deep bloody red (255,0,0).
    SDL_Surface* background = SDL_CreateRGBSurface(0,bmp_down->w,bmp_down->h,24,0,0,0,0);
    SDL_FillRect(background, 0, SDL_MapRGB(background->format, 255, 0, 0));


    // The following part is defining two sections. These sections define a area of pixels. The
    // size of the pixels is defined inside the variables <xxx>.w <xxx>.h. This values are filled
    // with the size of the arrow picture. The other variables (x,y) define the first pixel of the
    // area that shall be copied. Once for target and once for source.
    SDL_Rect dstrect;
    dstrect.w = bmp_right->w;
    dstrect.h = bmp_right->h;

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = bmp_right->w;
    src.h = bmp_right->h;

    // Now comes the tricky part to copy all the history to the surface. The for loop
    // will start to print the last value to the surface and then continue with the newer
    // positions. This means that if a postion it stored two times inside the history than
    // the newer change will overright the older one. New changes shall be printed more bright
    // red. The background will fade out the older the history value it.
    for(index = ((sizeof(history)/sizeof(history[0]))-1); index >=0; index--)
    {
        // First of all the position is calculated where the history value has to placed in the
        // surface
        dstrect.x = (history[index].x -1) * background->w;
        dstrect.y = (history[index].y -1) * background->h;

        // Next step is to calculated the color in which this field shall shine. The red value
        // is always at its maximum value and blue and green will be calculated based on how old
        // the memory value is.
        uint8_t green, blue;
        green = (uint8_t)((float)(index * 255 / CAPACITY_OF_REMEMBERING ));
        blue = green;

        // Now a the backgoround is printed with the appropiate color
        SDL_FillRect(background, 0, SDL_MapRGB(background->format, 255, green, blue));
        SDL_BlitSurface(background, &src, screen, &dstrect);

        // After the background the arrow is printed on the background. But to do is at first
        // it has to be determined which arrow need to be printed. This is done by the first part of
        // the following code. The variable dir stores a value to which direction the arrow is pointing
        // The switch statement afterwards selects the appropiate picture to print it.
        uint8_t dir = *(field->dyn_field + (history[index].y -1)* field->max_x + history[index].x -1);
        switch(dir)
            {
            case 0:
                SDL_BlitSurface(bmp_up, &src, screen, &dstrect);
                break;
            case 1:
                SDL_BlitSurface(bmp_right, &src, screen, &dstrect);
                break;
            case 2:
                SDL_BlitSurface(bmp_down, &src, screen, &dstrect);
                break;
            case 3:
                SDL_BlitSurface(bmp_left, &src, screen, &dstrect);
                break;
            default:
                printf("Unexpected value found\n");
            }

    }


    SDL_FreeSurface(bmp_right);
    SDL_FreeSurface(bmp_left);
    SDL_FreeSurface(bmp_up);
    SDL_FreeSurface(bmp_down);


}
