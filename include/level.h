#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "common.h"
#include "render.h"
#include "tank.h"
#include <list>
#include <tuple>

class Level {
protected:
  Tank *player1;
  Tank *player2;
  Tank *enemy[4];
  int scoreP1;
  int scoreP2;
  int type;
public:
  static Level *currentLevel;
  std::list <std::tuple<int, Tank *, int> > events; 
  Level(int type);
  virtual void run() = 0;
  friend class Render;
};


class Adventure: public Level {
public:
  Adventure(): Level(LV_AD1) {}
  void run();
};



#endif
