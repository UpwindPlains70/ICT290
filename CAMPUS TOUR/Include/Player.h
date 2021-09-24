#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>
#include "EntityAbility.h"
using namespace std;

class Player
{
public:
	Player();

	Player(string, string, int, int, int, int, int, int, int);

	~Player();

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

	void setClassName(string);

	string getClassName();

	void damagePlayer(int);

	void healPlayer(int);

	void resetMovementLeft();
	
	void movePlayer();

	bool canMove();

	void noMovementLeft();

	int getNumberOfAbilities();

private:
	string name;
	string classType;
	int maxHP;
	int armor;
	int hp;
	int stun;
	int posX;
	int posZ;  
	int movement;
	int movementLeft;
	int turn;
	int numAbilities;
	vector<EntityAbility> abilities;
};

#endif