#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "EntityAbility.h"
#include "Enemy.h"

/**
	 * @brief Handles all character class, enemy, ability file reading
	 *
	 * @author Mark Burns
	 * @version 01
	 * @date 20/09/2021, Started
	 * 
	 * @author Peter Neve
	 * @version 02
	 * @date 24/09/2021, fixed minor issues (added tempNameList.clear & allowed for empty lines)
	 * 
	 * @author Mark Burns
	 * @version 03
	 * @date 27/09/2021, add upgradable health
	 * 
	 * @author Mark Burns
	 * @version 04
	 * @date 22/10/2021, change health upgrade
	 */

using namespace std;

//store each which level will spawn which enemy
//each level is in a struct
struct LevelEnemy
{
	int min;
	int max;
	vector<Enemy> presetList;

	void resetEnemy()
	{
		min = 0;
		max = 0;
		presetList.clear();
	}
};

//store each class as a struct to be used for a classes class when making the player
struct Class
{
	string name;
	int hp;
	int armor;
	int movement;
	vector<EntityAbility> abilityList;

	//reset data
	void resetClass()
	{
		name = " ";
		hp = 0;
		armor = 0;
		movement = 0;
		abilityList.clear();
	}
};

//Initialising
extern vector<Class> allClasses;
extern vector<Enemy> allEnemies;
void GetCharacterData();
void GetEnemyData();
void GetEnemyPerLevelData();
void GetAbilityData();
EntityAbility GetAbility(string);
Enemy GetEnemy(string);
extern vector<Enemy> allEnemies;
extern map<int, LevelEnemy> enemyLevelMap;
extern map<string, int> upgradeHP;
#endif