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
 * 
 * @author Raymond Lau
 * @version 03
 * @date 26/09/2021, add ai connect to functions
 * 
 * @author Jason Botterill
 * @version 04
 * @date 27/09/2021, test model display
 * 
 * @author Mark Burns
 * @version 05
 * @date 27/09/2021, adding rolling, player movement and attacking
 * 
 * @author Jason Botterill
 * @version 06
 * @date 28/09/2021, add models and textures
 *
 * @author Jason Botterill
 * @version 07
 * @date 02/10/2021, add winning and losing screens
 *
 * @author Peter Neve
 * @version 08
 * @date 03/10/2021 resolver circular reference and merge
 * 
 * @author Jason Botterill
 * @version 09
 * @date 03/10/2021 add effects and add final screen
 *
 * @author Peter Neve
 * @version 10
 * @date 07/10/2021 add player and enemies to display model
 * 
 * @author Mark Burns
 * @version 11
 * @date 07/10/2021 only move when the new location is open
 * 
 * @author Jason Botterill
 * @version 12
 * @date 08/10/2021 fix berserker
 *
 * @author Mark Burns
 * @version 13
 * @date 08/10/2021 fix random_int()
 *
 * @author Mark Burns
 * @version 14
 * @date 09/10/2021 enemyTurn()
 * 
 * @author Mark Burns
 * @version 15
 * @date 15/10/2021 displayListOfEnemies
 * 
 * @author Jason Botterill
 * @version 16
 * @date 15/10/2021 testing models
 *
 * @author Peter Neve
 * @version 17
 * @date 19/10/2021 add rotation
 * 
 * @author Mark Burns
 * @version 18
 * @date 20/10/2021 add HP regen between levels and zero the cooldown
 *
 * @author Peter Neve
 * @version 19
 * @date 20/10/2021 Action cooldown
 * 
 * @author Mark Burns
 * @version 20
 * @date 21/10/2021 AOE Arrow
 * 
 * @author Raymond Lau
 * @version 21
 * @date 21/10/2021 Syntax fix
 * 
 * @author Peter Neve
 * @version 22
 * @date 22/10/2021 Enemy select fix
 * 
 * @author Raymond Lau
 * @version 23
 * @date 23/10/2021 corpses
 * 
 * @author Mark Burns
 * @version 24
 * @date 23/10/2021 logger and AOE fix
 */

//Initialising
extern enum state { NotGame, NotReady, Ready, Initialising, StartTurn, Action, Attack, Win, Lose, AttackAOE };
extern state gameState;
extern vector<Player> playerList;
extern int turn;
extern vector<Enemy> nowEnemies;
extern vector<int> turnList;
extern bool displayActionMenu;
extern bool allowedToRoll;
extern map<int, int> turnIDMap;
extern map<int, bool> isPCTurnMap;
extern bool displayEnt;
extern vector<Player> playerList;
extern vector<Enemy> nowEnemies;
extern bool canIJKL;
extern bool canAction;
extern bool canEndTurn;
extern int nowAbilityID;
extern int sessionRound;
extern bool pcHasAction;
extern int AOEArrowPosX;
extern int AOEArrowPosZ;
extern int originalArrowPosX;
extern int originalArrowPosZ;
void DisplayLinup();
void Update();
void endTurn();
void enemyTurn();
void playerTurn();
void upgrade();
void uniqueAbility();
void attack(int);
void AOEAbility();
void updatePopUpMessage();
int rollTheDice(int, int);
void movePlayer(int, int);
void moveArrow(int, int);
void abilityPressed(int);
int random_int(int, int);

#endif