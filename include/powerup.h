#ifndef __POWERUP_H__
#define __POWERUP_H__
#include "render.h"


class PowerUp: public Drawable {
private:
  int type;
public:
  static void deletePowerUp(PowerUp *p);
  PowerUp(int x, int y, int type): Drawable(x, y, 0), type(type) {}
  void draw();
  void hit(int type, int srcCamp);
};



#endif
