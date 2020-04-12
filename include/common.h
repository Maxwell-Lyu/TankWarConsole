#ifndef __COMMON_H__
#define __COMMON_H__
#include <iostream>
#include <sys/timeb.h>

uint64_t getTime();

enum { BL_NM, BL_AP, BL_HE };
enum { F_BLK = 30, F_RED, F_GRN, F_YLW, F_BLU, F_MGT, F_CYN, F_WHT, F_TSP };
enum { B_BLK = 40, B_RED, B_GRN, B_YLW, B_BLU, B_MGT, B_CYN, B_WHT, B_TSP };
enum { T_BNK, T_GRS, T_WTR, T_STN, T_WAL, T_DRW };
enum { D_UP, D_LT, D_DN, D_RT };
enum { M_LHT, M_AMR, M_ATG, M_HVY };

#endif

