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

int main() {
  system("chcp 65001");
  system("cls");
  ManualTank t;
  Render::run();
  Render::Drawables.emplace_back(&t);
  while(1) {
    if(kbhit()) {
      switch(getch()) {
      case 119: t.move(D_UP); break;
      case 97:  t.move(D_LT); break;
      case 115: t.move(D_DN); break;
      case 100: t.move(D_RT); break;
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