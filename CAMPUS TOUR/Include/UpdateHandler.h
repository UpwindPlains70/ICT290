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
#include "UIHandler.h"

/**
 * @brief Defines all User Interface menus
 *
 *
 * @author Mark Burns
 * @version 01
 * @date 21/09/2021 Started
 *
 * @author Peter Neve
 * @version 02
 * @date 25/09/2021 implented UI (added displayActionMenu, allowedToRoll bools)
 */
extern enum state { NotReady, Ready, Initialising, StartTurn, Action, Attack, Win, Lose, AttackAOE };
extern state gameState;
extern vector<Player> playerList;
extern int turn;
extern vector<Enemy> nowEnemies;
extern vector<int> turnList;
extern bool displayActionMenu;
extern bool allowedToRoll;
	///turnIDMap - (map<int, int>), maps turns to player/enemy indexes
extern map<int, int> turnIDMap;
	///isPCTurnMap - (map<int, bool>), maps players based on turn to have current turn
extern map<int, bool> isPCTurnMap;

void Update();
void endTurn();
void enemyTurn(Enemy);
void playerTurn(Player);
void upgrade();
void uniqueAbility();
void attack(int);

#endif