#ifndef __RENDER_H__
#define __RENDER_H__
#include <iostream>
#include <list>

#define MAP_W 10
#define MAP_H 10


typedef struct _pixel_t pixel_t;
typedef struct _pixelList_t pixelList_t;
typedef struct _elem_t elem_t;









enum { F_BLK = 30, F_RED, F_GRN, F_YLW, F_BLU, F_MGT, F_CYN, F_WHT };
enum { B_BLK = 40, B_RED, B_GRN, B_YLW, B_BLU, B_MGT, B_CYN, B_WHT };
enum { T_DRW, T_BNK, T_GRS, T_WTR, T_STN, T_WAL };
enum { D_UP, D_LT, D_DN, D_RT };

struct _pixel_t{
  // int x, y;
  int colorFG, colorBG;
  char *val;
};

struct _pixelList_t{
  pixel_t *pixels;
  int size;
};


class Drawable {
protected:
  int x = 2, y = 2;
  int direction = 0;
public:
  virtual void draw() = 0;
};

struct _elem_t{
  int type;
  Drawable *data;
};





class Render {
private:
  // static std::vector<Drawable *> drawableList;
  // static void draw(pixelList_t list);
  static pixel_t vBuf[MAP_H][MAP_W];
  static void thrRender();
  static void refresh();
public:
  static int fps;
  static void draw(pixel_t pixel, int x, int y) { vBuf[x][y] = pixel; }
  static void run();
  static std::list<Drawable *> Drawables;
};

#endif