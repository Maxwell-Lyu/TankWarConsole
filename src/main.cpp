#include <thread>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "tank.h"
#include "render.h"
#include "common.h"
#include "level.h"
using namespace std;

int Render::fps = 25;

int main() {
  system("chcp 65001");
  system("mode con cols=100 lines=40");
  system("cls");
  Render::run();
  Level *level = new Arena();
  int ret = level->run();
  level->showResult(ret);
  // Sleep(2000);
  // t.move(D_UP);
  // while(1) {
  //   Sleep(1000);
  // }
  system("pause");
  return 0;
}