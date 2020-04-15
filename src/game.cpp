#include "game.h"
#include "level.h"
#include "conio.h"
#include "common.h"
#include "windows.h"
int Game::menuSel = 0;


void Game::run() {
  Render::run();
  Render::scene = SC_WLC;
  while(1) {
    Sleep(50);
    if(kbhit()) {
      switch (getch()) {
        case 224: {
          int ch = getch();
          if(ch == 72)
            menuSel = (menuSel + 3) % 4;
          else if(ch == 80)
            menuSel = (menuSel + 1) % 4;
          break;
        }
        case 13: {
          switch (menuSel) {
            case MN_ADV: {
              Level *l = new Adventure();
              int ret = l->run();
              l->showResult(ret);
              break;
            }
            case MN_COP: {
              Level *l = new Cooperation();
              int ret = l->run();
              l->showResult(ret);
              break;
            }
            case MN_ARN: {
              Level *l = new Arena();
              int ret = l->run();
              l->showResult(ret);
              break;
            }
            case MN_EXT: {
              return;
              break;
            }
            default: {
              break;
            }
          }
          break;
        }
      }
    }
  }
}


