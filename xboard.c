#include "xboard.h"
#include "game_state.h"
#include "enumerate_moves.h"
#include "bitboard.h"
#include "move.h"
#include "boardstate.h"
#include "search.h"

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define XBOARD_INPUT_BUF_SIZE 1024

#define STREQ(buf, str) !strncmp(buf, str, XBOARD_INPUT_BUF_SIZE)

void xboard_start_io();
void getMove(unsigned char*, move*);
void makeComputerMove(game_state**, move*);
void getMoveText(move*, unsigned char*);

void xboard_start(){
  
  /* handle signals - ignore them for now */
  signal(SIGTERM, SIG_IGN);
  signal(SIGINT, SIG_IGN);

  /* init chess engine */
  srandomdev();
  init_enumerations();
  bb_init();

  /* start I/O with xboard */
  xboard_start_io();
}

void xboard_start_io(){
  /* set non-buffering output */
  setbuf(stdout, NULL);

  char *buf = (char*)malloc(sizeof(unsigned char) * XBOARD_INPUT_BUF_SIZE);
  char *cmd;
  char *argv[7], *inputstring;
  int i;

  game_state *gs;
  color cPlayer = WHITE;
  color cComputer = BLACK;
  move m;
  unsigned char moveText[6];
  moveText[5] = '\0';

  while (1){
    /* read line from stdin */
    fgets(buf, sizeof(char) * XBOARD_INPUT_BUF_SIZE, stdin);

    /* get parameters of line */
    inputstring = buf;
    i = 0;
    while (1){
      argv[i] = strsep(&inputstring, " \t\n");
      if (argv[i] == NULL) break;
      i++;
    }

    cmd = argv[0];

    if (STREQ(cmd, "quit")){
      gsShallowFree(gs);
      free(gs);
      exit(0);
    } else if (STREQ(cmd, "new")){
      gs = createDefaultGamestate();
    } else if(STREQ(cmd, "xboard")){

    } else if (STREQ(cmd, "protover")){
      printf("feature san=0 done=1\n");
    } else if (STREQ(cmd, "accepted")){

    } else if (STREQ(cmd, "rejected")){

    } else if (STREQ(cmd, "variant")){

    } else if (STREQ(cmd, "random")){

    } else if (STREQ(cmd, "force")){

    } else if (STREQ(cmd, "go")){

    } else if (STREQ(cmd, "playother")){

    } else if (STREQ(cmd, "white")){

    } else if (STREQ(cmd, "black")){

    } else if (STREQ(cmd, "level")){

    } else if (STREQ(cmd, "st")){

    } else if (STREQ(cmd, "sd")){

    } else if (STREQ(cmd, "time")){

    } else if (STREQ(cmd, "otim")){

    } else if (STREQ(cmd, "usermove")){

    } else if (STREQ(cmd, "?")){

    } else if (STREQ(cmd, "ping")){
      printf("pong %s\n", argv[1]);
    } else if (STREQ(cmd, "draw")){

    } else if (STREQ(cmd, "setboard")){

    } else if (STREQ(cmd, "edit")){

    } else if (STREQ(cmd, "hint")){

    } else if (STREQ(cmd, "bk")){

    } else if (STREQ(cmd, "undo")){

    } else if (STREQ(cmd, "remove")){

    } else if (STREQ(cmd, "hard")){

    } else if (STREQ(cmd, "easy")){

    } else if (STREQ(cmd, "post")){

    } else if (STREQ(cmd, "nopost")){

    } else if (STREQ(cmd, "analyze")){

    } else if (STREQ(cmd, "name")){

    } else if (STREQ(cmd, "rating")){

    } else if (STREQ(cmd, "ics")){

    } else if (STREQ(cmd, "computer")){

    } else if (STREQ(cmd, "pause")){

    } else if (STREQ(cmd, "resume")){

    } else {
      //printf("move e7e5");
      //fprintf(stderr, "%s\n", buf);
      getMove(argv[0], &m);
      if (!isValidMove(gs, &m)){
	printf("Illegal move: %s\n", argv[0]);
	continue;
      } else {
	makeMove(gs, &m);
      }

      if (isCheckMate(gs, cPlayer)){
	printf("1-0 {White mates}\n");
      }
      else {
	makeComputerMove(&gs, &m);
	getMoveText(&m, moveText);
	printf("move %s\n", moveText);
	if (isCheckMate(gs, cComputer)){
	  printf("0-1 {Black mates}\n");
	}
      }
    }
  }
}

void getMove(unsigned char *ntMove, move *m){
  unsigned int oldRow, oldCol, newRow, newCol;
  piece p;
  oldRow = ('9' - ntMove[1] - 1);
  oldCol = ntMove[0] - 'a';
  newRow = ('9' - ntMove[3] - 1);
  newCol = ntMove[2] - 'a';

  if (ntMove[4] != '\0'){
    switch (ntMove[4]){
    case 'b':
      p = BISHOP;
      break;
    case 'k':
      p = KNIGHT;
      break;
    case 'r':
      p = ROOK;
      break;
    case 'q':
      p = QUEEN;
      break;
    }
    setMoveWithPromotion(m, oldRow, oldCol, newRow, newCol, p);
  } else {
    setMove(m, oldRow, oldCol, newRow, newCol);
  }
}

void makeComputerMove(game_state **gs, move *m){
  /*game_state_list *gslPotentialMoves = enumerate_moves(*gs, 1);
  int r;
  
  long MAX = (1 << 31) - 1;

  r = (int)((random() / (float)MAX) * gslPotentialMoves->length);*/

  game_state *gsFrom = *gs;
  game_state *gsTo;

  gsTo = search(gsFrom, getPlayerToMove(gsFrom), 3);

  findMoveFromTo(getBoardstate(gsFrom), getBoardstate(gsTo), m, getPlayerToMove(gsFrom));

  *gs = gsTo;

  gsShallowFree(gsFrom);
  free(gsFrom);

  //*gs = gs_deepCopy(&gslPotentialMoves->game_states[r]);
  
  //gslDeepFree(gslPotentialMoves);

}

void getMoveText(move *m, unsigned char *text){
  text[0] = m->oldCol + 'a';
  text[1] = 7 - m->oldRow + 1 + '0';
  text[2] = m->newCol + 'a';
  text[3] = 7 - m->newRow + 1 + '0';
}
