#ifndef __COMMON_H__
#define __COMMON_H__
#include <iostream>
#include <sys/timeb.h>

uint64_t getTime();

enum { BL_NM, BL_AP, BL_HE };

enum { F_BLK = 30, F_RED, F_GRN, F_YLW, F_BLU, F_MGT, F_CYN, F_WHT, F_TSP };
enum { B_BLK = 40, B_RED, B_GRN, B_YLW, B_BLU, B_MGT, B_CYN, B_WHT, B_TSP };

#define MAP_W 30
#define MAP_H 30
enum { T_BNK, T_GRS, T_WTR, T_STN, T_WAL, T_DRW };


enum { D_UP, D_LT, D_DN, D_RT };

#define N_TANK_MODEL 4
enum { MD_LHT, MD_AMR, MD_ATG, MD_HVY };
enum { CP_P1 = 1, CP_P2, CP_EN };

enum { LV_AD1, LV_AD2, LV_ARN };
enum { EV_DST_TK, EV_DST_BS };
// enum { ST_STB, ST_RUN, ST_PUS, ST_FIN };
enum { SC_WLC, SC_HLP, SC_GRN, SC_GRD, SC_GPS, SC_GFN };


#endif

