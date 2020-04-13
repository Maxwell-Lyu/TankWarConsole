#ifndef __TANK_H__
#define __TANK_H__
#include <iostream>
#include "render.h"
#include "bullet.h"
#include "common.h"



class Tank: public Drawable {
protected:
  static char *models[N_TANK_MODEL][4][9];
  static bool canMove[N_TERRIAN];
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
  int nLife;

  uint64_t lastMove;
  uint64_t lastFire;

  int colorBody;
  int colorWheel;
  int camp;
public:
  static void renderStatusTank(int y, Tank *t);
  Tank(int x, int y, int direction, int camp, int modelSel = MD_LHT);
  void draw();
  virtual void move(int direction = 0);
  Bullet *fire();
  void hit(int type, int srcCamp);
  ~Tank();
  friend class Render;
  friend class Adventure;
};

class AutoTank: public Tank {
private:
  int getDirection();
public:
  AutoTank(int x, int y, int modelSel = MD_LHT): Tank(x, y, D_DN, CP_EN, modelSel) {}
  void move(int direction = 0);
};


#endif