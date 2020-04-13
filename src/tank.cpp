#include "tank.h"
#include <thread>
#include <windows.h>
#include <functional>
#include <conio.h>
#include <cmath>
#include <iostream>
#include "common.h"
#include "map.h"
#include "level.h"
// extern elem_t Map::map[MAP_W][MAP_H];


bool Tank::canMove[6] = {true, true, false, false, false, false};
int Tank::lifeMaxVals[N_TANK_MODEL] { 1000, 1000, 1000, 2000 };
int Tank::speedMoveVals[N_TANK_MODEL] { 200, 100, 200, 200 };
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


Tank::Tank(int x, int y, int direction, int camp, int modelSel): Drawable(x, y, direction), modelSel(modelSel), camp(camp), nLife(1)  {
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
void Tank::move(int direction) {
  if(direction != this->direction) {
    this->direction = direction;
    return;
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
    for (int y = this->y - 1; y <= this->y + 1; y++)
      Map::map[x][y] = {T_DRW, this};
}

Bullet *Tank::fire() {
  if(getTime() < speedFire + lastFire) return NULL;
  lastFire = getTime();
  Bullet *blt;
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
  if(Level::currentLevel->type != LV_ARN && !(this->camp & srcCamp)) return;
  switch (type) {
  case BL_NM: this->life -= 100; break;
  case BL_AP: this->life -= 200; break;
  case BL_HE: this->life -= 400; break;
  }
  if(this->life <= 0)
    Level::currentLevel->events.push_back(std::make_tuple(EV_DST_TK, this, srcCamp));
}

Tank::~Tank() {
  for (int x = this->x - 1; x <= this->x + 1; x++)
    for (int y = this->y - 1; y <= this->y + 1; y++)
      Map::map[x][y] = {T_BNK, NULL};
}