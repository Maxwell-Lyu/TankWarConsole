#include "game.h"
#include "level.h"
#include "conio.h"
#include "common.h"
#include "windows.h"
#include "map.h"
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
            menuSel = (menuSel + N_MENU - 1) % N_MENU;
          else if(ch == 80)
            menuSel = (menuSel + 1) % N_MENU;
          break;
        }
        case 13: {
          switch (menuSel) {
            case MN_ADV: {
              Map::loadMap();
              Level *l = new Adventure();
              int ret = l->run();
              l->showResult(ret);
              delete l;
              break;
            }
            case MN_COP: {
              Map::loadMap();
              Level *l = new Cooperation();
              int ret = l->run();
              l->showResult(ret);
              delete l;
              break;
            }
            case MN_ARN: {
              Map::loadMap();
              Level *l = new Arena();
              int ret = l->run();
              l->showResult(ret);
              delete l;
              break;
            }
            case MN_EDT: {
              Map::loadMap();
              Level *l = new MapEdit();
              int ret = l->run();
              l->showResult(ret);
              delete l;
              Map::saveMap();
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


