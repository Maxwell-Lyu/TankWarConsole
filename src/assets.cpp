#include "assets.h"
#include "common.h"

void Assets::renderLetter(int x, int y, int color, char letter) {
  for (int ty = -1; ty < 6; ty++)
    for (int tx = -1; tx < 6; tx++)
      std::cout << "\033["<< y + ty + 1 << ";" <<  (x + tx) * 2 + 1 << "H\033[" << color << ";1m" << "  " << std::endl;
  for (int ty = 0; ty < 5; ty++)
    for (int tx = 0; tx < 5; tx++)
    if(Letter[letter - 'A'][ty][tx])
      std::cout << "\033["<< y + ty + 1 << ";" <<  (x + tx) * 2 + 1 << "H\033[" << color << ";1m" << "██" << std::endl;
}
void Assets::renderDight(int x, int y, int color, int digit) {
  for (int ty = -1; ty < 6; ty++)
    for (int tx = -1; tx < 4; tx++)
      std::cout << "\033["<< y + ty + 1 << ";" <<  ((x + tx) << 1) + 1 << "H\033[" << color << ";1m" << "  " << std::endl;
  for (int ty = 0; ty < 5; ty++)
    for (int tx = 0; tx < 3; tx++)
      if(Digit[digit][ty][tx])
        std::cout << "\033["<< y + ty + 1 << ";" <<  ((x + tx) << 1) + 1 << "H\033[" << color << ";1m" << "██" << std::endl;
}

int Assets::Letter[26][5][5] {
{ {0, 1, 1, 1, 0},//A
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1} },

{ {1, 1, 1, 1, 0},//B
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 0},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 0} },

{ {0, 1, 1, 1, 0},//C
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 1},
  {0, 1, 1, 1, 0} },

{ {1, 1, 1, 1, 0},//D
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 0} },

{ {1, 1, 1, 1, 1},//E
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1} },

{ {1, 1, 1, 1, 1},//F
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0} },

{ {0, 1, 1, 1, 1},//G
  {1, 0, 0, 0, 0},
  {1, 0, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {0, 1, 1, 1, 0} },

{ {1, 0, 0, 0, 1},//H
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1} },

{ {1, 1, 1, 1, 1},//I
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {1, 1, 1, 1, 1} },

{ {1, 1, 1, 1, 1},//J
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {1, 1, 1, 0, 0} },

{ {1, 0, 0, 0, 1},//K
  {1, 1, 0, 1, 0},
  {1, 0, 1, 0, 0},
  {1, 0, 0, 1, 0},
  {1, 0, 0, 0, 1} },

{ {1, 0, 0, 0, 0},//L
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1} },

{ {1, 1, 0, 1, 1},//M
  {1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1} },

{ {1, 0, 0, 0, 1},//N
  {1, 1, 0, 0, 1},
  {1, 0, 1, 0, 1},
  {1, 0, 0, 1, 1},
  {1, 0, 0, 0, 1} },

{ {0, 1, 1, 1, 0},//O
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {0, 1, 1, 1, 0} },

{ {1, 1, 1, 1, 0},//P
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0} },

{ {0, 1, 1, 1, 0},//Q
  {1, 0, 0, 0, 1},
  {1, 0, 1, 0, 1},
  {1, 0, 0, 1, 1},
  {0, 1, 1, 1, 1} },

{ {1, 1, 1, 1, 0},//R
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 0},
  {1, 0, 1, 0, 0},
  {1, 0, 0, 1, 1} },

{ {0, 1, 1, 1, 1},//S
  {1, 0, 0, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 0, 1},
  {1, 1, 1, 1, 0} },

{ {1, 1, 1, 1, 1},//T
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0} },

{ {1, 0, 0, 0, 1},//U
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {0, 1, 1, 1, 0} },

{ {1, 0, 0, 0, 1},//V
  {1, 0, 0, 0, 1},
  {0, 1, 0, 1, 0},
  {0, 1, 0, 1, 0},
  {0, 0, 1, 0, 0} },

{ {1, 0, 1, 0, 1},//W
  {1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1},
  {0, 1, 0, 1, 0} },

{ {1, 0, 0, 0, 1},//X
  {0, 1, 0, 1, 0},
  {0, 0, 1, 0, 0},
  {0, 1, 0, 1, 0},
  {1, 0, 0, 0, 1} },

{ {1, 0, 0, 0, 1},//Y
  {0, 1, 0, 1, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0} },

{ {1, 1, 1, 1, 1},//Z
  {0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0},
  {1, 1, 1, 1, 1} },
};


int Assets::Digit[10][5][3] {
{ {1, 1, 1},//0
  {1, 0, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1} },

{ {1, 1, 0},//1
  {0, 1, 0},
  {0, 1, 0},
  {0, 1, 0},
  {1, 1, 1} },

{ {1, 1, 1},//2
  {0, 0, 1},
  {1, 1, 1},
  {1, 0, 0},
  {1, 1, 1} },

{ {1, 1, 1},//3
  {0, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1} },

{ {1, 0, 1},//4
  {1, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1} },

{ {1, 1, 1},//5
  {1, 0, 0},
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1} },

{ {1, 1, 1},//6
  {1, 0, 0},
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1} },

{ {1, 1, 1},//7
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1} },

{ {1, 1, 1},//8
  {1, 0, 1},
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1} },

{ {1, 1, 1},//9
  {1, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1} },
};