#ifndef __BASE_H__
#define __BASE_H__

#include "tank.h"


class Base: public Tank {
private:
  static int lifeMaxVal;
public:
  Base(int x, int y);
  void draw();
  void move();
};

#endif
