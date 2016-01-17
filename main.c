#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <SDL/SDL.h>


#include "field_works.h"
#include "observer.h"

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
    #include <stdbool.h>
#endif


/***********************************************************/
/**             Configuration of the software             **/

#define FULLSCREEN




int main( int argc, char** argv )
{

    /***************** GLOBAL VARIABLES **********************/
        uint32_t iterations = 0;
        field_of_arrows field;


    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // get the max monitor resolution


    // create a new window
    #ifdef FULLSCREEN
    const SDL_VideoInfo* monitor_settings = SDL_GetVideoInfo();
    SDL_Surface* screen = SDL_SetVideoMode(monitor_settings->current_w, monitor_settings->current_h, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    #else
        SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    #endif // FULLSCREEN

    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    init_field(&field, screen);

    // load an image
    SDL_Surface* bmp_right = SDL_LoadBMP("arrow_right.bmp");
    if (!bmp_right)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }


    // program main loop
    bool done = false;
    while (!done)
    {


        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing


        // Clear the console window and write the actual iteration step
        // to the consol window. Can disabled in a later version.
        clear_screen();
        iterations++;
        printf("Iterationcounter: %d\n", iterations);

        // Update the field of arrows with every new execution of the main
        // loop. The command update field will find out which arrow next need
        // to be turned.
        update_field(&field);

        // Observer starts to print the field. For this purpose will it look
        // at struct field to know what need to be drawn. The drawing
        // will be included in the first argument the screen.
        munch_the_field(screen, &field);
        plot_history(screen, &field);

        // finally, update the screen
        SDL_UpdateRect(screen, 0, 0, 0, 0);

        // To make it enjoyable 100 ms as a delay between each updated looks
        // like a good solution
        SDL_Delay(10);
    } // end main loop
    // free the dynamic reserved memory that is no more needed.
    free(field.dyn_field);


    printf("Exited cleanly\n");
    return 0;
}
