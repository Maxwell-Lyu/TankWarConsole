#include "powerup.h"
#include "level.h"
#include "map.h"
#include <tuple>
#include <thread>
#include <functional>
#include <windows.h>

void PowerUp::draw() {
  switch (this->type) {
    case PU_NLF: Render::draw({F_YLW, B_TSP, "+♥"}, x, y); break;
    case PU_UGD: Render::draw({F_YLW, B_TSP, "↑W"}, x, y); break;
    case PU_CLK: Render::draw({F_YLW, B_TSP, "||"}, x, y); break;
    case PU_SVL: Render::draw({F_YLW, B_TSP, "╔╗"}, x, y); break;
    case PU_BMB: Render::draw({F_YLW, B_TSP, "!!"}, x, y); break;
    case PU_RBS: Render::draw({F_YLW, B_TSP, "↑B"}, x, y); break;
  }
}
void PowerUp::deletePowerUp(PowerUp *p) { 
  Sleep(1000); 
  delete p; 
}

void PowerUp::hit(int type, int srcCamp) {
  std::get<2>(Level::currentLevel->events.back()) = this->type;
  std::thread t(&PowerUp::deletePowerUp, this);
  t.detach();
}