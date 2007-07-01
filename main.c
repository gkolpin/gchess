#include <unistd.h>

int xboard;

void processCommands();

int main(int argc, char **argv){

  xboard = 0;
  
  char ch;
  while ((ch = getopt(argc, argv, "x")) != -1){
    switch(ch){
    case 'x':
      xboard = 1;
      break;
    }
  }
  
  processCommands();

  return 0;
}

void processCommands(){
  if (xboard){
    xboard_start();
  }
}
