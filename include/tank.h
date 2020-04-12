#ifndef __TANK_H__
#define __TANK_H__
#include <iostream>
#include "render.h"
#include "bullet.h"
#include "common.h"



class Tank: public Drawable {
protected:
  static char *models[N_TANK_MODEL][4][9];
  static bool canMove[6];
  static int lifeMaxVals[N_TANK_MODEL];
  static int speedMoveVals[N_TANK_MODEL];
  static int speedFireVals[N_TANK_MODEL];
  static int weaponVals[N_TANK_MODEL];

  bool checkMove();
  
  const int modelSel;
  int lifeMax;
  int speedMove;
  int speedFire;
  int weapon;
  int life;

  uint64_t lastMove;
  uint64_t lastFire;

  int camp;
  int colorBody;
  int colorWheel;
public:
  Tank(int x, int y, int direction, int camp, 
    int modelSel = MD_LHT);
  void draw();
  virtual void move(int direction = 0);
  Bullet *fire();
  void hit(int type);
};

class AutoTank: public Tank {
public:
  void move(int direction = 0);
};


#endif