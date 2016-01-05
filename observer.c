/********************************************************************************************
*
*   Contains all functions that are necessary to observe the evolution of the field
*
*   Function:
*       print_field()
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

    int index;
    int jdex;
    uint8_t dir = 0;


    SDL_Surface* bmp_right = SDL_LoadBMP("arrow_right.bmp");
    if (!bmp_right){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Surface* bmp_left = SDL_LoadBMP("arrow_left.bmp");
    if (!bmp_left){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Surface* bmp_up = SDL_LoadBMP("arrow_up.bmp");
    if (!bmp_up){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Surface* bmp_down = SDL_LoadBMP("arrow_down.bmp");
    if (!bmp_down){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
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
    for( index = 0; index < field->max_y; index++){
        for( jdex = 0; jdex < field->max_x; jdex++){
            //printf( " %d  ", *field);


            dstrect.x = jdex * 16;
            dstrect.y = index *16;
            // draw bitmap
            dir = field->field[jdex][index];

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
                    return 1;
                }

            }

    }

    SDL_FreeSurface(bmp_right);
    SDL_FreeSurface(bmp_left);
    SDL_FreeSurface(bmp_up);
    SDL_FreeSurface(bmp_down);

}
