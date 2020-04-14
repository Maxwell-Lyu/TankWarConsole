#include "render.h"
// #include <iostream>
#include <windows.h>
#include <thread>
#include "map.h"
#include "level.h"
#include <iostream>
#include <iomanip>
#include "assets.h"
std::list<Drawable *> Render::Drawables;
pixel_t Render::vBuf[MAP_H][MAP_W];
int Render::scene;
// extern elem_t Map[MAP_W][MAP_H];


void Render::refresh(){
  for (register int x = 0; x < MAP_W; x++)
    for (register int y = 0; y < MAP_H; y++)
      std::cout << "\033[" << vBuf[x][y].colorFG <<  ";" << vBuf[x][y].colorBG << "m\033[" << y + 1 << ";" << x * 2 + 1 << "H" << vBuf[x][y].val;  
}

void Render::thrRender() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(0);
  std::cout<<"\033[?25l";
  register elem_t elem;
  while(1) {
    switch (scene) {
    case SC_GRN: {
      for (int x = 0; x < MAP_W; x++)
        for (int y = 0; y < MAP_H; y++) {
          elem = Map::map[x][y];
          switch (elem.type) {
          case T_DRW:
            break;
          case T_GRS:
            draw({F_WHT, B_GRN, "WW"}, x, y); break;
          case T_WTR:
            draw({F_BLU, B_BLK, "░░"}, x, y); break;
          case T_WAL:
            draw({F_YLW, B_BLK, "▓▓"}, x, y); break;
          case T_STN:
            draw({F_WHT, B_YLW, "╪╪"}, x, y); break;
          case T_BNK:
            draw({F_WHT, B_BLK, "  "}, x, y); break;
          }
        }
      for(auto &drawable: Drawables)
        drawable->draw();
      renderStatus();
      refresh();
      break;
    }
    case SC_GPS: {
      break;
    }
    case SC_GRD: {
      Assets::renderDight(23, 17, F_WHT, 3);
      Sleep(1000);
      Assets::renderDight(23, 17, F_WHT, 2);
      Sleep(1000);
      Assets::renderDight(23, 17, F_WHT, 1);
      Sleep(1000);
      Assets::renderDight(23, 17, F_WHT, 0);
      break;
    }
    case SC_GFN: {
      break;
    }
    case SC_WLC: {
      break;
    }
    case SC_HLP: {
      break;
    }
    default:
      break;
    }
    Sleep(fps);
  }
}

void Render::renderStatus() {
  switch (Level::currentLevel->type) {
  case LV_AD2: Tank::renderStatusTank(STATUS_START_Y + 19, Level::currentLevel->player2);
  case LV_AD1: {
    Tank::renderStatusTank(STATUS_START_Y + 14, Level::currentLevel->player1);
    Tank::renderStatusTank(STATUS_START_Y + 11, Level::currentLevel->base);
    int line = STATUS_START_Y + 2;
    for (auto it = Level::currentLevel->enemies.begin(); it != Level::currentLevel->enemies.end(); it++) {
      Tank::renderStatusTank(line, *it);
      line += 2;
    }
    for (; line < STATUS_START_Y + 10; line++)
      std::cout << "\033[" << line + 1 << ";" << STATUS_START_X << "H                ";
    renderStatusEnemy(STATUS_START_Y);
    break;
  }
  case LV_ARN:
    
    break;
  
  default:
    break;
  }
  // renderStatusTank(10, Level::currentLevel->player1);
  // switch (Level::currentLevel->type) {
  // case LV_AD1: {

  // }
  // default:
  //   break;
  // }
}
void Render::renderStatusEnemy(int y) {
  std::cout << "\033[31;1m\033[" << y + 1 << ";" << STATUS_START_X << "HENEMY LEFT [\033[37;1m" << std::setw(2) << std::setfill('0') << Level::currentLevel->waves.size() << "\033[31;1m]";
}

void Render::run() {
  std::thread t(&Render::thrRender);
  t.detach();
  // std::thread t2(&Render::refresh);
  // t2.detach();
}
