#ifndef __TANK_H__
#define __TANK_H__
#include <iostream>
#include "render.h"

#define N_TANK_MODEL 1


enum {M_LHT, M_AMR, M_ATG, M_HVY};

class Tank: public Drawable {
protected:
  static char *models[N_TANK_MODEL][4][9];
  static bool canMove[6];
  bool checkMove();
  int modelSel = M_LHT;
  int speed = 500;
  uint64_t lastMove;
public:
  virtual void draw() = 0;
  virtual void move(int direction) = 0;
};


class ManualTank: public Tank {
public:
  void draw();
  void move(int direction);
};

class AutoTank: public Tank {

};


#endif