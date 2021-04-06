#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

#include "game.h"
#include "pattern.h"
 
// Global seed for the random number generator
static int seed = 0;
// Players number: 2 by default)
static unsigned players_count = 2;
// Board side size: 10 by default 
static unsigned board_size = 10;


///////////////////////////////////////////////////////////////////////////////// 

// Function for parsing the options of the program
// Currently available options are :
// -s <seed>   : sets the seed (int)
// -n <number> : sets the number of players (int)
// -b <size>   : sets the board's size (int)
void parse_opts(int argc, char* argv[]) {
    seed = time(NULL);
    int opt;
    while ((opt = getopt(argc, argv, "s:b:n:")) != -1)
    {
        switch (opt)
        {
        case 's':
            seed = atoi(optarg);
            break;
        case 'b':
            board_size = atoi(optarg);
            break;
        case 'n':
            players_count = atoi(optarg);
            break;
        default: /* '?' */
            fprintf(stderr, "usage: %s [-s seed -b board_size -n players] \n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
}

/////////////////////////////////////////MAIN//////////////////////////////////////////

int main(int argc, char *argv[]){
  parse_opts(argc, argv);
  srand(seed);
  printf("----------------------------------------------------------------------\n");
  printf("seed : %d\nplayers_count : %d\nboard_size : %d\n",seed,players_count,board_size);
  

////////////////////////////////////INITIALIZATION////////////////////////////////////

  //BOARD_INIT
  struct board b;
  board_init(&b, board_size);

  //DECK_INIT
  struct deck d;
  deck_init(&d);

  //PLAYERS_INIT
  struct players p;
  players_init(players_count, &p); //The tiles are distributed to the players
  split_deck(&d,&p);

  //PATTERNS_INIT
  struct patterns pats;
  patterns_init(&pats);
  

////////////////////////////////////THE GAME STARTS///////////////////////////////////

  int turn = 0;
  int skipped_turns = 0;
  int ind_player = 0;
  int number_central_tiles = 0;
  
  
  while (skipped_turns != p.players_active){
      ind_player = ind_player % players_count;
      ind_player++;
      turn++;
      printf("\nTurn %d :\n",turn);
      struct player *active_player = get_next_player(&p,turn);
      if (active_player != NULL){
          const struct tile *active_player_card = file_top(&(active_player->hand));
          struct coord list_authorized_places[board_size*board_size];
          if (fill_authorized_places(active_player_card,&b,list_authorized_places,turn)){
              skipped_turns = 0;
              struct coord position = select_position(active_player_card,&b,list_authorized_places,turn);
              place_tile(active_player_card,&b,position);
              printf("Player %d places his tile in (%d,%d)\n",ind_player,position.x,position.y);
              active_player->score++;
              if (is_central_tile(active_player_card,&pats)){
                  update_tile_owner(active_player,position,number_central_tiles);
                  number_central_tiles++;
              }
              file_pop(&(active_player->hand));
              active_player->hand_size--;
              printf("Remaining tiles : %d\n",active_player->hand_size);
              if (active_player->hand_size == 0){
                printf("A player has placed all his tiles, the game is over\n");
                //show_board(&b);
                break;
              }
          }
          else{
              skipped_turns++;
              file_pop(&(active_player->hand));
              file_push(&(active_player->hand),active_player_card);
              printf("Skipped turn\n");
          }
      }
      else{
          break;
      }
      //show_board(&b);
    }
    show_board(&b);

////////////////////////////////////RESULTS DISPLAY///////////////////////////////////
  printf("\n-----------------GAME OVER-----------------\n"); 
  attribute_score_pattern(&b,&p,&pats);
  display_results(&p);

  
  return 0;
}