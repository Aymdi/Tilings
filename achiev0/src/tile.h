#ifndef _TILE_H_
#define _TILE_H_

#include "color.h"

enum direction { NORTH, SOUTH, EAST, WEST,
  MAX_DIRECTION, ERROR_DIRECTION = -1 };

struct tile; // Anonymous struct for tiles

#define MAX_DECK_SIZE 100

struct deck_pair {
  const struct tile* t; // a pointer to a tile
  unsigned int n;       // a number of occurrences of this tile
};

struct deck {
  struct deck_pair cards[MAX_DECK_SIZE]; // an array of struct deck_pair
  unsigned int size;                     // the number of struct deck_pair in `cards`
};

// A tile that is empty
const struct tile* empty_tile();

// A predicate telling if the tile is empty
int tile_is_empty(const struct tile* t);

// A comparator between tiles
int tile_equals(const struct tile* t1, const struct tile* t2);

// Accessors to the color of the edges
struct color* tile_edge(const struct tile* t, enum direction d);

// A function that fills a deck with tiles
// The contents of the deck `d` after the call must always be the same.
void deck_init(struct deck* d);

#endif // _TILE_H_