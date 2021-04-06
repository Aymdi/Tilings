#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "struct_tile.h"

//empty_tile
static struct tile empty_t = {{NULL, NULL, NULL, NULL}};

//function that returns a pointer to an empty_tile
const struct tile* empty_tile(){

	return(&empty_t);
};

// A predicate telling if the tile is empty (1 if empty, 0 if full)
int tile_is_empty(const struct tile* t){
	for (int i=0; i<MAX_DIRECTION; i++){
		if ( (t->color_direction[i]) != NULL )
			return 0; 
	}
	return 1;
}
	
// A comparator between tiles (1 if equals,0 if not)
int tile_equals(const struct tile* t1, const struct tile* t2){

	for (int i=0; i<MAX_DIRECTION; i++){
		if ( strcmp(color_name(t1->color_direction[i]),color_name(t2->color_direction[i])))
			return 0;
	}
	return 1;
}

		
// Accessors to the color of the edges
struct color* tile_edge(const struct tile* t, enum direction d){
	if (d==4 || d==-1)
		return NULL;
	return (t->color_direction[d]);

}

//List of different tiles
struct tile deck_tile[MAX_DECK_SIZE];

// A function that fills a deck with tiles  
void deck_init(struct deck* d){

	d->size = 5;//Fill the deck with 4 types of tiles

    //Tile 1
	deck_tile[0] = (struct tile) {{color_from_name("rouge"),
					               color_from_name("rouge"),
					               color_from_name("rouge"),
					               color_from_name("rouge")}};
	d->cards[0] = (struct deck_pair) {&deck_tile[0],16};

	//Tile 2
	deck_tile[1] = (struct tile) {{color_from_name("rouge"),
					               color_from_name("noir"),
					               color_from_name("noir"),
					               color_from_name("noir")}};
	d->cards[1] = (struct deck_pair) {&deck_tile[1],16};

	//Tile 3
	deck_tile[2] = (struct tile) {{color_from_name("noir"),
					               color_from_name("rouge"),
					               color_from_name("noir"),
					               color_from_name("noir")}};
    d->cards[2] = (struct deck_pair) {&deck_tile[2],8};

	//Tile 4
	deck_tile[3] = (struct tile) {{color_from_name("noir"),
					               color_from_name("noir"),
					               color_from_name("rouge"),
					               color_from_name("noir")}};
	d->cards[3] = (struct deck_pair) {&deck_tile[3],8};

	//Tile 5
	deck_tile[4] = (struct tile) {{color_from_name("noir"),
					               color_from_name("noir"),
					               color_from_name("noir"),
					               color_from_name("rouge")}};
	d->cards[4] = (struct deck_pair) {&deck_tile[4],8};

}
	