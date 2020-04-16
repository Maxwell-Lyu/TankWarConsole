#include "render.h"
#include "map.h"
#include <cstring>

#define E(type) {T_##type, nullptr}
#define Line(type) {E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type), E(type)}




elem_t Map::map[MAP_W][MAP_H] = {
 };


  
#define Line_WTR_WAL_WTR {E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(WTR), E(WTR), E(WTR), E(WTR), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(WAL), E(WAL), E(WAL), E(WAL), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(WTR), E(WTR), E(WTR), E(WTR), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), E(BNK), }

elem_t Map::savedMap[MAP_W][MAP_H] = {
  Line(BNK), Line(BNK), Line(BNK), Line(BNK), Line(BNK), Line(BNK), Line(BNK), Line(BNK),
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line_WTR_WAL_WTR,
  Line(BNK), Line(BNK), Line(BNK), Line(BNK), Line(BNK), Line(BNK), Line(BNK), Line(BNK),
 };

 void Map::loadMap(int id) {
   memcpy(map, savedMap, sizeof(map));
 }

 void Map::saveMap(int id) {
   memcpy(savedMap, map, sizeof(savedMap));
 }