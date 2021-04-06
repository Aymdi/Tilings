#ifndef _PATTERN_H_
#define _PATTERN_H_

#include "game.h"

#define MAX_PATTERN 20
#define MAX_PATTERN_SIZE 2


//Struct for pattern
struct pattern{
    int size;                      //Pattern size (0,1,2)
    int score;                     //Assigned score
    const struct tile *pattern_tiles[5][5]; //Matrix of pointer to tiles that define the pattern
};

//Struct for patterns
struct patterns{
    int number_patterns;          //Number of differents patterns defined in the game
    struct pattern list_patterns[MAX_PATTERN];//list of patterns
};

//Fill the pattern table with empty tiles
void patterns_nil(struct patterns *pat);


//pattern initialization and filling the central tiles
void patterns_init(struct patterns *p);


//Check if the tile is a central tile of a pattern (1 if so, 0 if not)
int is_central_tile(const struct tile *t,struct patterns *pats);

//a function that fills the list of coordinates of central patterns and returns the number of patterns in the board
int num_pattern_board(struct board *b,struct patterns *pats );

//upgrade the information of both player and his tile when it's central.
void update_tile_owner(struct player *p, struct coord c,int size);

//Verify if the central tile complete its pattern and display assigned scores
//t: pointer to the central tile
//c: coordinates of the central tile
int is_pattern(const struct tile *t,struct coord c, struct board *b, struct pattern *pat);



int coord_equal(struct coord c1, struct coord c2);

//Return the index of the owner of a central tile
int index_owner(struct coord c, struct players *p);

//function that assigns points according to the patterns found in the game
void attribute_score_pattern(struct board *b, struct players *p, struct patterns *pats);




#endif //_PATTERN_H_