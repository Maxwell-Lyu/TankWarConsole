#ifndef __BULLET_H__
#define __BULLET_H__
#include <list>
#include <cstring>
#include <malloc.h>
#include "render.h"

enum {BL_NM, BL_AP, BL_HE};

class Bullet: public Drawable {
protected:
  static std::list<Bullet *> pool;
  static int bulletSpeed;
  // static std::list<Bullet *> pool;
  uint64_t lastMove = 0;
  int type = BL_NM;
public:
  static std::list<Bullet *> Bullets;
  Bullet(int x, int y, int direction): Drawable(x, y, direction) {}
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
    pool.push_back((Bullet *)p);
  }
  void draw();
  bool move();
};


#endif
