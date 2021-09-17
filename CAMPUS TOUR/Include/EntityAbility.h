#pragma once

#ifndef ENTITYABILITY_H
#define ENTITYABILITY_H

#include <string>
#include <iostream>
using namespace std;

class EntityAbility
{
public:
	EntityAbility();

	EntityAbility(string, int, int, int, int, int, int, int, int, bool);

	~EntityAbility();

	void setToHit(int);

	int getToHit();

	void setDuplicate(int);

	int getDuplicate();

	void setDamage(int);

	int getDamage();

	void setUsed(bool);

	bool getUsed();

	void setName(string);

	string getName();

	void setRange(int);

	int getRange();

	void setAOE(int);

	int getAOE();

	void setStun(int);

	int getStun();

	void setCooldown(int);

	int getCooldown();

	void setCooldownCounter(int);

	int getCooldownCounter();

private:
	string name;
	int range;
	int aoe;
	int duplicate;
	int stun;
	int cooldown;
	int cooldownCounter;
	int tohit;
	int damage;
	bool used;
};

#endif