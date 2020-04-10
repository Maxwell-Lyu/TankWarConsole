#include "render.h"
#include <iostream>
#include <windows.h>
#include <thread>


elem_t Map[MAP_H][MAP_W] = {
  { {T_WAL, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_WTR, NULL}, },
  { {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, },
  { {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_BNK, NULL}, {T_GRS, NULL}, },
  { {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, },
  { {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, {T_GRS, NULL}, },
};


void Render::draw(pixel_t pixel) {
  std::cout << "\033[" << pixel.colorFG <<  ";" << pixel.colorBG 
    << "m\033[" << pixel.y + 1 << ";" << pixel.x * 2 + 1 << "H" << pixel.val;  
}

void Render::draw(pixelList_t *list) {
  for (int i = 0; i < list->size; i++)
    draw(list->pixels[i]);
  std::cout << "\033[0m";
}

void Render::thrRender() {
  std::cout<<"\033[?25l";
  register elem_t elem;
  while(1) {
    for (int x = 0; x < MAP_W; x++)
      for (int y = 0; y < MAP_H; y++) {
        elem = Map[y][x];
        switch (elem.type) {
        case T_DRW: {
          if(elem.data)
            draw(elem.data->toPixel(x, y));
          break;
        }
        case T_GRS:
          draw({x, y, F_WHT, B_GRN, "草"}); break;
        case T_WTR:
          draw({x, y, F_WHT, B_BLU, "水"}); break;
        case T_WAL:
          draw({x, y, F_WHT, B_YLW, "墙"}); break;
        case T_STN:
          draw({x, y, F_WHT, B_MGT, "石"}); break;
        case T_BNK:
          draw({x, y, F_WHT, B_BLK, "  "}); break;
        }
      }
    Sleep(fps);
  }
}

void Render::run() {
  std::thread t(&Render::thrRender);
  t.detach();
}
