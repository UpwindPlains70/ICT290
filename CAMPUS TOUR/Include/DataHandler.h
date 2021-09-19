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

void GetCharacterData();
void GetEnemyData();
void GetEnemyPerLevelData();
void GetAbilityData();
EntityAbility GetAbility(string);
Enemy GetEnemy(string);
#endif