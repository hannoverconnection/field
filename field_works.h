#ifndef FIELD_WORKS_H_INCLUDED
#define FIELD_WORKS_H_INCLUDED



/*******************Declarations*****************************/


typedef struct field {
    uint8_t *dyn_field;
    uint32_t last_changed_x, last_changed_y;
    uint32_t max_x, max_y;
} field_of_arrows;


/*******************Function_Prototypes**********************/

void update_field(field_of_arrows* field);
void init_field(field_of_arrows* str_field, SDL_Surface* monitor);
#endif // FIELD_WORKS_H_INCLUDED
