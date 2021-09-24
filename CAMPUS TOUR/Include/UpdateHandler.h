#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#pragma once

#include <string>
#include <map>
#include <vector>
#include "EntityAbility.h"
#include "Enemy.h"
#include "Player.h"
#include "MapLevel.h"
#include "LevelHandler.h"

extern enum state;
extern state gameState;
extern bool displayEnt;

void Update();
void endTurn();
void enemyTurn(Enemy);
void playerTurn(Player);
void upgrade();
void uniqueAbility();
void attack(int);

#endif