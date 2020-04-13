#include "bullet.h"
#include "common.h"
#include "map.h"
#include "level.h"
// extern elem_t Map[MAP_W][MAP_H];

char *Bullet::models[N_BULLET_MODEL] = {
  "○", "●", "◌",
};

int Bullet::bulletSpeed = 80;
std::list<Bullet *> Bullet::pool;
std::list<Bullet *> Bullet::Bullets;

void Bullet::draw() {
  Render::draw({F_WHT, B_TSP, Bullet::models[this->type]}, x, y);
}
bool Bullet::move() {
  if(getTime() < Bullet::bulletSpeed + lastMove) return false;
  lastMove = getTime();
  switch (this->direction) {
  case D_UP:{
    if(this->y > 0)
      --this->y;
    else
      return true;
    break;
  }
  case D_LT:{
    if(this->x > 0)
      --this->x;
    else
      return true;
    break;
  }
  case D_DN:{
    if(this->y < MAP_H - 1)
      ++this->y;
    else
      return true;
    break;
  }
  case D_RT:{
    if(this->x < MAP_W - 1)
      ++this->x;
    else
      return true;
    break;
  }
  }
  switch (Map::map[this->x][this->y].type) {
  case T_WAL: {
    Map::map[this->x][this->y] = {T_BNK, NULL}; 
    return true; 
  }
  case T_BNK: break;
  case T_GRS: break;
  case T_WTR: break;
  case T_STN: break;
  case T_DRW: {
    Map::map[x][y].data->hit(this->type, this->srcCamp);
    return true;
  }
  }
  return false;
}
