#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H
#pragma once
#include "CollisionHandler.h"
//#include "UpdateHandler.h"
#include "UIHandler.h"
#include "MapLevel.h"
#include "Player.h"
#include "Enemy.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

/**
	 * @brief defines all functions relating to levels
	 *
	 * @author Peter Neve
	 * @version 01
	 * @date 7/09/2021, level change
	 * 
	 * @author Mark Burns
	 * @version 02
	 * @date 7/09/2021, level maps
	 * 
	 * @author Peter Neve
	 * @version 03
	 * @date 15/09/2021, level maps gen redo (fixed movement)
	 * 
	 * @author Mark Burns
	 * @version 04
	 * @date 17/09/2021, Level map reader (.csv)
	 *  
	 * @author Peter Neve
	 * @version 05
	 * @date 18/09/2021, floor generation for maps
	 * 
	 * @author Peter Neve
	 * @version 06
	 * @date 19/10/2021, teleport to spawn added
	 * 
	 * @author Peter Neve
	 * @version 07
	 * @date 20/10/2021, fixed level 6 floor (issues with X-14, Z-5 & Z-6)
	 */

	 ///Size of each grid square
#define gridSquareSize 155

	///Global tracker for current level number
extern int currLevel;

	///Global variable storing all maps for the game
extern map<int, vector<LevelMap>> mapList;

	///Global tracker for current map preset
extern int mapID;

		/**
		 * @brief  teleports camera to game area
		 *
		 * @return void
		 */
void teleportCamera();

		/**
		 * @brief  check if player has gone far enough down the stairs to teleport
		 *
		 * @return void
		 */
bool levelZeroClear();

		/**
		 * @brief Read in 3D pillar object file
		 *
		 * @return void
		 */
void drawLevelObjects();

		/**
		 * @brief  draws and displays pillars in a wall structure
		 * @param bool - neg
		 *
		 * @return void
		 */
void displayWalls(bool neg);

		/**
		 * @brief  display the generated level map, uses set map X & Y value for size (length, width)
		 *
		 * @return void
		 */
void displayMap();

		/**
		 * @brief  Calcualtes the offsets of the floor and walls
		 *
		 * @return void
		 */
void displayFloor();

		/**
		 * @brief Sets objstical locations (update: load from file)
		 *
		 * @return void
		 */
void CreateMaps();

		/**
		 * @brief Display floor, pillars, enemies and players on the appropriate tiles
		 *
		 * @return void
		 */
void positionFloorObjects(vector<Enemy> nowEnemies, vector<Player> playerList);

		/**
		 * @brief Display all players and enemies based on their class/name
		 *
		 * @return void
		 */
void displayCharacterModels(vector<Enemy> nowEnemies, vector<Player> playerList);

		/**
		 * @brief Teleports player back to starting postion
		 *
		 * @return void
		 */
void teleportToSpawn();
#endif // !LEVELHANDLER_H


