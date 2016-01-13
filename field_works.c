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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "field_works.h"


void init_field(field_of_arrows* str_field)
{
    // Create a pointer to the field inside the struct
    // and use this one in the following loop to init the
    // field with random values.
    uint32_t index;
    uint8_t* ptr_x;
    ptr_x = (uint8_t *) str_field->field;  //ohne das Typecast bekomme ich eine Warnung.

    for(index = 0; index < sizeof(str_field->field); index++)
    {
        *ptr_x = rand() % 4;
        ptr_x++;

    }

    str_field->max_x = sizeof(str_field->field[0]);
    str_field->max_y = sizeof(str_field->field) / str_field->max_x;

    str_field->last_changed_x = (rand() % str_field->max_x) + 1;
    str_field->last_changed_y = (rand() % str_field->max_y) + 1;
}

void update_field(field_of_arrows* field)
{

    uint8_t random_dir;
    random_dir = rand() % 4;
    //Kev, Hilfe!!!
    field->field[0][0] = random_dir;

}

