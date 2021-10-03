#pragma once

#ifndef DATHANDLER_H //weird fix
#define DATHANDLER_H

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
	 */
using namespace std;

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

struct Class
{
	string name;
	int hp;
	int armor;
	int movement;
	vector<EntityAbility> abilityList;

	void resetClass()
	{
		name = " ";
		hp = 0;
		armor = 0;
		movement = 0;
		abilityList.clear();
	}
};

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