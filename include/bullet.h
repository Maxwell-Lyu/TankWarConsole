#ifndef __BULLET_H__
#define __BULLET_H__
#include <list>
#include <cstring>
#include <malloc.h>
#include "render.h"
#include "common.h"


class Bullet: public Drawable {
protected:
  static std::list<void *> pool;
  static int bulletSpeed;
  static char *models[N_BULLET_MODEL];
  // static std::list<Bullet *> pool;
  uint64_t lastMove;
public:
  int type;
  int srcCamp;
  int toRemove;
  static std::list<Bullet *> Bullets;
  Bullet(int x, int y, int direction, int type, int srcCamp): Drawable(x, y, direction), lastMove(0), type(type), srcCamp(srcCamp), toRemove(0) {}
	void *operator new(size_t size) {	
    if(pool.empty()) {
      void *p = malloc(size);
      memset(p, 0, size);
      return p;
    }
    else {
      auto blt = pool.front();
      pool.pop_front();
      return blt;
    }
	}
  void operator delete(void *p) {
    pool.push_back(p);
  }
  void draw();
  bool move();
  friend class Render;
  friend class Level;
  friend class Tank;
};


#endif
