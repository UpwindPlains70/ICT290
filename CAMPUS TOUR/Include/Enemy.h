#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>
#include <vector>
#include "EntityAbility.h"
#include "MapLevel.h"
#include "Player.h"

//#include "UpdateHandler.h"
using namespace std;

class Enemy
{
public:
	Enemy();

	Enemy(string, int, int, int, int, int, int, int);

	~Enemy();

	void setName(string);

	string getName();

	void resetHP();

	int getHP();

	void setMaxHP(int);

	int getMaxHP();

	void setArmor(int);

	int getArmor();

	int getNumAbilities();

	void setStun(int);

	int getStun();

	void setPosX(int);

	int getPosX();

	void setPosZ(int);

	int getPosZ();

	void setMovement(int);

	int getMovement();

	void setTurn(int);

	int getTurn();

	void pushAbility(EntityAbility);

	void popAbility();

	void setAbility(EntityAbility, int);

	EntityAbility getAbility(int);

	void damageEnemy(int dam);

	void healEnemy(int heal);

	void reset();

	void shield(int);

	void unshield();

	void AITurn(LevelMap* nowMap, vector<Player> playerList);
	void AIAttack(LevelMap* nowMap, vector<Player>& playerList, int& summon);
	void attack(EntityAbility ability, Player& player, LevelMap* nowMap);
	void kbAttack(EntityAbility ability, Player& player, LevelMap* nowMap);
	int random_int(int min, int max);
	int rollTheDice(int bonus, int AC);
private:
	string name;
	int maxHP;
	int hp;
	int armor;
	int numAbilities;
	int stun;
	int posX;
	int posZ;
	int movement;
	int turn;
	int originalAC;
	vector <EntityAbility> abilities;
private:
	//movement
	void moveUp(LevelMap* nowMap);
	void moveDown(LevelMap* nowMap);
	void moveLeft(LevelMap* nowMap);
	void moveRight(LevelMap* nowMap);
	//ai
	bool checkRange(vector<Player> playerList);
	int* getTargetPos(vector<Player> p);
	int moveToTarget(int tempMove, LevelMap* nowMap, vector<Player> playerList);
};

#endif