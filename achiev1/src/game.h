#ifndef _GAME_H_
#define _GAME_H_

#include "file.h"

///////////////////////////////RANDOM///////////////////////////////

//Allows at each execution to return a random number
int my_rand (void);


///////////////////////////////PLAYERS///////////////////////////////

#define MAX_PLAYERS 20
#define MIN_PLAYERS 2


//Struct for player
struct player{
    int active; //1 if so, 0 if not
    int score;
    int hand_size;
    struct file hand;
    int central_tiles_owns;  //Number of central tiles that the player owns
    struct coord *coord_central_tiles[MAX_TILE];

};

//Struct for players
struct players{
    int players_count;
    int players_active; // Number of active players
    struct player list_players[MAX_PLAYERS];
};

//Returns the active player structure: on each call the function returns the next player.
struct player *get_next_player(struct players *p,int turn);

//ALL IN ONE: init players
void players_init(int size, struct players *p);


///////////////////////////////BOARD///////////////////////////////

#define MAX_BOARD_SIZE 50 //The maximum size of the tray/board is 50x50.

//Struct for board
struct board{

    unsigned int dim; // The size of the board is dim*dim
    const struct tile *tile_board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    
};


//Struct for tile coordinates
struct coord{

    unsigned int x; //Line Ind
    unsigned int y; //Column Ind
};

//Initialization of the board : full of empty tiles
void board_init(struct board *b, int size);

// A predicate telling if the board is empty (1->empty 0->if not)
int board_is_empty(struct board *b);

//Show the board
void show_board(struct board *b);



///////////////////////////////TILES DISTRIBUTION///////////////////////////////

//Return the number of tiles in a deck
int tiles_count(struct deck *d);

//The number of tiles that each player has in hand after the distribution
//t_c : tiles_count
//p_c : players_count
int hand_size(int t_c, int p_c);


//Distribution of tiles from deck to a list (list_tiles)
void split_tiles_tolist(struct deck *d, const struct tile *list[]);


//Function allows to mix the tiles in the list
//tiles_count : number of tiles in the list 
void mix_tiles(int tiles_count, const struct tile *list[]);


//Distribution of tiles to players
void split_tiles(int tiles_count, const struct tile *list[], struct players *p);

//ALL IN ONE: mix tiles and split it to players
void split_deck(struct deck *d, struct players *p);

//A predicate indicating whether we can place a tile in the coordinates (x,y) respecting both rules
int can_place_tile_rules(const struct tile *t, struct board *b, struct coord c);


//A predicate indicating whether we can place a tile in the coordinates (x,y) (1 if so, 0 if not)
int can_place_tile(struct board *b, struct coord c);

//Function that places a tile in the board according to coordinates(x,y) 
void place_tile(const struct tile *t, struct board *b, struct coord c);

//Fill the list of authorized coordinates and returns the size of the list
int fill_authorized_places(const struct tile *t,struct board *b,struct coord list[],int turn);

//ALL IN ONE: Selects randomly a coordinate from the list after filling the list of coordinates ;)
struct coord select_position(const struct tile *t,struct board *b, struct coord list[],int turn);


//Displays results and the winner
void display_results(struct players *p);

#endif //_GAME_H_