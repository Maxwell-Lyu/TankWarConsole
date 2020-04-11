#include "tank.h"
#include <thread>
#include <windows.h>
#include <functional>
#include <conio.h>
#include <cmath>
#include <iostream>
#include <sys/timeb.h>

uint64_t getTime() {
  timeb time;
  ftime(&time);
  return time.time * 1000 + time.millitm;
}
extern elem_t Map[MAP_W][MAP_H];


bool Tank::canMove[6] = { false, true, true, false, false, false};

char *Tank::models[N_TANK_MODEL][4][9] = {{
  {" ▄", "▐▌" ,"▄ " ,"██" ,"▀▀" ,"██" ,"▀█" ,"▀▀" ,"█▀"},
  {"轮", "轮" ,"轮" ,"■■" ,"仓" ,"尾" ,"轮" ,"轮" ,"轮"},
  {"轮", "尾" ,"轮" ,"●○" ,"☼ " ,"轮" ,"  " ,"▲▲" ,"轮"},
  {"轮", "轮" ,"轮" ,"炮" ,"仓" ,"尾" ,"轮" ,"轮" ,"轮"},
}};


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
}



void ManualTank::draw() {
  Render::draw({F_WHT, B_BLK, models[modelSel][this->direction][0]}, x - 1, y - 1);
  Render::draw({F_GRN, B_BLK, models[modelSel][this->direction][1]}, x, y - 1);
  Render::draw({F_WHT, B_BLK, models[modelSel][this->direction][2]}, x + 1, y - 1);
  Render::draw({F_WHT, B_BLK, models[modelSel][this->direction][3]}, x - 1, y);
  Render::draw({F_GRN, B_BLK, models[modelSel][this->direction][4]}, x, y);
  Render::draw({F_WHT, B_BLK, models[modelSel][this->direction][5]}, x + 1, y);
  Render::draw({F_WHT, B_BLK, models[modelSel][this->direction][6]}, x - 1, y + 1);
  Render::draw({F_GRN, B_BLK, models[modelSel][this->direction][7]}, x, y + 1);
  Render::draw({F_WHT, B_BLK, models[modelSel][this->direction][8]}, x + 1, y + 1);
};
void ManualTank::move(int direction) {
  if(direction != this->direction) {
    this->direction = direction;
    return;
  }
  if(getTime() < speed + lastMove) return;
  lastMove = getTime();
  Map[this->x][this->y] = {T_BNK, NULL};
  switch (this->direction) {
  case D_UP:{
    if(this->y > 1 && checkMove())
      Map[this->x][--this->y] = {T_DRW, this};
    break;
  }
  case D_LT:{
    if(this->x > 1 && checkMove())
      Map[--this->x][this->y] = {T_DRW, this};
    break;
  }
  case D_DN:{
    if(this->y < MAP_H - 2 && checkMove())
      Map[this->x][++this->y] = {T_DRW, this};
    break;
  }
  case D_RT:{
    if(this->x < MAP_W - 2 && checkMove())
      Map[++this->x][this->y] = {T_DRW, this};
    break;
  }
  }
}
