#ifndef __ASSET_H__
#define __ASSET_H__
#include "render.h"

#define _P(c, v) {F_##c, B_BLK, v}
#define P(c) _P(c, "█")
#define B(c) _P(c, "  ")

class Assets {
public:
  static int Letter[26][5][5];
  static int Digit[10][5][3];
  static void renderLetter(int x, int y, int color, char letter);
  static void renderDight(int x, int y, int color, int digit);
};

#endif
