#ifndef FIELD_WORKS_H_INCLUDED
#define FIELD_WORKS_H_INCLUDED



/*******************Declarations*****************************/


typedef struct field {
    uint8_t field[40][40];
    uint32_t last_changed_x, last_changed_y;
    uint32_t max_x, max_y;
} field_of_arrows;

/*******************Function_Prototypes**********************/
void init_field(field_of_arrows* field);
void update_field(field_of_arrows* field);
#endif // FIELD_WORKS_H_INCLUDED
