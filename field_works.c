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

    int x_max = elements_of_a_row;
    int y_max = (number_of_elements / elements_of_a_row);

    int x_new = 1;
    int y_new = 1;

    int x_old = last_position->x +1; //because of fucking c is having a element 0.
    int y_old = last_position->y +1; //because of fucking c is having a element 0.
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

    *(field + ((elements_of_a_row * (y_new - 1))) + (x_new - 1)) = rand(time(NULL)) % 4;

    // Save the new arrow position
    last_position->x = x_new - 1;
    last_position->y = y_new - 1;
    // Just a test


}

void init_field_v2(field_of_arrows str_field)
{
    // Create a pointer to the field inside the struct
    // and use this one in the following loop to init the
    // field with random values.
    uint32_t index;
    uint8_t* ptr_x = str_field.field;
    *ptr_x = 1;

    for(index = 0; index < sizeof(str_field.field); index++)
    {
        *ptr_x = rand(time(NULL)) % 4;
        ptr_x++;
    }

    str_field.max_x = sizeof(str_field.field[0]);
    str_field.max_y = sizeof(str_field.field) / str_field.max_x;

    str_field.last_changed_x = (rand(time(NULL)) % str_field.max_x) + 1;
    str_field.last_changed_y = (rand(time(NULL)) % str_field.max_y) + 1;
}

void update_field_v2(field_of_arrows field)
{

    int x_max = field.max_x;
    int y_max = field.max_y;

    int x_new = 0;
    int y_new = 0;

    int x_old = field.last_changed_x;
    int y_old = field.last_changed_y;
    int8_t dir_old = field.field[x_old-1][y_old-1];
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
    field.last_changed_x = x_new;
    field.last_changed_y = y_new;
    // Just a test

   field.field[x_new -1][y_new -1] = rand(time(NULL)) % 4;
}

