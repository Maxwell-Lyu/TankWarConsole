#include "render.h"
// #include <iostream>
#include <windows.h>
#include <thread>
#include "map.h"

std::list<Drawable *> Render::Drawables;
pixel_t Render::vBuf[MAP_H][MAP_W];
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
    refresh();
    Sleep(fps);
  }
}

void Render::run() {
  std::thread t(&Render::thrRender);
  t.detach();
  // std::thread t2(&Render::refresh);
  // t2.detach();
}
