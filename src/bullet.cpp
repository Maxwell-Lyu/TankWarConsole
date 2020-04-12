#include "bullet.h"
#include "common.h"
#include "map.h"
// extern elem_t Map[MAP_W][MAP_H];

int Bullet::bulletSpeed = 200;
std::list<Bullet *> Bullet::pool;
std::list<Bullet *> Bullet::Bullets;

void Bullet::draw() {
  Render::draw({F_WHT, B_TSP, "弹"}, x, y);
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
  case T_BNK:
  case T_GRS:
  case T_WTR:
  case T_STN:
  case T_DRW: break;
  }
  if(Map::map[x][y].type == T_DRW) {
    Map::map[x][y].data->hit(this->type);
    return true;
  }
  return false;
}
