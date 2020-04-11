#include "common.h"

uint64_t getTime() {
  timeb time;
  ftime(&time);
  return time.time * 1000 + time.millitm;
}