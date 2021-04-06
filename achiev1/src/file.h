#ifndef _FILE_H_
#define _FILE_H_

#include "tile.h"

/*
Une telle file devrait pouvoir accepter d'insérer des éléments à l'intérieur (push),
de récupérer un pointeur vers l'élément en tête de pile (top) ainsi que de retirer
des éléments si la file n'est pas vide (pop), tout cela en respectant l'ordre d'insertion.
*/

#define MAX_TILE 200 //The number of possible tiles in a deck, and also in a player's hand, is 200.

//Struct for file
struct file{
    int head; //head index of the file in tiles
    int tail; //tail index of the file in tiles
    const struct tile *tiles[MAX_TILE+1]; //tiles[0] is empty: used to know if the file is empty

};

//Initialization of the file: an empty file
void file_init(struct file *f);

//Verify if the file is empty: returns 1 if so, 0 if not
int file_is_empty(struct file *f);

//return the size of the file
int file_size(struct file *f);

//Insert an element (tile) in the file
void file_push(struct file *f, const struct tile *t);

//Return a pointer to the element at the top of the file
const struct tile* file_top(struct file *f);

//Remove an element (tile) in the file
void file_pop(struct file *f);



#endif //_FILE_H