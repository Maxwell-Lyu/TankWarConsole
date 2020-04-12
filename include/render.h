#ifndef __RENDER_H__
#define __RENDER_H__
#include <iostream>
#include <list>
#include "common.h"

typedef struct _pixel_t pixel_t;
typedef struct _pixelList_t pixelList_t;
typedef struct _elem_t elem_t;




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
  Drawable() {}
  Drawable(int x, int y, int direction): x(x), y(y), direction(direction) {}
  virtual void draw() = 0;
  virtual void hit(int type, int srcCamp) {};
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
  static int scene;
  static int fps;
  static void draw(pixel_t pixel, int x, int y) { vBuf[x][y] = pixel;}
  static void run();
  static std::list<Drawable *> Drawables;
};

#endif