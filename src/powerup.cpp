#include "powerup.h"
#include "level.h"
#include "map.h"
#include <tuple>


void PowerUp::draw() {
  switch (this->type) {
    case PU_NLF: Render::draw({F_YLW, B_TSP, "+♥"}, x, y); break;
    case PU_UGD: Render::draw({F_YLW, B_TSP, "↑W"}, x, y); break;
    case PU_CLK: Render::draw({F_YLW, B_TSP, "||"}, x, y); break;
    case PU_SVL: Render::draw({F_YLW, B_TSP, "┏┓"}, x, y); break;
    case PU_BMB: Render::draw({F_YLW, B_TSP, "‼"}, x, y); break;
  }
}
void PowerUp::hit(int type, int srcCamp) {
  Level::currentLevel->events.push_back(std::make_tuple(EV_GET_PW, (Tank *)Map::map[x][y].data, this->type));
  delete this;
}