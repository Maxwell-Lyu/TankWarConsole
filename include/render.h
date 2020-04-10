#ifndef __RENDER_H__
#define __RENDER_H__


#define MAP_W 5
#define MAP_H 5


typedef struct _pixel_t pixel_t;
typedef struct _pixelList_t pixelList_t;
typedef struct _elem_t elem_t;









enum { F_BLK = 30, F_RED, F_GRN, F_YLW, F_BLU, F_MGT, F_CYN, F_WHT };
enum { B_BLK = 40, B_RED, B_GRN, B_YLW, B_BLU, B_MGT, B_CYN, B_WHT };
enum { T_DRW, T_BNK, T_GRS, T_WTR, T_STN, T_WAL };

struct _pixel_t{
  int x, y;
  int colorFG, colorBG;
  const char *val;
};

struct _pixelList_t{
  pixel_t *pixels;
  int size;
};


class Drawable {
private:
  int x, y;
public:
  virtual pixelList_t *toPixel(int x, int y) = 0;
};

struct _elem_t{
  int type;
  Drawable *data;
};





class Render {
private:
  // static std::vector<Drawable *> drawableList;
  static void draw(pixel_t pixel);
  static void draw(pixelList_t *list);
  static void thrRender();
public:
  static int fps;
  static void run();
};
#endif