#include "level.h"
#include "common.h"
#include "render.h"
#include "bullet.h"
#include "tank.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <list>
#include <algorithm>

Level *Level::currentLevel;


Level::Level(int type): type(type), scoreP1(0), scoreP2(0) {
  Level::currentLevel = this;
  switch (type) {
  case LV_AD1: {
    player1 = new Tank(5, 28, D_UP, CP_P1, MD_LHT);
    player2 = nullptr;
    scoreP1 = 0;
    scoreP2 = 0;
    Render::Drawables.push_back(player1);
    Render::Drawables.push_back(player2 = new Tank(5, 5, D_UP, CP_EN, MD_LHT));
    break;
  }
  default:
    break;
  }
}

void Adventure::run() {
  Render::scene = SC_GRN;
  while(1) {
    if(kbhit()) {
      switch(getch()) {
      case 119: player1->move(D_UP); break;
      case 97:  player1->move(D_LT); break;
      case 115: player1->move(D_DN); break;
      case 100: player1->move(D_RT); break;
      case 32: {
        Bullet *blt = player1->fire();
        if(blt != nullptr) {
          Render::Drawables.emplace_back(blt);
          Bullet::Bullets.emplace_back(blt);
        }
        break;
      } 
      }
    }
    for(auto it = Bullet::Bullets.begin(); it != Bullet::Bullets.end();) {
      Bullet *blt = *it;
      if(blt->move()) {
          it = Bullet::Bullets.erase(it);
          Render::Drawables.remove(blt);
          delete blt;
      }
      else {
        ++it;
      }
    }
    for(auto it = events.begin(); it != events.end();) {
      auto e = *it;
      switch(std::get<0>(e)) {
        case EV_DST_TK: {
          auto dest = std::get<1>(e);
          auto src = std::get<2>(e);
          Render::Drawables.remove(dest);
          dest->~Tank();
          if(dest == player1) {
            return;
          }
          else {
            scoreP1 += 1000;
          }
        }
      }
      it = events.erase(it);
    }
    Sleep(50);
  }
}