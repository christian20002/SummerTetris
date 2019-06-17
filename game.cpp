#include <ncurses.h>
#include <unistd.h>
#include <string>

const int DEBUG_DELAY = 00000;
const int REFRESH_DELAY = 1666;
const int NCOLUMNS = 10;
const int NROWS = 20;

const int UP = 'w';
const int DOWN = 's';
const int RIGHT = 'd';
const int LEFT = 'a';
const int ROTATE_LEFT = 'j';
const int ROTATE_RIGHT = 'k';

const bool DEBUG_COLLISION = false;



using namespace std;

class Tetrimino;

void placeBlock(char board[NROWS][NCOLUMNS], Tetrimino* block);


class Tetrimino {
  protected:
    int x = 4;
    int y = 0;
    
    
    
  public:
    string name;
    int orientation = 0;
    string (*shapes)[5][5];

    bool isTouchingFloor(char board[NROWS][NCOLUMNS]){
      int probX = x;
      int probY = y;
      char probCell;
      char probCellBelow;
      char probBoard;
      char** curShape = getShape();
      for (int i = 0; i < 4; i++) {
        probY = y+i;

        for (int j = 0; j < 4; j++) {

          probX = x+j;
          probCell = curShape[i][j];
          probCellBelow = curShape[i+1][j];
          probBoard = board[y+i+1][x+j];
          if ((probCell == '#')&&(probCellBelow !='#')){
            if (probY >= 19) {
              mvprintw(18,20,"CONTACT");
              return true;

            }
            if 
              (probBoard !='.'){
                mvprintw(18,20,"CONTACT");
                return true;
              }

          }
          if (DEBUG_COLLISION){
          ::move(probY,probX);
          addch('x');
          refresh();
          ::move(probY,probX);
          usleep(100000);
          addch(probCell);
          mvprintw(20,15," ProbX: %d ProbY %d ",probX, probY);
          printw("ProbC: %c ",probCell);
          printw("ProbB: %c",probBoard);
          refresh();
          }
          //usleep(1000);
        

         // probX++;
        }
        //probY++;

      }
      return false;
    }
    
    void move(int dir) {
      x+=dir;
    }

    int getX(void) {
      return x;
    }

    int getY(void) {
      return y;
    }

    void rotate(int direction) {
      orientation += direction;
      if (orientation == 4) {
        orientation = 0;
      }

      if (orientation == -1) {
        orientation = 3;
      }
    }

    Tetrimino () {
      //string testString = m_shapes[0][0];
      //printw(testString.c_str());
      //refresh();
      //sleep(1);
     
    }

    void fall (char board[NROWS][NCOLUMNS]) {

      if (!isTouchingFloor(board)) {
        y++;
      }

      else {
        placeBlock(board, this);
        x = 4;
        y = 0;
      }
    }


    char** getShape(void) {

     
      char** shapeOut = 0;
      shapeOut = new char*[5];
      for (int i = 0; i < 5; i++) {
        shapeOut[i] =const_cast<char*>((*shapes)[orientation][i].c_str());
      }
      return shapeOut;
    }

    void hardDrop(char board[NROWS][NCOLUMNS]) {
      while(!isTouchingFloor(board)){
        fall(board);
      }
    }
};

class IBlock : public Tetrimino {

    private:
    string m_shapes[5][5]= {
                { "    ",
                  "####",
                  "    ",
                  "    "},

                { "  # ",
                  "  # ",
                  "  # ",
                  "  # "},

                { "    ",
                  "    ",
                  "####",
                  "    ",
                  "    ",},

                { " #  ",
                  " #  ",
                  " #  ",
                  " #  ",
                  "    ",}

                };
  
    public:
    IBlock() : Tetrimino () {
      name = "IBlock";
      shapes = &m_shapes;
    }
};



class TBlock : public Tetrimino {

    private:
    string m_shapes[5][5]= {
                { " #  ",
                  "### ",
                  "    ",
                  "    "},

                { " #  ",
                  " ## ",
                  " #  ",
                  "    "},

                { "    ",
                  "### ",
                  " #  ",
                  "    ",
                  "    ",},

                { " #  ",
                  "##  ",
                  " #  ",
                  "    ",
                  "    ",}

                };
  
    public:
    TBlock() : Tetrimino () {
      name = "TBlock";
      shapes = &m_shapes;
    }
};

class OBlock : public Tetrimino {

    private:
    string m_shapes[5][5]= {
                { "##  ",
                  "##  ",
                  "    ",
                  "    "},

                { "##  ",
                  "##  ",
                  "    ",
                  "    "},

                { "##  ",
                  "##  ",
                  "    ",
                  "    ",
                  "    ",},

                { "##  ",
                  "##  ",
                  "    ",
                  "    ",
                  "    ",}

                };
  
    public:
    OBlock() : Tetrimino () {
      name = "Oblock";
      shapes = &m_shapes;
    }
};

class SBlock : public Tetrimino {

    private:
    string m_shapes[5][5]= {
                { " ## ",
                  "##  ",
                  "    ",
                  "    "},

                { " #  ",
                  " ## ",
                  "  # ",
                  "    "},

                { "    ",
                  " ## ",
                  "##  ",
                  "    ",
                  "    ",},

                { "#   ",
                  "##  ",
                  " #  ",
                  "    ",
                  "    ",}

                };
  
    public:
    SBlock() : Tetrimino () {
      name = "SBlock";
      shapes = &m_shapes;
    }
};

class ZBlock : public Tetrimino {

    private:
    string m_shapes[5][5]= {
                { "##  ",
                  " ## ",
                  "    ",
                  "    "},

                { "  # ",
                  " ## ",
                  " #  ",
                  "    "},

                { "    ",
                  "##  ",
                  " ## ",
                  "    ",
                  "    ",},

                { " #  ",
                  "##  ",
                  "#   ",
                  "    ",
                  "    ",}

                };
  
    public:
    ZBlock() : Tetrimino () {
      name = "Zblock";
      shapes = &m_shapes;
    }
};

class LBlock : public Tetrimino {

    private:
    string m_shapes[5][5]= {
                { "  # ",
                  "### ",
                  "    ",
                  "    "},

                { " #  ",
                  " #  ",
                  " ## ",
                  "    "},

                { "    ",
                  "### ",
                  "#   ",
                  "    ",
                  "    ",},

                { "##  ",
                  " #  ",
                  " #  ",
                  "    ",
                  "    ",}

                };
  
    public:
    LBlock() : Tetrimino () {
      shapes = &m_shapes;
    }
};

void placeBlock(char (board)[NROWS][NCOLUMNS], Tetrimino *block) {

  int x =  block->getX();
  int y = block->getY();


  for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {
       
        char c =(block->getShape()[i][j]);
        if (c!= ' ') {
          board[y+i][x+j] = c;
          if(DEBUG_COLLISION) {
            mvaddch(y+i,x+j,c);
            usleep(400000);
            refresh();
            }
          } 
        }
      }
    }

void debugDelay (void) {
  usleep(DEBUG_DELAY);
  if (DEBUG_DELAY > 0) {
    refresh();
  }
}

void display (char board[NROWS][NCOLUMNS], Tetrimino * block) {

  erase();
  
  int x = block->getX();
  int y = block->getY();
  printw("Score: %s",""+10);
  for (int y = 0; y < NROWS; y++){
   
    for (int x = 0; x < NCOLUMNS; x++) {

      mvaddch(y,x,board[y][x]);
      //refresh();
      //usleep(DEBUG_DELAY);
    }
    //mvaddnstr(y+1,0,board[y],10);
    debugDelay();

  }
  printw(block->name.c_str());
  printw("\n");
  printw("X: %d Y: %d",block->getX(),block->getY());
  



      
      move(y,x);
      for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {
       move(y+i,x+j);
        char c =(block->getShape()[i][j]);
        if (c!= ' ') {
          addch(c);
        }
        
        
        }
      }
      
     


  refresh(); 
} 

/*this input uses global consts so that input()
 can be substitued for something else when the
 platform or hardware change!*/

int input(void) {
    //int ch = getch();
    int i = getch();
  switch (i){
    
     
      case 'a':
        return LEFT;
        break;
      case 'd':
        return RIGHT;
        break;
        
      default:
      return i;
      break;
  }
    //return i;

}
/*  Here I hope to make a game loop
*   that is independent of any user
    interface: that is, it makes no
    explicit references to curses or
    the LED display or even SDL if
    we end up do
    ing that
*/

int gameLoop(void) {

  IBlock ib;
  OBlock ob;
  TBlock tb;
  SBlock sb;
  ZBlock zb;
  LBlock lb;
  Tetrimino* m = &tb;
  //*m.getShape();
  //sleep(1);

  char gameboard[NROWS][NCOLUMNS];
  /*for (auto& row : gameboard) {
    for(auto& c  : row) {
      c = '0';sle==
    }
  }*/

  for (int y = 0; y < NROWS; y++) {
    for (int x = 0; x < NCOLUMNS; x++) {
      gameboard[y][x] = '.';
    }
  }

  bool gameOver = false;

  int dropTic = 0;
  int dropTime = 100;
  while (!gameOver){
   //char i = input();
   //mvprintw(10,10,"Hey %s",""+getch());
   //debugDelay();
   //refresh();
   

    if (dropTic > dropTime) {
      dropTic = 0;
     m->fall(gameboard); }
    dropTic++;
    display(gameboard, m);
    //erase();
    //t.getShape();
    usleep(DEBUG_DELAY);
    usleep(REFRESH_DELAY);


   
   switch (input()){
      case 't':
        m = &tb;
        break;
      case 'o':
        m = &ob;
        break;
      case 'i':
        m = &ib;
        break;
      case UP:
        m->hardDrop(gameboard);
        break;
      case DOWN:
        dropTime = 10;
        break;
      case 'z':
        m = &zb;
        break;
      case 'l':
        m = &lb;
        break;
      case ROTATE_LEFT: m->rotate(-1);
        break;
      case ROTATE_RIGHT: m->rotate(1);
        break;
      case 'q':
        gameOver = true;
        break;
      case LEFT:
        m->move(-1);
        break;
      case RIGHT:
        m->move(1);
        break;
      default:
        dropTime = 100;
      

    }
  

    
    refresh();
  }
  addstr("Game Over");
  refresh();
  return 0;
}




int main() {

  initscr();
  (void) noecho();

  //addstr("What is your name> ");
  //refresh();
  //getnstr(users_name, sizeof(users_name) - 1);

  /* Here is where we clear the screen.                  */
  /* (Remember, when using Curses, no change will appear */
  /* on the screen until <b>refresh</b>() is called.     */
  clear();

  printw("Starting game loop!\n");
  refresh();
  //sleep(1);
  nodelay(stdscr, TRUE);
  gameLoop();
  sleep(1);
  endwin();
  return 0;
}