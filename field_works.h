#ifndef FIELD_WORKS_H_INCLUDED
#define FIELD_WORKS_H_INCLUDED



/*******************Declarations*****************************/

struct arrow_position
{
    int x;
    int y;
};

/*******************Function_Prototypes**********************/
void init_field(uint8_t *field , int number_of_elements);
void init_last_changed_position(uint8_t *field , int number_of_elements, int elements_of_a_row, struct arrow_position* point);
void update_field( uint8_t *field , int number_of_elements, int elements_of_a_row, struct arrow_position* last_position);

#endif // FIELD_WORKS_H_INCLUDED
