
#ifndef OBSERVER_H_INCLUDED
#define OBSERVER_H_INCLUDED

/*******************Configuration*********************/
#define CAPACITY_OF_REMEMBERING 50


/*******************FUNCTION_PROTOTYPS****************/
void clear_screen(void);
void munch_the_field(SDL_Surface* screen, field_of_arrows* field);
void plot_history(SDL_Surface* screen, field_of_arrows* field);
#endif // OBSERVER2_H_INCLUDED
