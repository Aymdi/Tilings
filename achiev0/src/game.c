#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"


///////////////////////////////RANDOM///////////////////////////////

//Allows at each execution to return a random number
int my_rand (void){
    static int first = 0;
    if (first == 0){
        srand (time (NULL));
        first = 1;
    }
    return (rand ());

}


 ///////////////////////////////PLAYER///////////////////////////////

//Returns the active player structure: on each call the function returns the next player.(NULL if no player is active)
struct player *get_next_player(struct players *p,int turn){
    
    int index = (turn-1) % p->players_count;
    return (&(p->list_players[index]));
}



///////////////////////////////BOARD///////////////////////////////

//Initialization of the board : full of empty tiles
void board_init(struct board *b, int size){
    b->dim = size;
    for (int i=0; i<MAX_BOARD_SIZE; i++){
        for (int j=0; j<MAX_BOARD_SIZE; j++){
            b->tile_board[i][j] = empty_tile();
        }
    }
}

// A predicate telling if the board is empty (1->empty 0->if not)
int board_is_empty(struct board *b){
    for (int i=0; i<MAX_BOARD_SIZE; i++){
        for (int j=0; j<MAX_BOARD_SIZE; j++){
            if (!(empty_tile(b->tile_board[i][j])))
                return 0;
        }
    }
    return 1;  
}

//Show the board
void show_board(struct board *b){
    for (unsigned i=0; i<b->dim;i++){
        for (unsigned int j=0; j<b->dim; j++){
            if (tile_is_empty(b->tile_board[i][j]))
                printf("   ");
            else{
            printf("%s ▼ \e[0m",color_cstring(tile_edge(b->tile_board[i][j],NORTH)));
            }   
        }
        printf("\n");
        for (unsigned int j=0; j<b->dim; j++){
            if (tile_is_empty(b->tile_board[i][j]))
                printf("   ");
            else{
                printf("%s▶\e[0m%s ◀\e[0m",color_cstring(tile_edge(b->tile_board[i][j],WEST)),color_cstring(tile_edge(b->tile_board[i][j],EAST)));
            }
        }
        printf("\n");
        for (unsigned int j=0; j<b->dim; j++){
            if (tile_is_empty(b->tile_board[i][j]))
                printf("   ");
            else{
                printf("%s ▲ \e[0m",color_cstring(tile_edge(b->tile_board[i][j],SOUTH)));
            }
        }
        printf("\n");
    }
}


///////////////////////////////TILES DISTRIBUTION///////////////////////////////


//Return the number of tiles in a deck
int tiles_count(struct deck *d){
    int sum = 0;
    for (unsigned int i=0; i<d->size; i++){
        sum += (d->cards[i]).n;
    }
    return sum;
}

//The number of tiles that each player has in hand after the distribution
//t_c : tiles_count
//p_c : players_count
int hand_size(int t_c, int p_c){
    if (p_c > 0)
        return (t_c)/(p_c);
    else
        return 0;
}

//List of tiles distributed from the deck
const struct tile *list_tiles[MAX_TILE]; 

//Distribution of tiles from deck to a list (list_tiles)
void split_tiles_tolist(struct deck *d, const struct tile *list[]){
    int k = 0;
    for (unsigned int i=0; i<d->size; i++ ){
        for (unsigned int j=0; j<(d->cards[i]).n; j++){
            list[k+j] = d->cards[i].t;
        }
        k += (d->cards[i]).n;
    }
}


//Function allows to mix the tiles in the list
//tiles_count : number of tiles in the list 
void mix_tiles(int tiles_count, const struct tile *list[]){
    for (int i=0; i<tiles_count-1; i++){
        int r;
        if (i==10)
            r = 0;
        else
            r = (my_rand() % (tiles_count-i-1));
        const struct tile *temp = list[i];   
        list[i] = list[i+r+1];              
        list[i+r+1] = temp;                 
    }                                                            
}


//Distribution of tiles to players
void split_tiles(int tiles_count, const struct tile *list[], struct players *p){
    for (int i=0; i < hand_size(tiles_count, p->players_count); i++){
        for (int j=0; j < p->players_count; j++){
            file_push(&(p->list_players[j].hand),list[j+i*(p->players_count)]);
            p->list_players[j].hand_size++;
        }      
    }
}


//ALL IN ONE: mix tiles and split it to players
void split_deck(struct deck *d, struct players *p){
    int t_c = tiles_count(d);
    split_tiles_tolist(d, list_tiles);
    mix_tiles(t_c,list_tiles);
    split_tiles(t_c, list_tiles, p);
}


//init players
void players_init(int size, struct players *p){
    p->players_count = size;
    p->players_active= size;
    for (int i=0; i<p->players_count; i++){
        p->list_players[i].hand_size = 0;
        file_init(&(p->list_players[i].hand));
        p->list_players[i].score = 0;
        p->list_players[i].active = 1;
        
    }
}


//A predicate indicating whether we can place a tile in the coordinates (x,y) (1 if so, 0 if not)
int can_place_tile_rules(const struct tile *t, struct board *b, struct coord c){
    int corner = 0; //1 if the tile is on the corner, 0 if not
    int side = 0;   //1 if the tile is on the side, 0 if not
    int k = 0;      //Indicator for adjacent empty tiles
    if (tile_is_empty(b->tile_board[c.x][c.y])){

        if ((c.x==0)||(c.x==b->dim-1)||(c.y==0)||(c.y==b->dim-1))
            side = 1;
        if ( ((c.x==0)&&(c.y==0)) || ((c.x==0)&&(c.y==b->dim-1)) || ((c.x==b->dim-1)&&(c.y==0)) || ((c.x==b->dim-1)&&(c.y==b->dim-1)) )
            corner = 1;
        if (c.x != 0){
            if (!(tile_is_empty(b->tile_board[c.x-1][c.y]))){
                if (strcmp(color_name(tile_edge(t,NORTH)),color_name(tile_edge(b->tile_board[c.x-1][c.y],SOUTH))))
                    return 0;
            }
            else{
                k++;
            }
        }
        if (c.y != b->dim-1){
            if (!(tile_is_empty(b->tile_board[c.x][c.y+1]))){
                if (strcmp(color_name(tile_edge(t,EAST)),color_name(tile_edge(b->tile_board[c.x][c.y+1],WEST))))
                    return 0;
            }
            else{
                k++;
            }
        }
        if (c.x != b->dim -1){
            if (!(tile_is_empty(b->tile_board[c.x+1][c.y]))){
                if (strcmp(color_name(tile_edge(t,SOUTH)),color_name(tile_edge(b->tile_board[c.x+1][c.y],NORTH))))
                    return 0;
            }
            else{
                k++;
            } 
        }
        if (c.y != 0){
            if (!(tile_is_empty(b->tile_board[c.x][c.y-1]))){
                if (strcmp(color_name(tile_edge(t,WEST)),color_name(tile_edge(b->tile_board[c.x][c.y-1],EAST))))
                    return 0;
            }
            else{
                k++;
            }
        }
        if( ((k == 4) && (side==0)) || ((k==2) && (corner==1)) || ((k==3) && (side==1)) )
            return 0;

        return 1;
    }
    return 0;
}


//CAN Just place the tile if the place is empty ... (1 if so, 0 if not)
int can_place_tile(struct board *b, struct coord c){
    if (tile_is_empty(b->tile_board[c.x][c.y]))
        return 1;
    return 0;
}


//Function that places a tile in the board according to coordinates(x,y) 
void place_tile(const struct tile *t, struct board *b, struct coord c){
    if (can_place_tile(b,c)){
        b->tile_board[c.x][c.y] = t;
    }
}


//Fill the list of authorized coordinates and returns the size of the list
int fill_authorized_places(const struct tile *t,struct board *b,struct coord list[],int turn){
    int k=0;
    for (unsigned int i=0; i<b->dim; i++){
        for (unsigned int j=0; j<b->dim; j++){
            struct coord c={i,j};
            if ((can_place_tile_rules(t,b,c)) || (turn==1)){
                list[k] = c;
                k++;
            }
        }
    }
    return (k); 
}



//ALL IN ONE: Selects randomly a coordinate from the list after filling the list of coordinates ;)
struct coord select_position(const struct tile *t,struct board *b, struct coord list[],int turn){
    int size = fill_authorized_places(t,b,list,turn); //!=0 car sinon la fct ne sera pas appellée (voir la boucle dans project.c)
    int r = rand() % size;
    return list[r];
    
}


//Displays results and the winner
void display_results(struct players *p){
    int list_score[p->players_count];
    printf("\n------------------RESULTS-----------------\n\n");
    printf("            PLAYER    |    SCORE    \n");
    printf("-------------------------------------------\n");
    for (int i=1; i<=p->players_count; i++){
    printf("           Player %d        %d     \n",i,p->list_players[i-1].score);
        list_score[i-1] = p->list_players[i-1].score;
    }
    int max_ind = 0;
    for (int i=1; i<p->players_count; i++){
        if (list_score[i] > list_score[max_ind])
            max_ind = i;
    }
    printf("Player %d wins !\n",max_ind+1);

}

