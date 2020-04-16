#include "tank.h"
#include <thread>
#include <windows.h>
#include <functional>
#include <conio.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "common.h"
#include "map.h"
#include "level.h"
// extern elem_t Map::map[MAP_W][MAP_H];


bool Tank::canMove[N_TERRIAN] = {true, true, false, false, false, false, true };
int Tank::lifeMaxVals[N_TANK_MODEL] { 1000, 1000, 1000, 2000 };
int Tank::speedMoveVals[N_TANK_MODEL] { 200, 150, 200, 200 };
int Tank::speedFireVals[N_TANK_MODEL] { 400, 400, 200, 400 };
int Tank::weaponVals[N_TANK_MODEL] { BL_NM, BL_NM, BL_NM, BL_AP};


char *Tank::models[N_TANK_MODEL][4][9] = {{
  {" ▄", "▐▌" ,"▄ " ,"██" ,"▀▀" ,"██" ,"▀█" ,"▀▀" ,"█▀"},
  {" ▄", "██" ,"█▄" ,"■■" ,"█ " ,"█ " ," ▀" ,"██" ,"█▀"},
  {"▄█", "▄▄" ,"█▄" ,"██" ,"▄▄" ,"██" ," ▀" ,"▐▌" ,"▀ "},
  {"▄█", "██" ,"▄ " ," █" ," █" ,"■■" ,"▀█" ,"██" ,"▀ "},
}, {
  {" ▄", "▐▌" ,"▄ " ,"██" ,"██" ,"██" ,"▀█" ,"  " ,"█▀"},
  {" ▄", "██" ,"█▄" ,"■■" ,"██" ,"  " ," ▀" ,"██" ,"█▀"},
  {"▄█", "  " ,"█▄" ,"██" ,"██" ,"██" ," ▀" ,"▐▌" ,"▀ "},
  {"▄█", "██" ,"▄ " ,"  " ,"██" ,"■■" ,"▀█" ,"██" ,"▀ "},
}, {
  {" ▄", "▐▌" ,"▄ " ,"██" ,"▐▌" ,"██" ,"▀█" ,"▀▀" ,"█▀"},
  {" ▄", "██" ,"█▄" ,"■■" ,"■■" ,"█ " ," ▀" ,"██" ,"█▀"},
  {"▄█", "▄▄" ,"█▄" ,"██" ,"▐▌" ,"██" ," ▀" ,"▐▌" ,"▀ "},
  {"▄█", "██" ,"▄ " ," █" ,"■■" ,"■■" ,"▀█" ,"██" ,"▀ "},
}, {
  {" ▄", "▐▌" ,"▄ " ,"██" ,"██" ,"██" ,"▀█" ,"▄▄" ,"█▀"},
  {" ▄", "██" ,"█▄" ,"■■" ,"██" ," █" ," ▀" ,"██" ,"█▀"},
  {"▄█", "▀▀" ,"█▄" ,"██" ,"██" ,"██" ," ▀" ,"▐▌" ,"▀ "},
  {"▄█", "██" ,"▄ " ,"█ " ,"██" ,"■■" ,"▀█" ,"██" ,"▀ "},
}, };


Tank::Tank(int x, int y, int direction, int camp, int modelSel): Drawable(x, y, direction), modelSel(modelSel), nLife(1), camp(camp)  {
  this->life = Tank::lifeMaxVals[modelSel];
  this->lifeMax = Tank::lifeMaxVals[modelSel];
  this->speedMove = Tank::speedMoveVals[modelSel];
  this->speedFire = Tank::speedFireVals[modelSel];
  this->weapon = Tank::weaponVals[modelSel];
  this->lastMove = 0;
  this->lastFire = 0;
  switch(camp) {
  case CP_P1: {
    this->colorBody = F_GRN;
    this->colorWheel = F_WHT;
    break;
  }
  case CP_P2: {
    this->colorBody = F_BLU;
    this->colorWheel = F_WHT;
    break;
  }
  case CP_EN: {
    this->colorBody = F_RED;
    this->colorWheel = F_WHT;
    break;
  }
  case CP_BS: {
    this->colorBody = F_YLW;
    this->colorWheel = F_WHT;
    break;
  }
  }
  for (int x = this->x - 1; x <= this->x + 1; x++)
    for (int y = this->y - 1; y <= this->y + 1; y++)
      Map::map[x][y] = {T_DRW, this};
}

bool Tank::checkMove() {
  switch (direction) {
  case D_UP:
    return canMove[Map::map[x - 1][y - 2].type] && canMove[Map::map[x][y - 2].type] && canMove[Map::map[x + 1][y - 2].type];
  case D_LT:
    return canMove[Map::map[x - 2][y - 1].type] && canMove[Map::map[x - 2][y].type] && canMove[Map::map[x - 2][y + 1].type];
  case D_DN:
    return canMove[Map::map[x - 1][y + 2].type] && canMove[Map::map[x][y + 2].type] && canMove[Map::map[x + 1][y + 2].type];
  case D_RT:
    return canMove[Map::map[x + 2][y - 1].type] && canMove[Map::map[x + 2][y].type] && canMove[Map::map[x + 2][y + 1].type];
  }
  return false;
}



void Tank::draw() {
  switch(this->direction) {
  case D_UP: {
    Render::draw({colorWheel, B_BLK, models[modelSel][D_UP][0]}, x - 1, y - 1);
    Render::draw({colorBody, B_BLK, models[modelSel][D_UP][1]}, x, y - 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_UP][2]}, x + 1, y - 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_UP][3]}, x - 1, y);
    Render::draw({colorBody, B_BLK, models[modelSel][D_UP][4]}, x, y);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_UP][5]}, x + 1, y);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_UP][6]}, x - 1, y + 1);
    Render::draw({colorBody, B_BLK, models[modelSel][D_UP][7]}, x, y + 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_UP][8]}, x + 1, y + 1);
    break;
  }
  case D_LT: {
    Render::draw({colorWheel, B_BLK, models[modelSel][D_LT][0]}, x - 1, y - 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_LT][1]}, x, y - 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_LT][2]}, x + 1, y - 1);
    Render::draw({colorBody, B_BLK, models[modelSel][D_LT][3]}, x - 1, y);
    Render::draw({colorBody, B_BLK, models[modelSel][D_LT][4]}, x, y);
    Render::draw({colorBody, B_BLK, models[modelSel][D_LT][5]}, x + 1, y);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_LT][6]}, x - 1, y + 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_LT][7]}, x, y + 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_LT][8]}, x + 1, y + 1);
    break;
  }
  case D_DN: {
    Render::draw({colorWheel, B_BLK, models[modelSel][D_DN][0]}, x - 1, y - 1);
    Render::draw({colorBody, B_BLK, models[modelSel][D_DN][1]}, x, y - 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_DN][2]}, x + 1, y - 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_DN][3]}, x - 1, y);
    Render::draw({colorBody, B_BLK, models[modelSel][D_DN][4]}, x, y);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_DN][5]}, x + 1, y);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_DN][6]}, x - 1, y + 1);
    Render::draw({colorBody, B_BLK, models[modelSel][D_DN][7]}, x, y + 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_DN][8]}, x + 1, y + 1);
    break;
  }
  case D_RT: {
    Render::draw({colorWheel, B_BLK, models[modelSel][D_RT][0]}, x - 1, y - 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_RT][1]}, x, y - 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_RT][2]}, x + 1, y - 1);
    Render::draw({colorBody, B_BLK, models[modelSel][D_RT][3]}, x - 1, y);
    Render::draw({colorBody, B_BLK, models[modelSel][D_RT][4]}, x, y);
    Render::draw({colorBody, B_BLK, models[modelSel][D_RT][5]}, x + 1, y);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_RT][6]}, x - 1, y + 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_RT][7]}, x, y + 1);
    Render::draw({colorWheel, B_BLK, models[modelSel][D_RT][8]}, x + 1, y + 1);
    break;
  }
  }
};
#define SNAPPY_MOVE
void Tank::move(int direction) {
  if(direction != this->direction) {
    this->direction = direction;
#ifndef SNAPPY_MOVE
    return;
#endif
  }
  if(getTime() < speedMove + lastMove) return;
  lastMove = getTime();
  for (int x = this->x - 1; x <= this->x + 1; x++)
    for (int y = this->y - 1; y <= this->y + 1; y++)
      Map::map[x][y] = {T_BNK, NULL};
  switch (this->direction) {
  case D_UP:{
    if(this->y > 1 && checkMove())
      --this->y;
    break;
  }
  case D_LT:{
    if(this->x > 1 && checkMove())
      --this->x;
    break;
  }
  case D_DN:{
    if(this->y < MAP_H - 2 && checkMove())
      ++this->y;
    break;
  }
  case D_RT:{
    if(this->x < MAP_W - 2 && checkMove())
      ++this->x;
    break;
  }
  }
  for (int x = this->x - 1; x <= this->x + 1; x++)
    for (int y = this->y - 1; y <= this->y + 1; y++) {
      if(Map::map[x][y].type == T_PWU) {
        Level::currentLevel->events.push_back(std::make_tuple(EV_GET_PW, this, -1));
        Map::map[x][y].data->hit(this->weapon, this->camp);
      } else
        Map::map[x][y] = {T_DRW, this};
    }
}

Bullet *Tank::fire() {
  if(getTime() < speedFire + lastFire) return nullptr;
  lastFire = getTime();
  Bullet *blt = nullptr;
  switch(this->direction) {
  case D_UP:
    blt = new Bullet(this->x, this->y - 1, this->direction, this->weapon, this->camp);
    break;
  case D_LT:
    blt = new Bullet(this->x - 1, this->y, this->direction, this->weapon, this->camp);
    break;
  case D_DN:
    blt = new Bullet(this->x, this->y + 1, this->direction, this->weapon, this->camp);
    break;
  case D_RT:
    blt = new Bullet(this->x + 1, this->y, this->direction, this->weapon, this->camp);
    break;
  }
  return blt;
}

void Tank::hit(int type, int srcCamp) {
  if(this->camp == srcCamp) return;
  if(Level::currentLevel->type != LV_ARN && !(this->camp & srcCamp)) return;
  this->weapon = this->weapon == BL_NM ? BL_NM : this->weapon - 1;
  switch (type) {
  case BL_NM: this->life -= 100; break;
  case BL_AP: this->life -= 200; break;
  case BL_HE: this->life -= 400; break;
  }
  Level::currentLevel->events.push_back(std::make_tuple(EV_HIT_TK, this, srcCamp));
  if(this->life <= 0) {
    if((--this->nLife) > 0)
      this->life = this->lifeMax;
    else
      Level::currentLevel->events.push_back(std::make_tuple(EV_DST_TK, this, srcCamp));
  }
}

Tank::~Tank() {
  for (int x = this->x - 1; x <= this->x + 1; x++)
    for (int y = this->y - 1; y <= this->y + 1; y++)
      Map::map[x][y] = {T_BNK, NULL};
}


int AutoTank::getDirection() {
  switch(this->direction) {
    case D_UP: return D_LT;
    case D_LT: return D_DN;
    case D_DN: return D_RT;
    case D_RT: return D_UP;
  }
  return D_UP;
}

void AutoTank::move(int direction) {
  if(getTime() < speedMove + lastMove) return;
  lastMove = getTime();
  for (int x = this->x - 1; x <= this->x + 1; x++)
    for (int y = this->y - 1; y <= this->y + 1; y++)
      Map::map[x][y] = {T_BNK, NULL};
  switch (this->direction) {
  case D_UP:{
    if(this->y > 1 && checkMove())
      --this->y;
    else
      this->direction = getDirection();
    break;
  }
  case D_LT:{
    if(this->x > 1 && checkMove())
      --this->x;
    else
      this->direction = getDirection();
    break;
  }
  case D_DN:{
    if(this->y < MAP_H - 2 && checkMove())
      ++this->y;
    else
      this->direction = getDirection();
    break;
  }
  case D_RT:{
    if(this->x < MAP_W - 2 && checkMove())
      ++this->x;
    else
      this->direction = getDirection();
    break;
  }
  }
  for (int x = this->x - 1; x <= this->x + 1; x++)
    for (int y = this->y - 1; y <= this->y + 1; y++) {
      if(Map::map[x][y].type == T_PWU) {
        Level::currentLevel->events.push_back(std::make_tuple(EV_GET_PW, this, -1));
        Map::map[x][y].data->hit(this->weapon, this->camp);
      } else
        Map::map[x][y] = {T_DRW, this};
    }
}



void Tank::renderStatusTank(int y, Tank *t) {
  std::cout << "\033[1m";
  std::cout << "\033[" << t->colorBody << "m\033[" << y + 1 << ";" << STATUS_START_X << "H";
  switch(t->camp) {
    case CP_P1: std::cout << "PLAYER 1"; break;
    case CP_P2: std::cout << "PLAYER 2"; break;
    case CP_BS: std::cout << "BASE TO PROTECT"; break;
    case CP_EN: {
      std::cout << "ENEMY   "; 
      std::cout << Tank::models[t->modelSel][D_RT][3] << Tank::models[t->modelSel][D_RT][4] << Tank::models[t->modelSel][D_RT][5]; break;
    }
  }
  std::cout << "\033[0m\033[1m";
  std::cout << "\033[" << y + 2 << ";" << STATUS_START_X << "HHP [";
    int n = t->life * 10 / t->lifeMax;
  for (int i = 0; i < n; i++) std::cout << "■";
  for (int i = n; i < 10; i++) std::cout << " ";
  std::cout << "\033[" << y + 2 << ";" << STATUS_START_X + 14 <<"H]";
  if(t->camp == CP_P1 || t->camp == CP_P2)
    std::cout << "\033[" << y + 3 << ";" << STATUS_START_X << "HWP [" << Bullet::models[t->weapon] << "]  LF [" << std::setw(2) << std::setfill('0') << t->nLife << "]";
  if(t->camp == CP_P1)
    std::cout << "\033[" << y + 4 << ";" << STATUS_START_X << "HPT [" << std::setw(10) << std::setfill(' ') << Level::currentLevel->scoreP1 << "] ";
  if(t->camp == CP_P2)
    std::cout << "\033[" << y + 4 << ";" << STATUS_START_X << "HPT [" << std::setw(10) << std::setfill(' ') << Level::currentLevel->scoreP2 << "] ";
    
}




Cursor::Cursor(): Tank(MAP_W / 2, MAP_H / 2, D_UP, CP_P1, MD_LHT) {
  this->weapon = T_BNK;
  this->speedMove = 200;
  for (int x = this->x - 1; x <= this->x + 1; x++)
    for (int y = this->y - 1; y <= this->y + 1; y++)
      Map::map[x][y] = {T_BNK, nullptr};
}

void Cursor::move(int direction) {
  // for (int x = this->x - 1; x <= this->x + 1; x++)
  //   for (int y = this->y - 1; y <= this->y + 1; y++)
  //     Render::draw({F_BLK, B_BLK, "  "}, x, y);
  switch (direction) {
  case D_UP:{
    if(this->y > 0)
      --this->y;
    break;
  }
  case D_LT:{
    if(this->x > 0)
      --this->x;
    break;
  }
  case D_DN:{
    if(this->y < MAP_H - 1)
      ++this->y;
    break;
  }
  case D_RT:{
    if(this->x < MAP_W - 1)
      ++this->x;
    break;
  }
  }
}

void Cursor::draw() {
  uint64_t t = getTime();
  if(t > speedMove + speedMove + lastMove)
    lastMove = t;
  else if(t > speedMove + lastMove)
    Render::draw({F_WHT, B_BLK, "▒▒"}, x, y);
  else 
    Render::draw({F_WHT, B_BLK, "  "}, x, y);
}


Bullet *Cursor::fire() {
  Map::map[x][y] = {this->weapon, nullptr};
  return nullptr;
}