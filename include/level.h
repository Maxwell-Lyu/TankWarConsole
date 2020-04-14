#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "common.h"
#include "render.h"
#include "tank.h"
#include "base.h"
#include <list>
#include <tuple>

class Level {
protected:
  Tank *player1;
  Tank *player2;
  Base *base;
  // Tank *enemy[4];
  std::list<std::tuple<int, int, int> > waves;
  std::list<Tank *> enemies;
  int scoreP1;
  int scoreP2;
public:
  int type;
  static Level *currentLevel;
  std::list <std::tuple<int, Tank *, int> > events; 
  Level(int type);
  virtual int run() = 0;
  friend class Render;
  friend class Tank;
};

//  TODO: Add Game Class 
//  TODO: Add Game Pause and screed 
//  TODO: Add result more screens
class Adventure: public Level {
protected:
  uint64_t nextWave = 0;
  uint64_t nextPowerUp = 0;
public:
  Adventure(): Level(LV_AD1) {}
  void sendEnemy();
  void sendPowerUp();
  int run();
  void result();
};



#endif
