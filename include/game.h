#ifndef __GAME_H__
#define __GAME_H__
#include "common.h"
#include "render.h"

class Game {
private:
  static int menuSel;
  // static void mapSel(int index = -1);
public:
  static void run();
  friend class Render;
};

#endif
