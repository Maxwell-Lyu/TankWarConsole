#include <thread>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "tank.h"
#include "render.h"

using namespace std;

int Render::fps = 50;

// extern elem_t Map[MAP_H][MAP_W];
extern std::list<Drawable *> Drawables;
extern std::list<Bullet *> Bullets;
int main() {
  system("chcp 65001");
  system("cls");
  Tank t(2, 2, D_UP);
  Tank t1(2, 6, D_UP);
  Render::run();
  Render::Drawables.emplace_back(&t);
  Render::Drawables.emplace_back(&t1);
  while(1) {
    if(kbhit()) {
      switch(getch()) {
      case 119: t.move(D_UP); break;
      case 97:  t.move(D_LT); break;
      case 115: t.move(D_DN); break;
      case 100: t.move(D_RT); break;
      case 32: {
        Bullet *blt = t.fire();
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

    Sleep(50);
  }

  // Sleep(2000);
  // t.move(D_UP);
  // while(1) {
  //   Sleep(1000);
  // }
  system("pause");
  return 0;
}