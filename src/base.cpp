#include "base.h"
#include "common.h"
#include "render.h"
#include "map.h"
#include "level.h"

int Base::lifeMaxVal = 2000;

Base::Base(int x, int y): Tank(x, y, D_UP, CP_BS) {
  this->life = Base::lifeMaxVal;
  this->lifeMax = Base::lifeMaxVal;
  switch(camp) {
  case CP_P1: {
    this->colorBody = F_GRN;
    this->colorWheel = F_WHT;
    break;
  }
  case CP_P2: {
    this->colorBody = F_BLU;
    this->colorWheel = F_WHT;
    break;
  }
  case CP_EN: {
    this->colorBody = F_RED;
    this->colorWheel = F_WHT;
    break;
  }
  case CP_BS: {
    this->colorBody = F_YLW;
    this->colorWheel = F_WHT;
    break;
  }
  }
  for (int x = this->x - 1; x <= this->x + 1; x++)
    for (int y = this->y - 1; y <= this->y + 1; y++)
      Map::map[x][y] = {T_DRW, this};
};



void Base::draw() {
    Render::draw({colorWheel, B_BLK, "▄ "}, x - 1, y - 1);
    Render::draw({colorBody, B_BLK, "▐▌"}, x, y - 1);
    Render::draw({colorWheel, B_BLK, " ▄"}, x + 1, y - 1);
    Render::draw({colorWheel, B_BLK, "█▄"}, x - 1, y);
    Render::draw({colorBody, B_BLK, "██"}, x, y);
    Render::draw({colorWheel, B_BLK, "▄█"}, x + 1, y);
    Render::draw({colorWheel, B_BLK, "██"}, x - 1, y + 1);
    Render::draw({colorBody, B_BLK, "██"}, x, y + 1);
    Render::draw({colorWheel, B_BLK, "██"}, x + 1, y + 1);
}


void Base::move() {}
