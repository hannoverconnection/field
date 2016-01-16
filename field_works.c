/********************************************************************************************
*
*   Contains all functions that are necessary for the field work
*
*   Function:
*       init_field
*       init_last_changed_position
*       update_field
*
*********************************************************************************************/
#include <SDL/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "field_works.h"


void init_field(field_of_arrows* str_field, SDL_Surface* monitor)
{
    // Create a pointer to the field inside the struct
    // and use this one in the following loop to init the
    // field with random values.
    uint32_t index;
    uint8_t* ptr_x;

    // find out how many arrows are possible
    str_field->max_x = monitor->w / 16;
    str_field->max_y = monitor->h /16;

    str_field->dyn_field = (uint8_t *) malloc(sizeof(uint8_t) * str_field->max_x * str_field->max_y);

    ptr_x = str_field->dyn_field;

    for(index = 0; index < (str_field->max_x * str_field->max_y); index++)
    {
        *ptr_x = rand() % 4;
        ptr_x++;

    }

    str_field->last_changed_x = (rand() % str_field->max_x) + 1;
    str_field->last_changed_y = (rand() % str_field->max_y) + 1;
}


void update_field(field_of_arrows* field)
{

    uint8_t random_dir;
    static uint32_t index = 0;

    if(index >= (field->max_x*field->max_y))
    {
        index = 0;
    }

    random_dir = rand() % 4;
    //Kev, Hilfe!!!
    *((field->dyn_field) + index) = random_dir;
    field->last_changed_x = (index % field->max_x)+1;
    field->last_changed_y = (index / field->max_x) +1;
    index++;
}

