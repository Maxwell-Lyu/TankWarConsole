#include "render.h"

#define E(type) {T_##type, NULL}

elem_t Map[MAP_W][MAP_H] = {
  { E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), },
  { E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), },
  { E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), },
  { E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), },
  { E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), },
  { E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), },
  { E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), },
  { E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), },
  { E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), },
  { E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), E(GRS), },
 };
