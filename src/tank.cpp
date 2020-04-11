#include "tank.h"
#include <thread>
#include <windows.h>
#include <functional>
#include <conio.h>
#include <cmath>
#include <iostream>
#include "common.h"
extern elem_t Map[MAP_W][MAP_H];


bool Tank::canMove[6] = {true, true, false, false, false, false};

char *Tank::models[N_TANK_MODEL][4][9] = {{
  {" ▄", "▐▌" ,"▄ " ,"██" ,"▀▀" ,"██" ,"▀█" ,"▀▀" ,"█▀"},
  {" ▄", "██" ,"█▄" ,"■■" ,"█ " ,"█ " ," ▀" ,"██" ,"█▀"},
  {"▄█", "▄▄" ,"█▄" ,"██" ,"▄▄" ,"██" ," ▀" ,"▐▌" ,"▀ "},
  {"▄█", "██" ,"▄ " ," █" ," █" ,"■■" ,"▀█" ,"██" ,"▀ "},
}};


Tank::Tank(int x, int y, int direction): Drawable(x, y, direction)  {
  for (int x = this->x - 1; x <= this->x + 1; x++)
    for (int y = this->y - 1; y <= this->y + 1; y++)
      Map[x][y] = {T_DRW, this};
}

bool Tank::checkMove() {
  switch (direction) {
  case D_UP:
    return canMove[Map[x - 1][y - 2].type] && canMove[Map[x][y - 2].type] && canMove[Map[x + 1][y - 2].type];
  case D_LT:
    return canMove[Map[x - 2][y - 1].type] && canMove[Map[x - 2][y].type] && canMove[Map[x - 2][y + 1].type];
  case D_DN:
    return canMove[Map[x - 1][y + 2].type] && canMove[Map[x][y + 2].type] && canMove[Map[x + 1][y + 2].type];
  case D_RT:
    return canMove[Map[x + 2][y - 1].type] && canMove[Map[x + 2][y].type] && canMove[Map[x + 2][y + 1].type];
  }
  return false;
}



void Tank::draw() {
  switch(this->direction) {
  case D_UP: {
    Render::draw({F_WHT, B_BLK, models[modelSel][D_UP][0]}, x - 1, y - 1);
    Render::draw({F_GRN, B_BLK, models[modelSel][D_UP][1]}, x, y - 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_UP][2]}, x + 1, y - 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_UP][3]}, x - 1, y);
    Render::draw({F_GRN, B_BLK, models[modelSel][D_UP][4]}, x, y);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_UP][5]}, x + 1, y);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_UP][6]}, x - 1, y + 1);
    Render::draw({F_GRN, B_BLK, models[modelSel][D_UP][7]}, x, y + 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_UP][8]}, x + 1, y + 1);
    break;
  }
  case D_LT: {
    Render::draw({F_WHT, B_BLK, models[modelSel][D_LT][0]}, x - 1, y - 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_LT][1]}, x, y - 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_LT][2]}, x + 1, y - 1);
    Render::draw({F_GRN, B_BLK, models[modelSel][D_LT][3]}, x - 1, y);
    Render::draw({F_GRN, B_BLK, models[modelSel][D_LT][4]}, x, y);
    Render::draw({F_GRN, B_BLK, models[modelSel][D_LT][5]}, x + 1, y);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_LT][6]}, x - 1, y + 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_LT][7]}, x, y + 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_LT][8]}, x + 1, y + 1);
    break;
  }
  case D_DN: {
    Render::draw({F_WHT, B_BLK, models[modelSel][D_DN][0]}, x - 1, y - 1);
    Render::draw({F_GRN, B_BLK, models[modelSel][D_DN][1]}, x, y - 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_DN][2]}, x + 1, y - 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_DN][3]}, x - 1, y);
    Render::draw({F_GRN, B_BLK, models[modelSel][D_DN][4]}, x, y);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_DN][5]}, x + 1, y);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_DN][6]}, x - 1, y + 1);
    Render::draw({F_GRN, B_BLK, models[modelSel][D_DN][7]}, x, y + 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_DN][8]}, x + 1, y + 1);
    break;
  }
  case D_RT: {
    Render::draw({F_WHT, B_BLK, models[modelSel][D_RT][0]}, x - 1, y - 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_RT][1]}, x, y - 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_RT][2]}, x + 1, y - 1);
    Render::draw({F_GRN, B_BLK, models[modelSel][D_RT][3]}, x - 1, y);
    Render::draw({F_GRN, B_BLK, models[modelSel][D_RT][4]}, x, y);
    Render::draw({F_GRN, B_BLK, models[modelSel][D_RT][5]}, x + 1, y);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_RT][6]}, x - 1, y + 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_RT][7]}, x, y + 1);
    Render::draw({F_WHT, B_BLK, models[modelSel][D_RT][8]}, x + 1, y + 1);
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
      Map[x][y] = {T_BNK, NULL};
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
      Map[x][y] = {T_DRW, this};
}

Bullet *Tank::fire() {
  if(getTime() < speedFire + lastFire) return NULL;
  lastFire = getTime();
  Bullet *blt;
  switch(this->direction) {
  case D_UP:
    blt = new Bullet(this->x, this->y - 1, this->direction);
    break;
  case D_LT:
    blt = new Bullet(this->x - 1, this->y, this->direction);
    break;
  case D_DN:
    blt = new Bullet(this->x, this->y + 1, this->direction);
    break;
  case D_RT:
    blt = new Bullet(this->x + 1, this->y, this->direction);
    break;
  }
  return blt;
}

void Tank::hit(int type) {
  switch (type) {
  case BL_NM: this->life -= 100; return;
  case BL_AP: this->life -= 200; return;
  case BL_HE: this->life -= 400; return;
  }
}