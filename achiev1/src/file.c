#include <stdlib.h>
#include <stdio.h>

#include "file.h"


//Initialization of the file: an empty file
void file_init(struct file *f){
    f->head = 0;
    f->tail = 0;
}

//Verify if the file is empty: returns 1 if so, 0 if not
int file_is_empty(struct file *f){
    if (f->head == 0){
        return 1;
    }
    return 0;
}

//return the size of the file
int file_size(struct file *f){
    if (file_is_empty(f))
        return 0;
    if (f->head <= f->tail)
        return ((f->tail) - (f->head) + 1);
    else{
        return (MAX_TILE - ((f->head)-(f->tail)-1));
    }
}

//Insert an element (tile) in the file
void file_push(struct file *f, const struct tile *t){
    if ( file_size(f) == MAX_TILE ){
        printf("Cannot insert an element in the file: FULL\n");
    }
    else{
        if (file_is_empty(f))
            f->head = 1;
        if (f->tail == MAX_TILE)
            f->tail = 1;
        else{
            f->tail++;
        }
        f->tiles[f->tail] = t; 
    }
}

//Return a pointer to the element at the top of the file
const struct tile* file_top(struct file *f){
    if (file_is_empty(f))
        return NULL;
    return (f->tiles[f->head]);
}

//Remove an element (tile) in the file
void file_pop(struct file *f){
    if (file_is_empty(f))
        printf("Cannot remove an element from the file: EMPTY\n");
    else{
        if (f->head == f->tail){
            f->head = 0;
            f->tail = 0;
        }
        else{
            if (f->head == MAX_TILE){
                f->head = 1;
            }
            else{
                f->head++;
            }
        }
    }
}