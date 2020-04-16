#ifndef __MAP_H__
#define __MAP_H__
#include "render.h"


class Map {
private:
  static elem_t savedMap[MAP_W][MAP_H];
public:
  static elem_t map[MAP_W][MAP_H];
  static void loadMap(int id = 0);
  static void saveMap(int id = 0);
};
#endif
