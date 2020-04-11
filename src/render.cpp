#include "render.h"
// #include <iostream>
#include <windows.h>
#include <thread>


std::list<Drawable *> Drawables;


elem_t Map[MAP_W][MAP_H] = {
  { {T_WAL, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_WTR, NULL}, },
  { {T_GRS, NULL}, {T_GRS, NULL}, {T_BNK, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, },
  { {T_GRS, NULL}, {T_GRS, NULL}, {T_BNK, NULL}, {T_BNK, NULL}, {T_GRS, NULL}, },
  { {T_GRS, NULL}, {T_GRS, NULL}, {T_BNK, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, },
  { {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, },
};


void Render::refresh(){
  for (int x = 0; x < MAP_W; x++)
    for (int y = 0; y < MAP_H; y++)
      std::cout << "\033[" << vBuf[x][y].colorFG <<  ";" << vBuf[x][y].colorBG 
        << "m\033[" << y + 1 << ";" << x * 2 + 1 << "H" << vBuf[x][y].val;  
}

void Render::thrRender() {
  std::cout<<"\033[?25l";
  register elem_t elem;
  while(1) {
    for (int x = 0; x < MAP_W; x++)
      for (int y = 0; y < MAP_H; y++) {
        elem = Map[x][y];
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
    refresh();
    Sleep(fps);
  }
}

void Render::run() {
  std::thread t(&Render::thrRender);
  t.detach();
}
