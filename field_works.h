#ifndef FIELD_WORKS_H_INCLUDED
#define FIELD_WORKS_H_INCLUDED



/*******************Declarations*****************************/

struct arrow_position
{
    int x;
    int y;
};

typedef struct field {
    uint8_t field[40][40];
    uint32_t last_changed_x, last_changed_y;
    uint32_t max_x, max_y;
} field_of_arrows;

/*******************Function_Prototypes**********************/
void init_field(uint8_t *field , int number_of_elements);
void init_last_changed_position(uint8_t *field , int number_of_elements, int elements_of_a_row, struct arrow_position* point);
void update_field( uint8_t *field , int number_of_elements, int elements_of_a_row, struct arrow_position* last_position);

void init_field_v2(field_of_arrows field);
void update_field_v2(field_of_arrows field);
#endif // FIELD_WORKS_H_INCLUDED
