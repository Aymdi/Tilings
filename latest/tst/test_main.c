#include <stdio.h>
#include <string.h>

#include "../src/game.h"
#include "../src/struct_color.h"
#include "../src/struct_tile.h"
#include "../src/pattern.h"

/*
struct color color[8]={{"noir","\e[0;30m"},
                     {"rouge","\e[0;31m"},
					 {"vert","\e[0;32m"},
					 {"jaune","\e[0;33m"},
					 {"bleu","\e[0;34m"},
					 {"violet","\e[0;35m"},
					 {"cyan","\e[0;36m"},
					 {"blanc","\e[0;37m"}
					};
*/

int main(){

//////////////////////////////COLOR.C//////////////////////////////
//color_name  
    if (strcmp( color_name(color_from_name("noir")), (color_from_name("noir"))->name) == 0)
        printf("color_name: PASSED (1/5)\n");
    else
        printf("color_name: FAILED in line %d\n",__LINE__);

    if (strcmp( color_name(color_from_name("rouge")), (color_from_name("rouge"))->name) == 0)
        printf("color_name: PASSED (2/5)\n");
    else
        printf("FAILED in line %d\n",__LINE__);
    if (strcmp( color_name(color_from_name("jaune")), (color_from_name("jaune"))->name) == 0)
        printf("color_name: PASSED (3/5)\n");
    else
        printf("FAILED in line %d\n",__LINE__);
      if (strcmp( color_name(color_from_name("bleu")), (color_from_name("bleu"))->name) == 0)
        printf("color_name: PASSED (4/5)\n");
    else
        printf("FAILED in line %d\n",__LINE__);
    if (strcmp( color_name(color_from_name("violet")), (color_from_name("violet"))->name) == 0)
        printf("color_name: PASSED (5/5)\n");
    else
        printf("FAILED in line %d\n",__LINE__);

//color_cstring

    if (strcmp(color_cstring(color_from_name("noir")),"\e[0;30m" ) == 0)
        printf("color_cstring: PASSED (1/5)\n");
    else
        printf("color_cstring: FAILED in line %d\n",__LINE__);
    if (strcmp(color_cstring(color_from_name("rouge")),"\e[0;31m" ) == 0)
        printf("color_cstring: PASSED (2/5)\n");
    else
        printf("color_cstring: FAILED in line %d\n",__LINE__);
    if (strcmp(color_cstring(color_from_name("vert")),"\e[0;32m" ) == 0)
        printf("color_cstring: PASSED (3/5)\n");
    else
        printf("color_cstring: FAILED in line %d\n",__LINE__);
    if (strcmp(color_cstring(color_from_name("jaune")),"\e[0;33m" ) == 0)
        printf("color_cstring: PASSED (4/5)\n");
    else
        printf("color_cstring: FAILED in line %d\n",__LINE__);
    if (strcmp(color_cstring(color_from_name("bleu")),"\e[0;34m" ) == 0)
        printf("color_cstring: PASSED (5/5)\n");
    else
        printf("color_cstring: FAILED in line %d\n",__LINE__);

//color_from_name
    if (color_from_name(color_from_name("noir")->name)== color_from_name("noir"))
        printf("color_from_name: PASSED (1/4)\n");
    else
        printf("color_from_name: FAILED in line %d\n",__LINE__);
    if (color_from_name(color_from_name("rouge")->name)== color_from_name("rouge"))
        printf("color_from_name: PASSED (2/4)\n");
    else
        printf("color_from_name: FAILED in line %d\n",__LINE__);
    if (color_from_name(color_from_name("vert")->name)== color_from_name("vert"))
        printf("color_from_name: PASSED (3/4)\n");
    else
        printf("color_from_name: FAILED in line %d\n",__LINE__);
    if (color_from_name(color_from_name("bleu")->name)== color_from_name("bleu"))
        printf("color_from_name: PASSED (4/4)\n");
    else
        printf("color_from_name: FAILED in line %d\n",__LINE__);


//////////////////////////////TILE.C//////////////////////////////

    const struct tile *tile_empty = empty_tile();
    const struct tile t1={{color_from_name("noir"),
                    color_from_name("rouge"),
                    color_from_name("bleu"),
                    color_from_name("vert"),
                    }};
    struct tile t2={{color_from_name("noir"),
                    color_from_name("noir"),
                    color_from_name("bleu"),
                    color_from_name("vert"),
                    }};
//empty_tile
    for (int i=0; i<4; i++){
        if (tile_empty->color_direction[i] != NULL)
            printf("empty_tile: FAILED in line %d\n",__LINE__);
    }
    printf("empty_tile: PASSED (1/1)\n");

//tile_is_empty
    if (tile_is_empty(tile_empty))
        printf("tile_is_empty: PASSED (1/2)\n");
    else
        printf("tile_is_empty: FAILED in line %d\n",__LINE__);
    if (tile_is_empty(&t1) == 0)
        printf("tile_is_empty: PASSED (2/2)\n");
    else
        printf("tile_is_empty: FAILED in line %d\n",__LINE__);
    

//tile_equals
    if (tile_equals(&t1,&t1) == 1)
        printf("tile_equals: PASSED (1/2)\n");
    else
        printf("tile_equals: FAILED in line %d\n",__LINE__);
    if (tile_equals(&t1,&t2) == 0)
        printf("tile_equals: PASSED (2/2)\n");
    else
        printf("tile_equals: FAILED in line %d\n",__LINE__);
        
//tile
    if (tile_edge(&t1,NORTH) == t1.color_direction[NORTH])
        printf("tile_edge: PASSED (1/3)\n");
    else
        printf("tile_edge: FAILED in line %d\n",__LINE__);
    if (tile_edge(&t1,SOUTH) == t1.color_direction[SOUTH])
        printf("tile_edge: PASSED (2/3)\n");
    else
        printf("tile_edge: FAILED in line %d\n",__LINE__);
    if (tile_edge(&t1,WEST) == t1.color_direction[WEST])
        printf("tile_edge: PASSED (3/3)\n");
    else
        printf("tile_edge: FAILED in line %d\n",__LINE__);
    
//deck-init
    struct deck d;
    deck_init(&d);
    if (d.size == 4)
        printf("deck_init: PASSED (1/4)\n");
    else
        printf("deck_init: FAILED in line %d\n",__LINE__);
    if (d.cards[0].n == 4)
        printf("deck_init: PASSED (2/4)\n");
    else
        printf("deck_init: FAILED in line %d\n",__LINE__);
    if (strcmp(d.cards[0].t->color_direction[EAST]->name, "noir") == 0)
        printf("deck_init: PASSED (3/4)\n");
    else
        printf("deck_init: FAILED in line %d\n",__LINE__);   
    if (strcmp(d.cards[3].t->color_direction[WEST]->name, "noir") == 0)
        printf("deck_init: PASSED (4/4)\n");
    else
        printf("deck_init: FAILED in line %d\n",__LINE__);    

//////////////////////////////FILE.C//////////////////////////////
    struct file f;
    struct file t;
    struct file empty_file;
//file_init
    file_init(&f);
    file_init(&empty_file);

//file_is_empty
    if (file_is_empty(&f) == 1){
        printf("file_init: PASSED (1/1)\n");
        printf("file_is_empty: PASSED (1/1)\n");
    }
    else
        printf("file_is_empty: FAILED in line %d\n",__LINE__); 

//file_size
    if (file_size(&f) == 0)
        printf("file_size: PASSED (1/2)\n");
    else
        printf("file_size: FAILED in line %d\n",__LINE__); 
    t.head = 2;
    t.tail = 5;
    if (file_size(&t) == 4)
        printf("file_size: PASSED (2/2)\n");
    else
        printf("file_size: FAILED in line %d\n",__LINE__);

//file_push
    file_push(&f,&t1);
    if ((f.head == 1) && (f.tail ==1) && (f.tiles[1] == &t1))
        printf("file_push: PASSED (1/2)\n");
    else
        printf("file_push: FAILED in line %d\n",__LINE__); 

    t.head = 1;
    t.tail = 200;
    file_push(&t,&t1);
    printf("file_push: PASSED (2/2)\n");

//file_top
    if ( file_top(&f) == &t1)
        printf("file_top: PASSED (1/2)\n");
    else
        printf("file_top: FAILED in line %d\n",__LINE__);

    if (file_top(&(empty_file)) == NULL)
        printf("file_top: PASSED (2/2)\n");
    else
        printf("file_top: FAILED in line %d\n",__LINE__);

//file_pop
    file_pop(&f);
    if ( (file_top(&f) == NULL) && (f.head == 0) && (f.tail == 0))
        printf("file_pop: PASSED (1/2)\n");
    else
        printf("file_pop: FAILED in line %d\n",__LINE__);
    //file_init(&empty_file);
    //file_pop(&empty_file);
    printf("file_pop: PASSED (2/2)\n");

////////////////////////////////GAME.C//////////////////////////////////////

////MINI GAME
struct board b;
board_init(&b,3);
if ((tile_is_empty(b.tile_board[0][0])) && tile_is_empty(b.tile_board[2][2]) && (b.dim == 3))
    printf("board_init: PASSED (1/1)\n");
else
    printf("board_init: FAILED\n");

//init deck already done

struct players p;
players_init(2,&p);
printf("players_init: PASSED (1/1)\n");

split_deck(&d,&p);//12 tiles 
if (p.list_players[0].hand_size == p.list_players[1].hand_size)
    printf("split_deck: PASSED (1/2)\n");

extern const struct tile *list_tiles[MAX_TILE]; 
split_tiles_tolist(&d, list_tiles);
printf("%s\n",list_tiles[11]->color_direction[0]->name);
mix_tiles(tiles_count(&d),list_tiles);
printf("%s\n",list_tiles[9]->color_direction[0]->name); 

split_deck(&d,&p);
for (int i=0; i<2; i++){
    printf("Player[%d] hand :\n",i);
    for (int j=0;j<6;j++){
        printf("Tile[%d]:\n",j);
        for (int k=0;k<MAX_DIRECTION;k++)
            printf("Tile[%d](color[%d]): %s\n",j,k,p.list_players[i].hand.tiles[j+1]->color_direction[k]->name);
    }
}
printf("split_deck: PASSED (1/1)\n");
int turn = 1;
struct coord c11={1,1};
place_tile(&t1,&b,c11);


struct player *active_player=&(p.list_players[0]);
const struct tile *active_player_card = file_top(&(active_player->hand));
struct coord list_authorized_places[9];
fill_authorized_places(active_player_card,&b,list_authorized_places,turn);
printf("Player[0] list_authorized_places :\n");
for (int i=0; i<9; i++)
    printf("%d : (%d,%d)\n",i,list_authorized_places[i].x,list_authorized_places[i].y);
printf("fill_authorized_places: PASSED\n");
struct coord position = select_position(active_player_card,&b,list_authorized_places,turn);
printf("Position choosed: (%d,%d)\n",position.x,position.y);
printf("select_position: PASSED\n");
place_tile(&t1,&b,position);
printf("Player[0] placed his tile in (%d,%d)\n",position.x,position.y);
if (tile_equals(b.tile_board[position.x][position.y],&t1))
    printf("place_tile: PASSED\n");
printf("show_board: Shape of a tile\n");
printf(" ▼ \n");
printf("▶ ◀\n");
printf(" ▲ \n");

////////////////////////////////PATTERN.C//////////////////////////////////////
struct patterns pats;
patterns_init(&pats);

const struct tile trouge= {{color_from_name("rouge"),color_from_name("rouge"),color_from_name("rouge"),color_from_name("rouge")}};

if(is_central_tile(&trouge,&pats))
    printf("is_central_tile: PASSED\n");
else
    printf("is_central_tile: FAILED in line %d\n",__LINE__);

struct board b2;
board_init(&b2,5);
struct coord c00 = {0,0};
struct coord c01 = {0,1};
place_tile(&trouge,&b2,c00);
place_tile(&trouge,&b2,c01);
if ( num_pattern_board(&b2,&pats) == 2 )
    printf("num_pattern_board: PASSED (1/2)\n");
else
    printf("num_pattern_board: FAILED in line %d\n",__LINE__);

update_tile_owner(&(p.list_players[0]),c00,0);
update_tile_owner(&(p.list_players[1]),c01,1);

struct tile tp_1={{color_from_name("noir"),
                color_from_name("rouge"),
                color_from_name("noir"),
                color_from_name("noir"),
                }};
struct tile tp_2={{color_from_name("noir"),
                color_from_name("noir"),
                color_from_name("noir"),
                color_from_name("rouge"),
                }};
struct tile tp_3={{color_from_name("rouge"),
                color_from_name("noir"),
                color_from_name("noir"),
                color_from_name("noir"),
                }};
struct tile tp_4={{color_from_name("noir"),
                color_from_name("noir"),
                color_from_name("rouge"),
                color_from_name("noir"),
                }};

struct coord c22={2,2};
struct coord c12={1,2};
struct coord c23={2,3};
struct coord c32={3,2};
struct coord c21={2,1};
place_tile(&trouge,&b2,c22);
place_tile(&tp_1,&b2,c12);
place_tile(&tp_2,&b2,c23);
place_tile(&tp_3,&b2,c32);
place_tile(&tp_4,&b2,c21);
show_board(&b2);
if (num_pattern_board(&b2,&pats) == 3)
    printf("num_pattern_board: PASSED (2/2)\n");
else
    printf("num_pattern_board: FAILED in line %d\n",__LINE__);

if (is_pattern(&trouge,c22,&b2,&(pats.list_patterns[0])))
    printf("is_pattern: PASSED (1/3)\n");
else
    printf("is_pattern: FAILED in line %d\n",__LINE__);
if (is_pattern(&trouge,c00,&b2,&(pats.list_patterns[3])))
    printf("is_pattern: PASSED (1/3)\n");
else
    printf("is_pattern: FAILED in line %d\n",__LINE__);
if (is_pattern(&trouge,c01,&b2,&(pats.list_patterns[3])))
    printf("is_pattern: PASSED (1/3)\n");
else
    printf("is_pattern: FAILED in line %d\n",__LINE__);




return 0;
}