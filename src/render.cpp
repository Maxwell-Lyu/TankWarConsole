#include "render.h"
// #include <iostream>
#include <windows.h>
#include <thread>
#include "map.h"
#include "level.h"
#include <iostream>
#include <iomanip>
#include "game.h"
#include "assets.h"
std::list<Drawable *> Render::Drawables;
pixel_t Render::vBuf[MAP_H][MAP_W];
int Render::scene;
// extern elem_t Map[MAP_W][MAP_H];


void Render::refresh(){
  for (register int x = 0; x < MAP_W; x++)
    for (register int y = 0; y < MAP_H; y++)
      std::cout << "\033[" << vBuf[x][y].colorFG <<  ";" << vBuf[x][y].colorBG << "m\033[" << y + 1 << ";" << x * 2 + 1 << "H" << vBuf[x][y].val;  
}

void Render::thrRender() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(0);
  std::cout<<"\033[?25l";
  register elem_t elem;
  while(1) {
    switch (scene) {
    case SC_GRN: {
      for (int x = 0; x < MAP_W; x++)
        for (int y = 0; y < MAP_H; y++) {
          elem = Map::map[x][y];
          switch (elem.type) {
          case T_DRW:
            break;
          case T_GRS:
            draw({F_WHT, B_GRN, "WW"}, x, y); break;
          case T_WTR:
            draw({F_BLU, B_BLK, "░░"}, x, y); break;
          case T_WAL:
            draw({F_YLW, B_BLK, "▓▓"}, x, y); break;
          case T_STN:
            draw({F_WHT, B_YLW, "╪╪"}, x, y); break;
          case T_BNK:
            draw({F_WHT, B_BLK, "  "}, x, y); break;
          case T_PWU:
            elem.data->draw(); break;
          }
        }
      for(auto &drawable: Drawables)
        drawable->draw();
      renderStatus();
      refresh();
      break;
    }
    case SC_GPS: {
      for (int ty = 17; ty < 24; ty++)
        std::cout << "\033["<< ty << ";45H"<< "          " << std::endl;
      std::cout << "\033[18;47H\033[37;1m██  ██" << std::endl;
      std::cout << "\033[19;47H\033[37;1m██  ██" << std::endl;
      std::cout << "\033[20;47H\033[37;1m██  ██" << std::endl;
      std::cout << "\033[21;47H\033[37;1m██  ██" << std::endl;
      std::cout << "\033[22;47H\033[37;1mPAUSED" << std::endl;
      while(scene == SC_GPS)
        Sleep(50);
      break;
    }
    case SC_GRD: {
      Assets::renderDight(23, 17, F_WHT, 3);
      Sleep(1000);
      Assets::renderDight(23, 17, F_WHT, 2);
      Sleep(1000);
      Assets::renderDight(23, 17, F_WHT, 1);
      Sleep(1000);
      Assets::renderDight(23, 17, F_WHT, 0);
      break;
    }
    case SC_GFN: {
      std::cout << "\033[2J" << std::endl;
      Level::currentLevel->renderResult();
      while(scene == SC_GFN)
        Sleep(50);
      break;
    }
    case SC_WLC: {
      std::cout << "\033[2J" << std::endl;
      Assets::renderLetter(13, 8 , F_GRN, 'T');
      Assets::renderLetter(19, 8 , F_GRN, 'A');
      Assets::renderLetter(25, 8 , F_GRN, 'N');
      Assets::renderLetter(31, 8 , F_GRN, 'K');
      Assets::renderLetter(4 , 14, F_BLU, 'W');
      Assets::renderLetter(10, 14, F_BLU, 'A');
      Assets::renderLetter(16, 14, F_BLU, 'R');
      Assets::renderLetter(22, 14, F_BLU, 'F');
      Assets::renderLetter(28, 14, F_BLU, 'A');
      Assets::renderLetter(34, 14, F_BLU, 'R');
      Assets::renderLetter(40, 14, F_BLU, 'E');
      renderString(12, 39, "Copyright © 2020 Maxwell Lyu. All Rights Reserved.");
      while(scene == SC_WLC) {
        if(Game::menuSel == MN_ADV) renderString(19, MENU_START_Y + 0, ">>  [   ADVENTURE  ]  <<", F_YLW);
        else                        renderString(19, MENU_START_Y + 0, "    [   ADVENTURE  ]    ", F_WHT);

        if(Game::menuSel == MN_COP) renderString(19, MENU_START_Y + 2, ">>  [ CO-OPERATION ]  <<", F_YLW);
        else                        renderString(19, MENU_START_Y + 2, "    [ CO-OPERATION ]    ", F_WHT);

        if(Game::menuSel == MN_ARN) renderString(19, MENU_START_Y + 4, ">>  [     ARENA    ]  <<", F_YLW);
        else                        renderString(19, MENU_START_Y + 4, "    [     ARENA    ]    ", F_WHT);

        if(Game::menuSel == MN_EXT) renderString(19, MENU_START_Y + 6, ">>  [     EXIT     ]  <<", F_YLW);
        else                        renderString(19, MENU_START_Y + 6, "    [     EXIT     ]    ", F_WHT);
        Sleep(50);
      }
      std::cout << "\033[2J" << std::endl;
      break;
    }
    case SC_HLP: {
      std::cout << "\033[2J" << std::endl;
      renderString(HELP_START_X, HELP_START_Y, "[ ENEMY INTEL ]");
      renderString(HELP_START_X + 0, HELP_START_Y + 2, Tank::models[MD_LHT][D_UP][0], F_WHT, B_BLK);
      renderString(HELP_START_X + 1, HELP_START_Y + 2, Tank::models[MD_LHT][D_UP][1], F_RED, B_BLK);
      renderString(HELP_START_X + 2, HELP_START_Y + 2, Tank::models[MD_LHT][D_UP][2], F_WHT, B_BLK);
      renderString(HELP_START_X + 0, HELP_START_Y + 3, Tank::models[MD_LHT][D_UP][3], F_WHT, B_BLK);
      renderString(HELP_START_X + 1, HELP_START_Y + 3, Tank::models[MD_LHT][D_UP][4], F_RED, B_BLK);
      renderString(HELP_START_X + 2, HELP_START_Y + 3, Tank::models[MD_LHT][D_UP][5], F_WHT, B_BLK);
      renderString(HELP_START_X + 0, HELP_START_Y + 4, Tank::models[MD_LHT][D_UP][6], F_WHT, B_BLK);
      renderString(HELP_START_X + 1, HELP_START_Y + 4, Tank::models[MD_LHT][D_UP][7], F_RED, B_BLK);
      renderString(HELP_START_X + 2, HELP_START_Y + 4, Tank::models[MD_LHT][D_UP][8], F_WHT, B_BLK);
      renderString(HELP_START_X + 4, HELP_START_Y + 2, "LIGHT TANK", F_RED, B_BLK);
      renderString(HELP_START_X + 4, HELP_START_Y + 3, "SAME PERFORMANCE AS PLAYER", F_WHT, B_BLK);
      renderString(HELP_START_X + 20, HELP_START_Y + 2, Tank::models[MD_AMR][D_UP][0], F_WHT, B_BLK);
      renderString(HELP_START_X + 21, HELP_START_Y + 2, Tank::models[MD_AMR][D_UP][1], F_RED, B_BLK);
      renderString(HELP_START_X + 22, HELP_START_Y + 2, Tank::models[MD_AMR][D_UP][2], F_WHT, B_BLK);
      renderString(HELP_START_X + 20, HELP_START_Y + 3, Tank::models[MD_AMR][D_UP][3], F_WHT, B_BLK);
      renderString(HELP_START_X + 21, HELP_START_Y + 3, Tank::models[MD_AMR][D_UP][4], F_RED, B_BLK);
      renderString(HELP_START_X + 22, HELP_START_Y + 3, Tank::models[MD_AMR][D_UP][5], F_WHT, B_BLK);
      renderString(HELP_START_X + 20, HELP_START_Y + 4, Tank::models[MD_AMR][D_UP][6], F_WHT, B_BLK);
      renderString(HELP_START_X + 21, HELP_START_Y + 4, Tank::models[MD_AMR][D_UP][7], F_RED, B_BLK);
      renderString(HELP_START_X + 22, HELP_START_Y + 4, Tank::models[MD_AMR][D_UP][8], F_WHT, B_BLK);
      renderString(HELP_START_X + 24, HELP_START_Y + 2, "ARMORED VEHICLE", F_RED, B_BLK);
      renderString(HELP_START_X + 24, HELP_START_Y + 3, "HIGH MOVE SPEED", F_WHT, B_BLK);
      renderString(HELP_START_X + 0, HELP_START_Y + 6, Tank::models[MD_ATG][D_UP][0], F_WHT, B_BLK);
      renderString(HELP_START_X + 1, HELP_START_Y + 6, Tank::models[MD_ATG][D_UP][1], F_RED, B_BLK);
      renderString(HELP_START_X + 2, HELP_START_Y + 6, Tank::models[MD_ATG][D_UP][2], F_WHT, B_BLK);
      renderString(HELP_START_X + 0, HELP_START_Y + 7, Tank::models[MD_ATG][D_UP][3], F_WHT, B_BLK);
      renderString(HELP_START_X + 1, HELP_START_Y + 7, Tank::models[MD_ATG][D_UP][4], F_RED, B_BLK);
      renderString(HELP_START_X + 2, HELP_START_Y + 7, Tank::models[MD_ATG][D_UP][5], F_WHT, B_BLK);
      renderString(HELP_START_X + 0, HELP_START_Y + 8, Tank::models[MD_ATG][D_UP][6], F_WHT, B_BLK);
      renderString(HELP_START_X + 1, HELP_START_Y + 8, Tank::models[MD_ATG][D_UP][7], F_RED, B_BLK);
      renderString(HELP_START_X + 2, HELP_START_Y + 8, Tank::models[MD_ATG][D_UP][8], F_WHT, B_BLK);
      renderString(HELP_START_X + 4, HELP_START_Y + 6, "ANTITANK GUN", F_RED, B_BLK);
      renderString(HELP_START_X + 4, HELP_START_Y + 7, "HIGH FIRE SPEED", F_WHT, B_BLK);
      renderString(HELP_START_X + 20, HELP_START_Y + 6, Tank::models[MD_HVY][D_UP][0], F_WHT, B_BLK);
      renderString(HELP_START_X + 21, HELP_START_Y + 6, Tank::models[MD_HVY][D_UP][1], F_RED, B_BLK);
      renderString(HELP_START_X + 22, HELP_START_Y + 6, Tank::models[MD_HVY][D_UP][2], F_WHT, B_BLK);
      renderString(HELP_START_X + 20, HELP_START_Y + 7, Tank::models[MD_HVY][D_UP][3], F_WHT, B_BLK);
      renderString(HELP_START_X + 21, HELP_START_Y + 7, Tank::models[MD_HVY][D_UP][4], F_RED, B_BLK);
      renderString(HELP_START_X + 22, HELP_START_Y + 7, Tank::models[MD_HVY][D_UP][5], F_WHT, B_BLK);
      renderString(HELP_START_X + 20, HELP_START_Y + 8, Tank::models[MD_HVY][D_UP][6], F_WHT, B_BLK);
      renderString(HELP_START_X + 21, HELP_START_Y + 8, Tank::models[MD_HVY][D_UP][7], F_RED, B_BLK);
      renderString(HELP_START_X + 22, HELP_START_Y + 8, Tank::models[MD_HVY][D_UP][8], F_WHT, B_BLK);
      renderString(HELP_START_X + 24, HELP_START_Y + 6, "HEAVY TANK", F_RED, B_BLK);
      renderString(HELP_START_X + 24, HELP_START_Y + 7, "HIGH ARMOR (HP)", F_WHT, B_BLK);
      renderString(HELP_START_X + 24, HELP_START_Y + 8, "ARMOR-PIERCING BULLET", F_WHT, B_BLK);
      renderString(HELP_START_X, HELP_START_Y + 10, "[ CONTORL ]");
      renderString(HELP_START_X, HELP_START_Y + 12, "PLAYER 1", F_GRN);
      renderString(HELP_START_X + 0, HELP_START_Y + 13, Tank::models[MD_LHT][D_UP][0], F_WHT, B_BLK);
      renderString(HELP_START_X + 1, HELP_START_Y + 13, Tank::models[MD_LHT][D_UP][1], F_GRN, B_BLK);
      renderString(HELP_START_X + 2, HELP_START_Y + 13, Tank::models[MD_LHT][D_UP][2], F_WHT, B_BLK);
      renderString(HELP_START_X + 0, HELP_START_Y + 14, Tank::models[MD_LHT][D_UP][3], F_WHT, B_BLK);
      renderString(HELP_START_X + 1, HELP_START_Y + 14, Tank::models[MD_LHT][D_UP][4], F_GRN, B_BLK);
      renderString(HELP_START_X + 2, HELP_START_Y + 14, Tank::models[MD_LHT][D_UP][5], F_WHT, B_BLK);
      renderString(HELP_START_X + 0, HELP_START_Y + 15, Tank::models[MD_LHT][D_UP][6], F_WHT, B_BLK);
      renderString(HELP_START_X + 1, HELP_START_Y + 15, Tank::models[MD_LHT][D_UP][7], F_GRN, B_BLK);
      renderString(HELP_START_X + 2, HELP_START_Y + 15, Tank::models[MD_LHT][D_UP][8], F_WHT, B_BLK);
      renderString(HELP_START_X + 4, HELP_START_Y + 13, "MOVE:      [W]");
      renderString(HELP_START_X + 4, HELP_START_Y + 14, "        [A][S][D]");
      renderString(HELP_START_X + 4, HELP_START_Y + 15, "FIRE:    [SPACE]");
      renderString(HELP_START_X + 20, HELP_START_Y + 12, "PLAYER 2", F_BLU);
      renderString(HELP_START_X + 20, HELP_START_Y + 13, Tank::models[MD_LHT][D_UP][0], F_WHT, B_BLK);
      renderString(HELP_START_X + 21, HELP_START_Y + 13, Tank::models[MD_LHT][D_UP][1], F_BLU, B_BLK);
      renderString(HELP_START_X + 22, HELP_START_Y + 13, Tank::models[MD_LHT][D_UP][2], F_WHT, B_BLK);
      renderString(HELP_START_X + 20, HELP_START_Y + 14, Tank::models[MD_LHT][D_UP][3], F_WHT, B_BLK);
      renderString(HELP_START_X + 21, HELP_START_Y + 14, Tank::models[MD_LHT][D_UP][4], F_BLU, B_BLK);
      renderString(HELP_START_X + 22, HELP_START_Y + 14, Tank::models[MD_LHT][D_UP][5], F_WHT, B_BLK);
      renderString(HELP_START_X + 20, HELP_START_Y + 15, Tank::models[MD_LHT][D_UP][6], F_WHT, B_BLK);
      renderString(HELP_START_X + 21, HELP_START_Y + 15, Tank::models[MD_LHT][D_UP][7], F_BLU, B_BLK);
      renderString(HELP_START_X + 22, HELP_START_Y + 15, Tank::models[MD_LHT][D_UP][8], F_WHT, B_BLK);
      renderString(HELP_START_X + 24, HELP_START_Y + 13, "MOVE:      [I]");
      renderString(HELP_START_X + 24, HELP_START_Y + 14, "        [J][K][L]");
      renderString(HELP_START_X + 24, HELP_START_Y + 15, "FIRE:    [ENTER]");
      renderString(HELP_START_X + 0, HELP_START_Y + 17, "PAUSE/RESUME: [ESC]        EXIT: [Q]           HELP: [H]");
      renderString(HELP_START_X, HELP_START_Y + 19, "[ POWER-UPS ]");
      renderString(HELP_START_X, HELP_START_Y + 20, "PICKED UP WHEN PLAYERS TOUCH, DESTROYED WHEN ENEMIES TOUCH");
      renderString(HELP_START_X, HELP_START_Y + 22, "[+♥]: ADD 1 LIFE            [↑W]: UPGRADE WEAPON        [||]: ザ · ワールド", F_YLW);
      renderString(HELP_START_X, HELP_START_Y + 23, "      DEATH COSTS 1 LIFE          NORM->AP->HE                STOP ENEMY FOR 3s");
      renderString(HELP_START_X, HELP_START_Y + 24, "[╔╗]: DONALD TRUMP          [‼]: BOMB                  [↑B]: REPAIR BASE", F_YLW);
      renderString(HELP_START_X, HELP_START_Y + 25, "      BUILD WALL AROUND BASE      KILL ALL ENEMIES            ADD 1000 BASE'S HP");         
      renderString(HELP_START_X, HELP_START_Y + 27, "[ BULLETS ]");
      renderString(HELP_START_X, HELP_START_Y + 29, "[○]: NORMAL(100)            [●]: ARMOR-PIERCING(200)    [☼]: HIGH-EXPLOSIVE(400)");
      while(scene == SC_HLP)
        Sleep(50);
      std::cout << "\033[2J" << std::endl;
      break;
    }
    default:
      break;
    }
    Sleep(fps);
  }
}

void Render::renderStatus() {
  switch (Level::currentLevel->type) {
  case LV_COP: Tank::renderStatusTank(STATUS_START_Y + 19, Level::currentLevel->player2);
  case LV_ADV: {
    Tank::renderStatusTank(STATUS_START_Y + 14, Level::currentLevel->player1);
    Tank::renderStatusTank(STATUS_START_Y + 11, Level::currentLevel->base);
    int line = STATUS_START_Y + 2;
    for (auto it = Level::currentLevel->enemies.begin(); it != Level::currentLevel->enemies.end(); it++) {
      Tank::renderStatusTank(line, *it);
      line += 2;
    }
    for (; line < STATUS_START_Y + 10; line++)
      std::cout << "\033[" << line + 1 << ";" << STATUS_START_X << "H                ";
    renderStatusEnemy(STATUS_START_Y);
    break;
  }
  case LV_ARN:{
    Tank::renderStatusTank(STATUS_START_Y + 9, Level::currentLevel->player1);
    Tank::renderStatusTank(STATUS_START_Y + 14, Level::currentLevel->player2);
    break;
  }
  }
}
void Render::renderStatusEnemy(int y) {
  std::cout << "\033[31;1m\033[" << y + 1 << ";" << STATUS_START_X << "HENEMY LEFT [\033[37;1m" << std::setw(2) << std::setfill('0') << Level::currentLevel->waves.size() << "\033[31;1m]";
}

void Render::run() {
  std::thread t(&Render::thrRender);
  t.detach();
  // std::thread t2(&Render::refresh);
  // t2.detach();
}


void Render::renderString(int x, int y, const char *string, int colorFG, int F_REDG) {
  std::cout << "\033[" << y + 1 << ";" << (x << 1) + 1 << "H\033[" << colorFG << ";" << F_REDG << ";1m" << string << std::endl;
}
