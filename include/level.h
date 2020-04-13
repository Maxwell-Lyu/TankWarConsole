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
  virtual void run() = 0;
  friend class Render;
};


class Adventure: public Level {
protected:
  int lastWave = 0;
  int waveSpeed = 5000;
public:
  Adventure(): Level(LV_AD1) {}
  void sendEnemy();
  void run();
};



#endif
