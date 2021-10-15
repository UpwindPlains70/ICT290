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

#include "UIHandler.h"

#include "DataHandler.h"


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
extern enum state { NotGame, NotReady, Ready, Initialising, StartTurn, Action, Attack, Win, Lose, AttackAOE };
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

extern bool displayEnt;
extern vector<Player> playerList;
extern vector<Enemy> nowEnemies;
extern bool canIJKL;
extern bool canAction;
extern bool canEndTurn;
extern int nowAbilityID;
extern int sessionRound;

void DisplayLinup();
void Update();
void endTurn();
void enemyTurn();
void playerTurn();
void upgrade();
void uniqueAbility();
void attack(int);

void updateModels();
void updatePopUpMessage();

int rollTheDice(int, int);
void movePlayer(int, int);
void abilityPressed(int);
int random_int(int, int);


#endif