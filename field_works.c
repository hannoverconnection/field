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
#include <time.h>

#include "field_works.h"

void init_field(uint8_t *field , int number_of_elements)
{
    int index;
    for(index = 0; index < number_of_elements; index++)
    {
        int time_point;
        time_point = rand(NULL);
        *field = rand(time(NULL)) % 4;
        field++;
    }
}


void init_last_changed_position(uint8_t *field , int number_of_elements, int elements_of_a_row, struct arrow_position* point )
{
    // The  field has the dimension of [elements_of_row][number_of_elements / elements_of_a_row]

    point->x = rand(time(NULL)) % elements_of_a_row;
    point->y = rand(time(NULL)) % (number_of_elements /elements_of_a_row);
}



void update_field( uint8_t *field , int number_of_elements, int elements_of_a_row, struct arrow_position* last_position)
{

    int x_max = elements_of_a_row + 1;
    int y_max = (number_of_elements / elements_of_a_row) + 1;

    int x_new;
    int y_new;

    int x_old = last_position->x;
    int y_old = last_position->y;
    int8_t dir_old = *(field + ((elements_of_a_row * last_position->y) + last_position->x));
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

    // Determin the direction of the new arrow
    if(((elements_of_a_row * (y_new-1)) + (x_new-1)) < 0 || ((elements_of_a_row * (y_new-1)) + (x_new-1)) > number_of_elements )
    {
        printf("Algorithm has gone crazy. Run!");
        getchar();
    }
    else{
        dir_new_field = *(field + ((elements_of_a_row * (y_new-1)) + (x_new-1)));
    }

    //TODO: Algorithm the change the field
    // Die Zeile darunter ist nur zum Testen ob das mit der Parameterübergabe klappt.
    uint8_t rotation_dir;
    switch(rand(time(NULL)) % 2)
    {
        case 0:
            rotation_dir = 1;
            break;
        case 1:
            rotation_dir = -1;
            break;
        default:
            printf("Going to another dimesion. Run!");
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

    *(field + ((elements_of_a_row * (y_new - 1))) + (x_new - 1)) = rand(time(NULL)) % 4;

    // Save the new arrow position
    last_position->x = x_new - 1;
    last_position->y = y_new - 1;
    // Just a test


}


