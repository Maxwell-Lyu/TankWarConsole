#include <thread>
#include <iostream>
#include "game.h"
using namespace std;

int Render::fps = 25;

int main() {
  system("chcp 65001");
  system("mode con cols=100 lines=40");
  system("cls");
  Game::run();
  system("pause");
  return 0;
}