#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "common.h"
#include "render.h"
#include "tank.h"
#include "base.h"
#include <list>
#include <tuple>
#include <mutex>

class Level {
protected:
  Tank *player1;
  Tank *player2;
  Base *base;
  // Tank *enemy[4];
  std::list<std::tuple<int, int, int> > waves;
  std::list<Tank *> enemies;
  std::list<Tank *> deadEnemies;
  int scoreP1;
  int scoreP2;
  int result;
public:
  std::mutex mutex;
  int type;
  static Level *currentLevel;
  std::list <std::tuple<int, Tank *, int> > events; 
  Level(int type);
  virtual int run() = 0;
  void showResult(int ret);
  virtual void renderResult() = 0;
  friend class Render;
  friend class Tank;
  virtual ~Level();
};

class Adventure: public Level {
protected:
  uint64_t nextWave = 0;
  uint64_t nextPowerUp = 0;
public:
  Adventure(): Level(LV_ADV) {}
  void sendEnemy();
  void sendPowerUp();
  int run();
  void renderResult();
};

class Cooperation: public Level {
protected:
  uint64_t nextWave = 0;
  uint64_t nextPowerUp = 0;
public:
  Cooperation(): Level(LV_COP) {}
  void sendEnemy();
  void sendPowerUp();
  int run();
  void renderResult();
};



class Arena: public Level {
protected:
  uint64_t nextPowerUp = 0;
public:
  Arena(): Level(LV_ARN) {}
  void sendPowerUp();
  int run();
  void renderResult();
};

class MapEdit: public Level {
public:
  MapEdit(): Level(LV_EDT) {}
  int run();
  void renderResult();
};

#endif
