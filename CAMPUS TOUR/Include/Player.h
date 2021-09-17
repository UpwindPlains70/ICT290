#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "PlayerClass.h"
using namespace std;


class Player
{
public:
	Player();

	Player(int, string, string, int, int, int, int, int, int);

	~Player();

	void setID(int);

	int getID();

	void setName(string);

	string getName();

	void setClassType(string);

	string getClassType();

	void setHP(int);

	int getHP();

	void setStun(int);

	int getStun();

	void setPosX(int);

	int getPosX();

	void setPosZ(int);

	int getPosZ();

	void setMovementLeft(int);

	int getMovementLeft();

	void setTurn(int);

	int getTurn();

private:
	int id;
	string name;
	string classtype;
	int hp;
	int stun;
	int posX;
	int posZ;
	int movementleft;
	int turn;
	PlayerClass pc;
};

#endif