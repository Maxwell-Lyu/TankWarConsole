#ifndef __COMMON_H__
#define __COMMON_H__
#include <iostream>
#include <sys/timeb.h>

uint64_t getTime();

#define N_BULLET_MODEL 3
enum { BL_NM, BL_AP, BL_HE };

enum { F_BLK = 30, F_RED, F_GRN, F_YLW, F_BLU, F_MGT, F_CYN, F_WHT, F_TSP };
enum { B_BLK = 40, B_RED, B_GRN, B_YLW, B_BLU, B_MGT, B_CYN, B_WHT, B_TSP };

#define MAP_W 40
#define MAP_H 40

#define N_TERRIAN 7
enum { T_BNK, T_GRS, T_WTR, T_STN, T_WAL, T_DRW, T_PWU };


enum { D_UP, D_LT, D_DN, D_RT };

#define N_TANK_MODEL 4
enum { MD_LHT, MD_AMR, MD_ATG, MD_HVY };
enum { CP_P1 = 1, CP_P2 = 2, CP_BS = 4, CP_EN = 7 };

enum { LV_ADV, LV_COP, LV_ARN, LV_EDT };
enum { EV_DST_TK, EV_GET_PW, EV_HIT_TK };
// enum { ST_STB, ST_RUN, ST_PUS, ST_FIN };


#define STATUS_START_X 83
#define STATUS_START_Y 8
enum { SC_WLC, SC_HLP, SC_GRN, SC_GRD, SC_GPS, SC_GFN };

#define HELP_START_Y 5
#define HELP_START_X 5

#define N_POWER_UP 6
enum { PU_NLF, PU_UGD, PU_CLK, PU_SVL, PU_BMB, PU_RBS };



enum { GR_PW, GR_PL, GR_P1W, GR_P2W, GR_EXT = -1 };


#define N_MENU 4
#define MENU_START_Y 24
enum { MN_ADV, MN_COP, MN_ARN, MN_EXT };

#endif

