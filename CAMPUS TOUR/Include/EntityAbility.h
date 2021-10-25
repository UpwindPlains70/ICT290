#pragma once

#ifndef ENTITYABILITY_H
#define ENTITYABILITY_H

#include <string>
#include <iostream>
using namespace std;
/**
 * @brief Defines class EntityAbility
 *
 * @author Mark Burns
 * @version 01
 * @date 17/09/2021, Started
 * 
 * @author Peter Neve
 * @version 02
 * @date 22/10/2021, changed cooldown to zero base
 */

class EntityAbility
{
public:
	EntityAbility();

	EntityAbility(string, int, int, int, int, int, int, int, int);

	~EntityAbility();

	void setToHit(int);

	int getToHit();

	void setDuplicate(int);

	int getDuplicate();

	void setDamage(int);

	int getDamage();

	void setUnique(int);

	int getUnique();

	void used();

	void setName(string);

	string getName();

	void setRange(int);

	int getRange();

	void setAOE(int);

	int getAOE();

	bool isAOE();

	void setStun(int);

	int getStun();

	void setCooldown(int);

	int getCooldown();

	int getCooldownCounter();

	void resetCooldownCounter();

	void roundPassed();

	bool canUseAbility();

	void zeroCooldownCounter();

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
	int unique;
};

#endif