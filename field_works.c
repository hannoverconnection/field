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

    uint32_t x_max = field->max_x;
    uint32_t y_max = field->max_y;

    uint32_t x_new = 0;
    uint32_t y_new = 0;

    uint32_t x_old = field->last_changed_x;
    uint32_t y_old = field->last_changed_y;
    int8_t dir_old = field->field[y_old-1][x_old-1];
    int8_t dir_new_field;

    switch(dir_old)
    {
    case 0:
        y_new = y_old - 1;
        x_new = x_old;
        break;
   case 1:
        y_new = y_old;
        x_new = x_old +1;
        break;
    case 2:
        y_new = y_old +1;
        x_new = x_old;
        break;
    case 3:
        y_new = y_old;
        x_new = x_old -1;
        break;
    }

    if(x_new < 1 || x_new > x_max)
    {
        //printf("X_Range ERROR. new_x = %d\n", x_new);
        x_new = x_old;
        y_new = y_old;
        //getchar();
    }

    if(y_new < 1 || y_new > y_max)
    {
        //printf("Y_Range ERROR. new_y = %d\n", y_new);
        x_new = x_old;
        y_new = y_old;
        //getchar();
    }



    //TODO: Algorithm the change the field
    // Die Zeile darunter ist nur zum Testen ob das mit der Parameterübergabe klappt.
    uint8_t rotation_dir;
    switch(rand() % 2)
    {
        case 0:
            rotation_dir = 1;
            break;
        case 1:
            rotation_dir = -1;
            break;
        default:
            printf("Going to another dimesion. Run!");
            getchar();
    }

    // Check for overruns
    if(dir_new_field + rotation_dir > 3)
    {
        dir_new_field = 0;
    }
    if(dir_new_field + rotation_dir < 0)
    {
        dir_new_field = 3;
    }

    // Save the new arrow position
    field->last_changed_x = x_new;
    field->last_changed_y = y_new;

    // Rotate the new arrow
    field->field[y_new -1][x_new -1] = rand() % 4;
}

