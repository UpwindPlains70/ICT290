#ifndef UPDATEHANDLER_H
#define UPDATEHANDLER_H
#pragma once

#include <string>
#include <map>
#include <vector>
#include "EntityAbility.h"
#include "Enemy.h"
#include "Player.h"
#include "MapLevel.h"
#include "LevelHandler.h"
#include "DataHandler.h"

extern enum state;
extern state gameState;
extern bool displayEnt;
extern vector<Player> playerList;
extern vector<Enemy> nowEnemies;
extern bool canIJKL;
extern bool canAction;
extern bool canEndTurn;

void Update();
void endTurn();
void enemyTurn(Enemy);
void playerTurn(Player);
void upgrade();
void uniqueAbility();
void attack(int);
int rollTheDice(int, int);
void movePlayer(int, int);
void abilityPressed(int);

#endif