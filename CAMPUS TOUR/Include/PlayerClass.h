#pragma once
//useless at the moment

#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include <string>
#include <iostream>
#include "EntityAbility.h"
using namespace std;


class PlayerClass
{
public:
	PlayerClass();

	PlayerClass(int, int, int, string, string, string);

	~PlayerClass();

	void setMaxHP(int);

	int getMaxHP();

	void setArmor(int);

	int getArmor();

	void setMovement(int);

	int getMovement();

	void setAbility1(string);

	string getAbility1();

	void setAbility2(string);

	string getAbility2();

	void setAbility3(string);

	string getAbility3();

private:
	int maxhp;
	int armor;
	int movement;
	string ability1;
	string ability2;
	string ability3;
	EntityAbility abilities[3];
};

#endif