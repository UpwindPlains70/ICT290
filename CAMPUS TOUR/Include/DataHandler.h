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

using namespace std;

struct LevelEnemy
{
	int min;
	int max;
	vector<string> presetList;
};

struct Class
{
	string name;
	int hp;
	int armor;
	int movement;
	vector<EntityAbility> abilityList;
};

void GetCharacterData();
void GetEnemyData();
void GetEnemyPerLevelData();
void GetAbilityData();
#endif