#include "level.h"
#include "common.h"
#include "render.h"
#include "bullet.h"
#include "tank.h"
#include "base.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <list>
#include <algorithm>
#include "map.h"
#include "powerup.h"
#include <iomanip>
#include "assets.h"

Level *Level::currentLevel;


Level::Level(int type): scoreP1(0), scoreP2(0), type(type) {
  Level::currentLevel = this;
  switch (type) {
  case LV_ADV: {
    player1 = new Tank(5, 38, D_UP, CP_P1, MD_LHT);
    player2 = nullptr;
    base = new Base(MAP_W >> 1, MAP_H - 2);
    scoreP1 = 0;
    scoreP2 = 0;
    Render::Drawables.push_back(base);
    Render::Drawables.push_back(player1);
    waves.push_back(std::make_tuple(5, 5, MD_LHT));
    waves.push_back(std::make_tuple(10, 5, MD_AMR));
    waves.push_back(std::make_tuple(15, 5, -1));
    waves.push_back(std::make_tuple(20, 5, -1));
    waves.push_back(std::make_tuple(5, 5, MD_LHT));
    waves.push_back(std::make_tuple(10, 5, MD_AMR));
    waves.push_back(std::make_tuple(15, 5, MD_ATG));
    waves.push_back(std::make_tuple(20, 5, MD_HVY));
    // Map::map[15][10] = {T_PWU, new PowerUp(15, 10, PU_UGD)};
    // Map::map[20][10] = {T_PWU, new PowerUp(20, 10, PU_CLK)};
    // Map::map[25][10] = {T_PWU, new PowerUp(25, 10, PU_SVL)};
    // Map::map[30][10] = {T_PWU, new PowerUp(30, 10, PU_BMB)};
    break;
  }
  case LV_COP: {
    player1 = new Tank(5, 38, D_UP, CP_P1, MD_LHT);
    player2 = new Tank(34, 38, D_UP, CP_P2, MD_LHT);
    base = new Base(MAP_W >> 1, MAP_H - 2);
    scoreP1 = 0;
    scoreP2 = 0;
    Render::Drawables.push_back(base);
    Render::Drawables.push_back(player1);
    Render::Drawables.push_back(player2);
    waves.push_back(std::make_tuple(5, 5, MD_LHT));
    break;
  }
  case LV_ARN: {
    player1 = new Tank(1 , 20, D_RT, CP_P1, MD_LHT);
    player2 = new Tank(38, 20, D_LT, CP_P2, MD_LHT);
    scoreP1 = 0;
    scoreP2 = 0;
    Render::Drawables.push_back(player1);
    Render::Drawables.push_back(player2);
    break;
  }
  case LV_EDT: {
    player1 = new Cursor();
    player2 = nullptr;
    scoreP1 = 0;
    scoreP2 = 0;
    Render::Drawables.push_back(player1);
    break;
  }
  }
}

Level::~Level() {
  for(auto &a: Render::Drawables)
    delete a;
  for(auto &a: deadEnemies)
    delete a;
  Render::Drawables.clear();
  Bullet::Bullets.clear();
}

void Level::showResult(int ret) {
  std::cout << "\033[2J";
  this->result = ret;
  Render::scene = SC_GFN;
  while(Render::scene == SC_GFN) {
    Sleep(50);
    if(kbhit() && getch() == 27) {
      Render::scene = SC_WLC;
    }
  }
}

int Adventure::run() {
  Render::scene = SC_GRD;
  // Render::scene = SC_HLP;
  Sleep(3000);
  Render::scene = SC_GRN;
  Sleep(500);
  while(1) {
    // * user input and oprations
    while(kbhit()) {
      switch(getch()) {
      case 119: player1->move(D_UP); break;
      case 97:  player1->move(D_LT); break;
      case 115: player1->move(D_DN); break;
      case 100: player1->move(D_RT); break;
      case 27: {
        Render::scene = SC_GPS;
        while(Render::scene == SC_GPS) {
          Sleep(50);
          if(kbhit()) {
            switch(getch()) {
              case 13: {
                Render::scene = SC_GRD;
                break;
              }
              case 104: {
                Render::scene = SC_HLP;
                while(Render::scene != SC_GRD) {
                  Sleep(50);
                  if(kbhit() && getch() == 27)
                    break;
                }
                Render::scene = SC_GRN;
                Sleep(100);
                Render::scene = SC_GPS;
                break;
              }
              case 27: {
                return GR_EXT;
              }
            }
          }
        }
        Sleep(3000);
        Render::scene = SC_GRN;
        Sleep(500);
        break;
      }; 
      case 32: {
        Bullet *blt = player1->fire();
        if(blt != nullptr) {
          Render::Drawables.emplace_back(blt);
          Bullet::Bullets.emplace_back(blt);
        }
        break;
      } 
      }
    }
    // * move and fire for AutoTank
    for(auto it = enemies.begin(); it != enemies.end(); ++it) {
      (*it)->move();
      if(getTime() % 4000 < 2000){
        Bullet *blt = (*it)->fire();
        if(blt != nullptr) {
          Render::Drawables.emplace_back(blt);
          Bullet::Bullets.emplace_back(blt);
        }
      } 
    }
    // * move bullets
    for(auto it = Bullet::Bullets.begin(); it != Bullet::Bullets.end();) {
      Bullet *blt = *it;
      if(blt->move()) {
          it = Bullet::Bullets.erase(it);
          Render::Drawables.remove(blt);
          delete blt;
      }
      else {
        ++it;
      }
    }
    // * bullet cancels each other
    for(auto it = Bullet::Bullets.begin(); it != Bullet::Bullets.end();++it)
      for(auto it2 = it; it2 != Bullet::Bullets.end();++it2)
        if((*it)->x == (*it2)->x && (*it)->y == (*it2)->y && it != it2)
          (*it)->toRemove = (*it2)->toRemove = 1;
    for(auto it = Bullet::Bullets.begin(); it != Bullet::Bullets.end();) {
      Bullet *blt = *it;
      if(blt->toRemove) {
        it = Bullet::Bullets.erase(it);
        Render::Drawables.remove(blt);
        delete blt;
      }
      else
        it++;
    }
    // * handle events
    for(auto it = events.begin(); it != events.end();) {
      auto e = *it;
      switch(std::get<0>(e)) {
        case EV_DST_TK: {
          auto dest = std::get<1>(e);
          // auto src = std::get<2>(e);
          Render::Drawables.remove(dest);
          dest->~Tank();
          if(dest == player1) {
            player1 = nullptr;
            return GR_PL;
          } 
          else if(dest == base) {
            return GR_PL;
          }
          else {
            enemies.remove(dest);
            scoreP1 += 1000;
          }
          break;
        }
        case EV_HIT_TK: {
          // auto dest = std::get<1>(e);
          auto src = std::get<2>(e);
          switch(src) {
            case CP_P1: scoreP1 += 100; break;
            case CP_EN: break;
          }
          break;
        }
        case EV_GET_PW: {
          auto target = std::get<1>(e);
          auto type = std::get<2>(e);
          if(target->camp != CP_EN) {
            switch(type) {
              case PU_NLF: target->nLife++; break;
              case PU_UGD: target->weapon = target->weapon == BL_HE ? BL_HE : target->weapon + 1; 
              break;
              case PU_CLK: {
                for(auto it = enemies.begin(); it != enemies.end(); ++it)
                  (*it)->lastMove = (*it)->lastFire = getTime() + 3000;
                break;
              }
              case PU_SVL: {
                for (int x = base->x - 4; x <= base->x + 4; x++)
                  for (int y = base->y - 4; y <= base->y + 1; y++)
                    if(Map::map[x][y].type == T_BNK)
                      Map::map[x][y] = {T_WAL, NULL};
                break;
              }
              case PU_BMB:  {
                for(auto it = enemies.begin(); it != enemies.end();) {
                  Render::Drawables.remove(*it);
                  (*it)->~Tank();
                  deadEnemies.push_back(*it);
                  it = enemies.erase(it);
                }
                break;
              }
              case PU_RBS: {
                base->life += 1000;
                if(base->life > base->lifeMax) base->life = base->lifeMax;
                break;
              }
            }
          }
          break;
        }
      }
      it = events.erase(it);
    }
    sendPowerUp();
    if(enemies.size())
      nextWave = getTime() + 5000;
    else if(waves.size())
      sendEnemy();
    else
      return GR_PW;
    Sleep(50);
  }
}

void Adventure::sendPowerUp() {
  if(getTime() < nextPowerUp + 10000) return;
  int x = rand() % MAP_W;
  int y = rand() % (MAP_H - 12) + 6;
  if(Map::map[x][y].type == T_BNK) {
    auto p = new PowerUp(x, y, getTime() % N_POWER_UP);
    Map::map[x][y] = {T_PWU, p};
  }
  nextPowerUp = getTime();
}

void Adventure::sendEnemy() {
  if(getTime() < nextWave) return;
  nextWave = getTime();
  for (int i = 0; i < 4 && waves.size(); i++) {
    auto w = waves.front();
    waves.pop_front();
    if(std::get<2>(w) == -1) continue;
    auto t = new AutoTank(std::get<0>(w), std::get<1>(w), std::get<2>(w));
    enemies.push_back(t);
    Render::Drawables.push_back(t);
  }
}

void Adventure::renderResult() {
  switch(this->result) {
    case GR_PW: {
      Assets::renderLetter(4, 10, F_GRN, 'Y');
      Assets::renderLetter(10, 10, F_GRN, 'O');
      Assets::renderLetter(16, 10, F_GRN, 'U');
      Assets::renderLetter(28, 10, F_GRN, 'W');
      Assets::renderLetter(34, 10, F_GRN, 'I');
      Assets::renderLetter(40, 10, F_GRN, 'N');
      break;
    }
    case GR_PL: {
      Assets::renderLetter(2 , 10, F_RED, 'Y');
      Assets::renderLetter(8 , 10, F_RED, 'O');
      Assets::renderLetter(14, 10, F_RED, 'U');
      Assets::renderLetter(24, 10, F_RED, 'L');
      Assets::renderLetter(30, 10, F_RED, 'O');
      Assets::renderLetter(36, 10, F_RED, 'S');
      Assets::renderLetter(42, 10, F_RED, 'E');
      break;
    }
    default: {
      Assets::renderLetter(4 , 10, F_YLW, 'S');
      Assets::renderLetter(10, 10, F_YLW, 'U');
      Assets::renderLetter(16, 10, F_YLW, 'S');
      Assets::renderLetter(22, 10, F_YLW, 'P');
      Assets::renderLetter(28, 10, F_YLW, 'E');
      Assets::renderLetter(34, 10, F_YLW, 'N');
      Assets::renderLetter(40, 10, F_YLW, 'D');
      break;
    }
  }
  Render::renderString(20, 23, "    [  MODE  ]    ", F_WHT);
  Render::renderString(20, 24, "    ADVENTURE     ", F_WHT);
  Render::renderString(20, 26, "    [  SCORE ]    ", F_WHT);
  std::cout << "\033[32;1m\033[" << 28 << ";" << 41 << "H    " << std::setw(10) << std::setfill(' ') << scoreP1 << "    " << std::endl;;
  Render::renderString(20, 29, "PRESS [ESC] TO EXIT", F_WHT);
}
int Cooperation::run() {
  Render::scene = SC_GRD;
  // Render::scene = SC_HLP;
  Sleep(3000);
  Render::scene = SC_GRN;
  Sleep(500);
  while(1) {
    // * user input and oprations
    while(kbhit()) {
      switch(getch()) {
      case 119: player1->move(D_UP); break;
      case 97:  player1->move(D_LT); break;
      case 115: player1->move(D_DN); break;
      case 100: player1->move(D_RT); break;
      case 105: player2->move(D_UP); break;
      case 106:  player2->move(D_LT); break;
      case 107: player2->move(D_DN); break;
      case 108: player2->move(D_RT); break;
      case 27: {
        Render::scene = SC_GPS;
        while(Render::scene == SC_GPS) {
          Sleep(50);
          if(kbhit()) {
            switch(getch()) {
              case 13: {
                Render::scene = SC_GRD;
                break;
              }
              case 104: {
                Render::scene = SC_HLP;
                while(Render::scene != SC_GRD) {
                  Sleep(50);
                  if(kbhit() && getch() == 27)
                    break;
                }
                Render::scene = SC_GRN;
                Sleep(100);
                Render::scene = SC_GPS;
                break;
              }
              case 27: {
                return GR_EXT;
              }
            }
          }
        }
        Sleep(3000);
        Render::scene = SC_GRN;
        Sleep(500);
        break;
      }; 
      case 32: {
        Bullet *blt = player1->fire();
        if(blt != nullptr) {
          Render::Drawables.emplace_back(blt);
          Bullet::Bullets.emplace_back(blt);
        }
        break;
      } 
      case 13: {
        Bullet *blt = player2->fire();
        if(blt != nullptr) {
          Render::Drawables.emplace_back(blt);
          Bullet::Bullets.emplace_back(blt);
        }
        break;
      } 
      }
    }
    // * move and fire for AutoTank
    for(auto it = enemies.begin(); it != enemies.end(); ++it) {
      (*it)->move();
      if(getTime() % 4000 < 2000){
        Bullet *blt = (*it)->fire();
        if(blt != nullptr) {
          Render::Drawables.emplace_back(blt);
          Bullet::Bullets.emplace_back(blt);
        }
      } 
    }
    // * move bullets
    for(auto it = Bullet::Bullets.begin(); it != Bullet::Bullets.end();) {
      Bullet *blt = *it;
      if(blt->move()) {
          it = Bullet::Bullets.erase(it);
          Render::Drawables.remove(blt);
          delete blt;
      }
      else {
        ++it;
      }
    }
    // * bullet cancels each other
    for(auto it = Bullet::Bullets.begin(); it != Bullet::Bullets.end();++it)
      for(auto it2 = it; it2 != Bullet::Bullets.end();++it2)
        if((*it)->x == (*it2)->x && (*it)->y == (*it2)->y && it != it2)
          (*it)->toRemove = (*it2)->toRemove = 1;
    for(auto it = Bullet::Bullets.begin(); it != Bullet::Bullets.end();) {
      Bullet *blt = *it;
      if(blt->toRemove) {
        it = Bullet::Bullets.erase(it);
        Render::Drawables.remove(blt);
        delete blt;
      }
      else
        it++;
    }
    // * handle events
    for(auto it = events.begin(); it != events.end();) {
      auto e = *it;
      switch(std::get<0>(e)) {
        case EV_DST_TK: {
          auto dest = std::get<1>(e);
          auto src = std::get<2>(e);
          Render::Drawables.remove(dest);
          dest->~Tank();
          if(dest == player1) {
            player1 = nullptr;
          } 
          else if(dest == base) {
            return GR_PL;
          }
          else if(dest == player2) {
            player2 = nullptr;
          }
          else {
            enemies.remove(dest);
            if(src == CP_P1)
              scoreP1 += 1000;
            if(src == CP_P2)
              scoreP2 += 1000;
          }
          if(player1 == nullptr && player2 == nullptr)
            return GR_PL;
          break;
        }
        case EV_HIT_TK: {
          // auto dest = std::get<1>(e);
          auto src = std::get<2>(e);
          switch(src) {
            case CP_P1: scoreP1 += 100; break;
            case CP_P2: scoreP2 += 100; break;
            case CP_EN: break;
          }
          break;
        }
        case EV_GET_PW: {
          auto target = std::get<1>(e);
          auto type = std::get<2>(e);
          if(target->camp != CP_EN) {
            switch(type) {
              case PU_NLF: target->nLife++; break;
              case PU_UGD: target->weapon = target->weapon == BL_HE ? BL_HE : target->weapon + 1; break;
              case PU_CLK: {
                for(auto it = enemies.begin(); it != enemies.end(); ++it)
                  (*it)->lastMove = (*it)->lastFire = getTime() + 3000;
                break;
              }
              case PU_SVL: {
                for (int x = base->x - 4; x <= base->x + 4; x++)
                  for (int y = base->y - 4; y <= base->y + 1; y++)
                    if(Map::map[x][y].type == T_BNK)
                      Map::map[x][y] = {T_WAL, NULL};
                break;
              }
              case PU_BMB:  {
                for(auto it = enemies.begin(); it != enemies.end();) {
                  Render::Drawables.remove(*it);
                  (*it)->~Tank();
                  deadEnemies.push_back(*it);
                  it = enemies.erase(it);
                }
                break;
              }
              case PU_RBS: {
                base->life += 1000;
                if(base->life > base->lifeMax) base->life = base->lifeMax;
                break;
              }
            }
          }
          break;
        }
      }
      it = events.erase(it);
    }
    sendPowerUp();
    if(enemies.size())
      nextWave = getTime() + 5000;
    else if(waves.size())
      sendEnemy();
    else
      return GR_PW;
    Sleep(50);
  }
}

void Cooperation::sendPowerUp() {
  if(getTime() < nextPowerUp + 10000) return;
  int x = rand() % MAP_W;
  int y = rand() % (MAP_H - 12) + 6;
  if(Map::map[x][y].type == T_BNK) {
    auto p = new PowerUp(x, y, getTime() % N_POWER_UP);
    Map::map[x][y] = {T_PWU, p};
  }
  nextPowerUp = getTime();
}

void Cooperation::sendEnemy() {
  if(getTime() < nextWave) return;
  nextWave = getTime();
  for (int i = 0; i < 4 && waves.size(); i++) {
    auto w = waves.front();
    waves.pop_front();
    if(std::get<2>(w) == -1) continue;
    auto t = new AutoTank(std::get<0>(w), std::get<1>(w), std::get<2>(w));
    enemies.push_back(t);
    Render::Drawables.push_back(t);
  }
}

void Cooperation::renderResult() {
  switch(this->result) {
    case GR_PW: {
      Assets::renderLetter(4, 10, F_GRN, 'Y');
      Assets::renderLetter(10, 10, F_GRN, 'O');
      Assets::renderLetter(16, 10, F_GRN, 'U');
      Assets::renderLetter(28, 10, F_GRN, 'W');
      Assets::renderLetter(34, 10, F_GRN, 'I');
      Assets::renderLetter(40, 10, F_GRN, 'N');
      break;
    }
    case GR_PL: {
      Assets::renderLetter(2 , 10, F_RED, 'Y');
      Assets::renderLetter(8 , 10, F_RED, 'O');
      Assets::renderLetter(14, 10, F_RED, 'U');
      Assets::renderLetter(24, 10, F_RED, 'L');
      Assets::renderLetter(30, 10, F_RED, 'O');
      Assets::renderLetter(36, 10, F_RED, 'S');
      Assets::renderLetter(42, 10, F_RED, 'E');
      break;
    }
    default: {
      Assets::renderLetter(4 , 10, F_YLW, 'S');
      Assets::renderLetter(10, 10, F_YLW, 'U');
      Assets::renderLetter(16, 10, F_YLW, 'S');
      Assets::renderLetter(22, 10, F_YLW, 'P');
      Assets::renderLetter(28, 10, F_YLW, 'E');
      Assets::renderLetter(34, 10, F_YLW, 'N');
      Assets::renderLetter(40, 10, F_YLW, 'D');
      break;
    }
  }
  Render::renderString(20, 23, "    [  MODE  ]    ", F_WHT);
  Render::renderString(20, 24, "   CO-OPERATION   ", F_WHT);
  Render::renderString(14, 26, "    [ SCORE P1 ]            [ SCORE P2 ]    ", F_WHT);
  std::cout << "\033[32;1m\033[" << 28 << ";" << 29 << "H    " << std::setw(10) << std::setfill(' ') << scoreP1 << "              " << "\033[34;1m" << std::setw(10) << std::setfill(' ') << scoreP2 <<  std::endl;;
  Render::renderString(20, 29, "PRESS [ESC] TO EXIT", F_WHT);
}

int Arena::run() {
  Render::scene = SC_GRD;
  // Render::scene = SC_HLP;
  Sleep(3000);
  Render::scene = SC_GRN;
  Sleep(500);
  while(1) {
    // * user input and oprations
    while(kbhit()) {
      switch(getch()) {
      case 119: player1->move(D_UP); break;
      case 97:  player1->move(D_LT); break;
      case 115: player1->move(D_DN); break;
      case 100: player1->move(D_RT); break;
      case 105: player2->move(D_UP); break;
      case 106: player2->move(D_LT); break;
      case 107: player2->move(D_DN); break;
      case 108: player2->move(D_RT); break;
      case 27: {
        Render::scene = SC_GPS;
        while(Render::scene == SC_GPS) {
          Sleep(50);
          if(kbhit()) {
            switch(getch()) {
              case 13: {
                Render::scene = SC_GRD;
                break;
              }
              case 104: {
                Render::scene = SC_HLP;
                while(Render::scene != SC_GRD) {
                  Sleep(50);
                  if(kbhit() && getch() == 27)
                    break;
                }
                Render::scene = SC_GRN;
                Sleep(100);
                Render::scene = SC_GPS;
                break;
              }
              case 27: {
                return GR_EXT;
              }
            }
          }
        }
        Sleep(3000);
        Render::scene = SC_GRN;
        Sleep(500);
        break;
      }; 
      case 32: {
        Bullet *blt = player1->fire();
        if(blt != nullptr) {
          Render::Drawables.emplace_back(blt);
          Bullet::Bullets.emplace_back(blt);
        }
        break;
      } 
      case 13: {
        Bullet *blt = player2->fire();
        if(blt != nullptr) {
          Render::Drawables.emplace_back(blt);
          Bullet::Bullets.emplace_back(blt);
        }
        break;
      } 
      }
    }
    // * move bullets
    for(auto it = Bullet::Bullets.begin(); it != Bullet::Bullets.end();) {
      Bullet *blt = *it;
      if(blt->move()) {
          it = Bullet::Bullets.erase(it);
          Render::Drawables.remove(blt);
          delete blt;
      }
      else {
        ++it;
      }
    }
    // * bullet cancels each other
    for(auto it = Bullet::Bullets.begin(); it != Bullet::Bullets.end();++it)
      for(auto it2 = it; it2 != Bullet::Bullets.end();++it2)
        if((*it)->x == (*it2)->x && (*it)->y == (*it2)->y && it != it2)
          (*it)->toRemove = (*it2)->toRemove = 1;
    for(auto it = Bullet::Bullets.begin(); it != Bullet::Bullets.end();) {
      Bullet *blt = *it;
      if(blt->toRemove) {
        it = Bullet::Bullets.erase(it);
        Render::Drawables.remove(blt);
        delete blt;
      }
      else
        it++;
    }
    // * handle events
    for(auto it = events.begin(); it != events.end();) {
      auto e = *it;
      switch(std::get<0>(e)) {
        case EV_DST_TK: {
          auto dest = std::get<1>(e);
          // auto src = std::get<2>(e);
          Render::Drawables.remove(dest);
          dest->~Tank();
          if(dest == player1) {
            player1 = nullptr;
            scoreP2 += 1000;
            return GR_P2W;
          } 
          else {
            player2 = nullptr;
            scoreP1 += 1000;
            return GR_P1W;
          }
          break;
        }
        case EV_HIT_TK: {
          // auto dest = std::get<1>(e);
          auto src = std::get<2>(e);
          switch(src) {
            case CP_P1: scoreP1 += 100; break;
            case CP_P2: scoreP2 += 100; break;
            case CP_EN: break;
          }
          break;
        }
        case EV_GET_PW: {
          auto target = std::get<1>(e);
          auto type = std::get<2>(e);
          switch(type) {
            case PU_NLF: target->nLife++; break;
            case PU_UGD: target->weapon = target->weapon == BL_HE ? BL_HE : target->weapon + 1; break;
            case PU_CLK: {
              if(target->camp == CP_P1)
                player2->lastMove = player2->lastFire = getTime() + 3000;
              else
                player1->lastMove = player1->lastFire = getTime() + 3000;
              break;
            }
          }
          break;
        }
      }
      it = events.erase(it);
    }
    sendPowerUp();
    Sleep(50);
  }
}

void Arena::sendPowerUp() {
  if(getTime() < nextPowerUp + 10000) return;
  int x = rand() % MAP_W;
  int y = rand() % (MAP_H - 12) + 6;
  if(Map::map[x][y].type == T_BNK) {
    auto p = new PowerUp(x, y, getTime() % N_POWER_UP - 3);
    Map::map[x][y] = {T_PWU, p};
  }
  nextPowerUp = getTime();
}

void Arena::renderResult() {
  switch(this->result) {
    case GR_P1W: {
      Assets::renderLetter(4 , 10, F_GRN, 'Y');
      Assets::renderLetter(10, 10, F_GRN, 'O');
      Assets::renderLetter(16, 10, F_GRN, 'U');
      Assets::renderLetter(28, 10, F_BLU, 'Y');
      Assets::renderLetter(34, 10, F_BLU, 'O');
      Assets::renderLetter(40, 10, F_BLU, 'U');
      Assets::renderLetter(4 , 16, F_GRN, 'W');
      Assets::renderLetter(10, 16, F_GRN, 'I');
      Assets::renderLetter(16, 16, F_GRN, 'N');
      Assets::renderLetter(28, 16, F_BLU, 'L');
      Assets::renderLetter(34, 16, F_BLU, 'O');
      Assets::renderLetter(40, 16, F_BLU, 'S');
      break;
    }
    case GR_P2W: {
      Assets::renderLetter(4 , 10, F_GRN, 'Y');
      Assets::renderLetter(10, 10, F_GRN, 'O');
      Assets::renderLetter(16, 10, F_GRN, 'U');
      Assets::renderLetter(28, 10, F_BLU, 'Y');
      Assets::renderLetter(34, 10, F_BLU, 'O');
      Assets::renderLetter(40, 10, F_BLU, 'U');
      Assets::renderLetter(4 , 16, F_GRN, 'L');
      Assets::renderLetter(10, 16, F_GRN, 'O');
      Assets::renderLetter(16, 16, F_GRN, 'S');
      Assets::renderLetter(28, 16, F_BLU, 'W');
      Assets::renderLetter(34, 16, F_BLU, 'I');
      Assets::renderLetter(40, 16, F_BLU, 'N');
      break;
    }
    default: {
      Assets::renderLetter(4 , 10, F_YLW, 'S');
      Assets::renderLetter(10, 10, F_YLW, 'U');
      Assets::renderLetter(16, 10, F_YLW, 'S');
      Assets::renderLetter(22, 10, F_YLW, 'P');
      Assets::renderLetter(28, 10, F_YLW, 'E');
      Assets::renderLetter(34, 10, F_YLW, 'N');
      Assets::renderLetter(40, 10, F_YLW, 'D');
      break;
    }
  }
  Render::renderString(20, 23, "    [  MODE  ]    ", F_WHT);
  Render::renderString(20, 24, "       ARENA      ", F_WHT);
  Render::renderString(14, 26, "    [ SCORE P1 ]            [ SCORE P2 ]    ", F_WHT);
  std::cout << "\033[32;1m\033[" << 28 << ";" << 29 << "H    " << std::setw(10) << std::setfill(' ') << scoreP1 << "              " << "\033[34;1m" << std::setw(10) << std::setfill(' ') << scoreP2 <<  std::endl;;
  Render::renderString(20, 29, "PRESS [ESC] TO EXIT", F_WHT);
}



int MapEdit::run() {
  Render::scene = SC_GRN;
  Sleep(500);
  while(1) {
    // * user input and oprations
    while(kbhit()) {
      switch(getch()) {
      case 119: player1->move(D_UP); break;
      case 97:  player1->move(D_LT); break;
      case 115: player1->move(D_DN); break;
      case 100: player1->move(D_RT); break;
      case 49: player1->weapon = T_BNK; break;
      case 50: player1->weapon = T_GRS; break;
      case 51: player1->weapon = T_WTR; break;
      case 52: player1->weapon = T_STN; break;
      case 53: player1->weapon = T_WAL; break;
      case 32:  player1->fire(); break;      
      case 27:  return GR_EXT; break;
      }
    Sleep(50);
    }
  }
}


void MapEdit::renderResult() {
  Assets::renderLetter(10, 10, F_GRN, 'S');
  Assets::renderLetter(16, 10, F_GRN, 'A');
  Assets::renderLetter(22, 10, F_GRN, 'V');
  Assets::renderLetter(28, 10, F_GRN, 'E');
  Assets::renderLetter(34, 10, F_GRN, 'D');
  Render::renderString(14, 26, "        THE EDITED MAP IS GOOD TO GO        ", F_WHT);
  Render::renderString(20, 29, "PRESS [ESC] TO EXIT", F_WHT);
}