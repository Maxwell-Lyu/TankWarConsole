#include "render.h"
// #include <iostream>
#include <windows.h>
#include <thread>
#include "map.h"
#include "level.h"
#include <iostream>
#include <iomanip>
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
            draw({F_WHT, B_GRN, "草"}, x, y); break;
          case T_WTR:
            draw({F_WHT, B_BLU, "水"}, x, y); break;
          case T_WAL:
            draw({F_WHT, B_YLW, "墙"}, x, y); break;
          case T_STN:
            draw({F_WHT, B_MGT, "石"}, x, y); break;
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
  case LV_AD2: renderStatusTank(23, Level::currentLevel->player2);
  case LV_AD1: {
    renderStatusTank(18, Level::currentLevel->player1);
    renderStatusTank(15, Level::currentLevel->base);
    int line = 7;
    for (auto it = Level::currentLevel->enemies.begin(); it != Level::currentLevel->enemies.end(); it++) {
      renderStatusTank(line, *it);
      line += 2;
    }
    for (; line < 15; line++)
      std::cout << "\033[" << line + 1 << ";63H                ";
    renderStatusEnemy(5);
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
void Render::renderStatusTank(int y, Tank *t) {
  std::cout << "\033[1m";
  std::cout << "\033[" << t->colorBody << "m\033[" << y + 1 << ";63H";
  switch(t->camp) {
    case CP_P1: std::cout << "PLAYER 1"; break;
    case CP_P2: std::cout << "PLAYER 2"; break;
    case CP_BS: std::cout << "BASE TO PROTECT"; break;
    case CP_EN: {
      std::cout << "ENEMY   "; 
      std::cout << Tank::models[t->modelSel][D_RT][3] << Tank::models[t->modelSel][D_RT][4] << Tank::models[t->modelSel][D_RT][5]; break;
    }
  }
  std::cout << "\033[0m";
  std::cout << "\033[" << y + 2 << ";63HHP [";
    int n = t->life * 10 / t->lifeMax;
  for (int i = 0; i < n; i++) std::cout << "■";
  for (int i = n; i < 10; i++) std::cout << " ";
  std::cout << "\033[" << y + 2 << ";77H]";
  if(t->camp == CP_P1 || t->camp == CP_P2)
    std::cout << "\033[" << y + 3 << ";63HWP [" << Bullet::models[t->weapon] << "]  LF [" << std::setw(2) << std::setfill('0') << t->nLife << "]";
  if(t->camp == CP_P1)
    std::cout << "\033[" << y + 4 << ";63HPT [" << std::setw(10) << std::setfill(' ') << Level::currentLevel->scoreP1 << "] ";
  if(t->camp == CP_P2)
    std::cout << "\033[" << y + 4 << ";63HPT [" << std::setw(10) << std::setfill(' ') << Level::currentLevel->scoreP2 << "] ";
    
}
void Render::renderStatusEnemy(int y) {
  std::cout << "\033[31;1m\033[" << y + 1 << ";63HENEMY LEFT [\033[37;1m" << std::setw(2) << std::setfill('0') << Level::currentLevel->waves.size() << "\033[31;1m]";
}

void Render::run() {
  std::thread t(&Render::thrRender);
  t.detach();
  // std::thread t2(&Render::refresh);
  // t2.detach();
}
