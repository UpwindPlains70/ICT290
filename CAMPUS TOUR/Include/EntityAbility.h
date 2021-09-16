#pragma once

#ifndef ENTITYABILITY_H
#define ENTITYABILITY_H

#include <iostream>
using namespace std;

class EntityAbility
{
public:
	EntityAbility();

	EntityAbility(int, int, int, bool);

	~EntityAbility();

	void setToHit(int);

	int getToHit();

	void setNum(int);

	int getNum();

	void setDamage(int);

	int getDamage();

	void setUsed(bool);

	bool getUsed();

private:
	int tohit;
	int num;
	int damage;
	bool used;
};

#endif