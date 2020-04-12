#include "render.h"
#include "map.h"
#define E(type) {T_##type, NULL}

elem_t Map::map[MAP_W][MAP_H] = {
  { E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), },
  { E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), },
  { E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), },
  { E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), },
  { E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), },
  { E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), },
  { E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), },
  { E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), },
  { E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), },
  { E(BNK), E(BNK), E(BNK), E(BNK), E(WAL), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), },
 };
