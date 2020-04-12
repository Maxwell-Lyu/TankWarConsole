#ifndef __TANK_H__
#define __TANK_H__
#include <iostream>
#include "render.h"
#include "bullet.h"

#define N_TANK_MODEL 1


enum {M_LHT, M_AMR, M_ATG, M_HVY};

class Tank: public Drawable {
protected:
  static char *models[N_TANK_MODEL][4][9];
  static bool canMove[6];
  bool checkMove();
  int modelSel = M_LHT;
  int speedMove = 500;
  int speedFire = 500;
  uint64_t lastMove;
  uint64_t lastFire;
  int life = 1000;
public:
  Tank(int x, int y, int direction);
  void draw();
  void move(int direction = 0);
  Bullet *fire();
  void hit(int type);
};

class AutoTank: public Tank {

};


#endif