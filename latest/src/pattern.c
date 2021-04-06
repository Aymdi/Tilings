#include <stdio.h>

#include "pattern.h"
#include "struct_tile.h"

//////////////////////////PATTERNS INITIALIZATION//////////////////////////

//Fill the pattern table with empty tiles
void patterns_nil(struct patterns *pat){
    for (int i=0; i<pat->number_patterns; i++){
        for (int j=0; j<5; j++){
            for(int k=0; k<5; k++){
                pat->list_patterns[i].pattern_tiles[j][k] = empty_tile();
            }
        }
    }
}

//list of pattern tiles
struct tile pattern_tiles[20][5][5];

//pattern initialization
void patterns_init(struct patterns *pats){
    pats->number_patterns = 4; //We will define 3 patterns for the moment
    patterns_nil(pats);

    //Pattern 1 
    pats->list_patterns[0].size  = 1;
    pats->list_patterns[0].score = 34;
    ////central_tile
    pattern_tiles[0][2][2] = (struct tile) {{color_from_name("rouge"),
                                            color_from_name("rouge"),
                                            color_from_name("rouge"),
                                            color_from_name("rouge")}};
    pattern_tiles[0][1][2] = (struct tile) {{color_from_name("noir"),
                                            color_from_name("rouge"),
                                            color_from_name("noir"),
                                            color_from_name("noir")}};
    pattern_tiles[0][3][2] = (struct tile) {{color_from_name("rouge"),
                                            color_from_name("noir"),
                                            color_from_name("noir"),
                                            color_from_name("noir")}};
    pattern_tiles[0][2][3] = (struct tile) {{color_from_name("noir"),
                                            color_from_name("noir"),
                                            color_from_name("noir"),
                                            color_from_name("rouge")}};
    pattern_tiles[0][2][1] = (struct tile) {{color_from_name("noir"),
                                            color_from_name("noir"),
                                            color_from_name("rouge"),
                                            color_from_name("noir")}};
    pats->list_patterns[0].pattern_tiles[2][2] = (&(pattern_tiles[0][2][2]));
    pats->list_patterns[0].pattern_tiles[1][2] = (&(pattern_tiles[0][1][2]));
    pats->list_patterns[0].pattern_tiles[3][2] = (&(pattern_tiles[0][3][2]));
    pats->list_patterns[0].pattern_tiles[2][3] = (&(pattern_tiles[0][2][3]));
    pats->list_patterns[0].pattern_tiles[2][1] = (&(pattern_tiles[0][2][1]));

    //Pattern 2 
    pats->list_patterns[1].size  = 1;
    pats->list_patterns[1].score = 70;
    ////central_tile
    pattern_tiles[1][2][2] = (struct tile) {{color_from_name("rouge"),
                                            color_from_name("rouge"),
                                            color_from_name("rouge"),
                                            color_from_name("rouge")}};
    pattern_tiles[1][1][2] = (struct tile) {{color_from_name("noir"),
                                            color_from_name("rouge"),
                                            color_from_name("noir"),
                                            color_from_name("noir")}};
    pattern_tiles[1][2][3] = (struct tile) {{color_from_name("noir"),
                                            color_from_name("noir"),
                                            color_from_name("noir"),
                                            color_from_name("rouge")}};
    pattern_tiles[1][2][1] = (struct tile) {{color_from_name("noir"),
                                            color_from_name("noir"),
                                            color_from_name("rouge"),
                                            color_from_name("noir")}};
    pats->list_patterns[1].pattern_tiles[2][2] = (&(pattern_tiles[1][2][2]));
    pats->list_patterns[1].pattern_tiles[1][2] = (&(pattern_tiles[1][1][2]));
    pats->list_patterns[1].pattern_tiles[2][3] = (&(pattern_tiles[1][2][3]));
    pats->list_patterns[1].pattern_tiles[2][1] = (&(pattern_tiles[1][2][1]));

    //Pattern 3
    pats->list_patterns[2].size  = 1;
    pats->list_patterns[2].score = 80;
    ////central_tile
    pattern_tiles[2][2][2] = (struct tile) {{color_from_name("rouge"),
                                            color_from_name("rouge"),
                                            color_from_name("vert"),
                                            color_from_name("vert")}};
    pattern_tiles[2][1][2] = (struct tile) {{color_from_name("vert"),
                                            color_from_name("rouge"),
                                            color_from_name("vert"),
                                            color_from_name("vert")}};
    pattern_tiles[2][3][2] = (struct tile) {{color_from_name("rouge"),
                                            color_from_name("vert"),
                                            color_from_name("vert"),
                                            color_from_name("vert")}};
    pats->list_patterns[2].pattern_tiles[2][2] = (&(pattern_tiles[2][2][2]));
    pats->list_patterns[2].pattern_tiles[1][2] = (&(pattern_tiles[2][1][2]));
    pats->list_patterns[2].pattern_tiles[3][2] = (&(pattern_tiles[2][3][2]));

    //Pattern 4
    pats->list_patterns[3].size  = 0;
    pats->list_patterns[3].score = 20;
    ////central_tile
    pattern_tiles[3][2][2] = (struct tile) {{color_from_name("rouge"),
                                            color_from_name("rouge"),
                                            color_from_name("rouge"),
                                            color_from_name("rouge")}};
    pats->list_patterns[3].pattern_tiles[2][2] = (&(pattern_tiles[3][2][2]));


}


//Check if the tile is a central tile of a pattern (1 if so, 0 if not)
int is_central_tile(const struct tile *t,struct patterns *pats){
    if (!(tile_is_empty(t))){
        for (int i=0; i<pats->number_patterns; i++){
            if (tile_equals(pats->list_patterns[i].pattern_tiles[2][2],t))
                return 1;
        }
    }
    return 0;
}


//returns the number of patterns in the board
int num_pattern_board(struct board *b, struct patterns *pats){
    int sum = 0;
    for (unsigned int i=0; i<b->dim; i++){
        for (unsigned int j=0; j<b->dim; j++){
            if(is_central_tile(b->tile_board[i][j],pats)){
                sum++;
            }
        }
    }
    return sum;
}

struct coord coord_central_tiles[MAX_TILE];

//upgrade the information of both player and his tile when it's central.
void update_tile_owner(struct player *p, struct coord c, int size){
    coord_central_tiles[size] = c;
    p->coord_central_tiles[p->central_tiles_owns] = &(coord_central_tiles[size]);
    p->central_tiles_owns++;
}


//Verify if the central tile complete its pattern 
//t: pointer to the central tile
//c: coordinates of the central tile
int is_pattern(const struct tile *t,struct coord c,struct board *b, struct pattern *pat){
    if (tile_equals(t,pat->pattern_tiles[2][2])){
        for (int i = -pat->size; i <= pat->size; i++){
            for (int j= -pat->size; j <= pat->size; j++){
                if (tile_is_empty(pat->pattern_tiles[2+i][2+j]) == 0){
                    if ( ((c.x+i)<b->dim) && ((c.y+j)<b->dim) /*&& ((c.x+i)>=0) && ((c.y+j)>=0)*/ ){
                        if (tile_is_empty(b->tile_board[c.x+i][c.y+j]) == 0){
                            if (tile_equals(pat->pattern_tiles[2+i][2+j],b->tile_board[c.x+i][c.y+j]) == 0)
                                return 0;
                        }
                        else{
                            return 0;
                        }         
                    }
                    else{
                        return 0;
                    }      
                }    
            }
        }
        return 1;
    }
    return 0;
}


int coord_equal(struct coord c1, struct coord c2){
    if ( (c1.x == c2.x) && (c1.y == c2.y) )
        return 1;
    return 0;
}

//Return the index of the owner of a central tile
int index_owner(struct coord c, struct players *p){
    for (int i=0; i<p->players_count; i++){
        for (int j=0; j<p->list_players[i].central_tiles_owns; j++){
            if (coord_equal(c,*(p->list_players[i].coord_central_tiles[j])))
                return i;
        }
    }
    return -1;
}


//////////////////////////ATTRIBUTING SCORE AT THE END OF THE GAME//////////////////////////

//function that assigns points according to the patterns found in the game
void attribute_score_pattern(struct board *b, struct players *p, struct patterns *pats){
    if ( (pats->number_patterns >0) && (num_pattern_board(b,pats) > 0) ){
        printf("%d PATTERNS FOUND !\n",num_pattern_board(b,pats));
        for (unsigned int i=0; i<b->dim; i++){
            for (unsigned int j=0; j<b->dim; j++){
                struct coord c = {i,j};
                if (is_central_tile(b->tile_board[i][j],pats)){
                    for (int k=0; k<pats->number_patterns; k++){
                        if (is_pattern(b->tile_board[i][j],c,b,&(pats->list_patterns[k]))){
                            int index = index_owner(c,p);
                            p->list_players[index].score += pats->list_patterns[k].score;
                            printf("PATTERN[%d] FOUND : Player %d wins %d points\n",k,index+1,pats->list_patterns[k].score);
                        }
                    }
                }
            }
        }
    }
    else{
        printf("NO PATTERNS FOUND\n");
    }   
}