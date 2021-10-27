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

	/**
	* @brief  Sets to hit variable
	*
	* This function sets to hit variable 
	*
	* @param  int
	*/
	void setToHit(int);

	/**
	* @brief  returns to hit variable
	*
	* This function returns the to hit variable
	*
	* @return int
	*/
	int getToHit();

	/**
	* @brief  Sets to duplicate variable
	*
	* This function sets to duplicate variable
	*
	* @param  int
	*/
	void setDuplicate(int);

	/**
	* @brief  returns duplicate variable
	*
	* This function returns the duplicate variable
	*
	* @return int
	*/
	int getDuplicate();

	/**
	* @brief  Sets damage dealt
	* 
	* This function sets damage dealt
	*
	* @param  int
	*/
	void setDamage(int);

	/**
	* @brief  returns damage dealt
	*
	* This function returns the damage dealt
	*
	* @return int
	*/
	int getDamage();

	/**
	* @brief  Sets to unique variable
	*
	* This function sets to unique variable
	*
	* @param  int
	*/
	void setUnique(int);

	/**
	* @brief  returns to unique variable
	*
	* This function returns the to unique variable
	*
	* @return int
	*/
	int getUnique();

	/**
	* @brief  Sets ability as used
	*
	* This function activates ability's cooldown
	*/
	void used();

	/**
	* @brief  Sets name
	*
	* This function sets name of ability
	*
	* @param  string
	*/
	void setName(string);

	/**
	* @brief  returns name
	*
	* This function returns name of ability
	*
	* @return string
	*/
	string getName();

	/**
	* @brief  Sets range 
	*
	* This function sets range of ability
	*
	* @param  int
	*/
	void setRange(int);

	/**
	* @brief  returns range
	*
	* This function returns range of ability
	*
	* @return int
	*/
	int getRange();

	/**
	* @brief  Sets to AOE variable
	*
	* This function sets AOE variable
	*
	* @param  int
	*/
	void setAOE(int);

	/**
	* @brief  returns AOE variable
	*
	* This function returns the AOE variable
	*
	* @return int
	*/
	int getAOE();

	/**
	* @brief  checks ability if its AOE
	*
	* This function checks ability for AOE tag
	*
	* @return bool
	*/
	bool isAOE();

	/**
	* @brief  Sets to stun variable
	*
	* This function sets stun variable
	*
	* @param  int
	*/
	void setStun(int);

	/**
	* @brief  returns stun variable
	*
	* This function returns the stun variable
	*
	* @return int
	*/
	int getStun();

	/**
	* @brief  Sets cooldown 
	*
	* This function sets cooldown
	*
	* @param  int
	*/
	void setCooldown(int);

	/**
	* @brief  returns cooldown
	*
	* This function returns the cooldown of the ability
	*
	* @return int
	*/
	int getCooldown();

	/**
	* @brief  returns cooldown counter
	*
	* This function returns cooldown counter
	*
	* @return int
	*/
	int getCooldownCounter();

	/**
	* @brief  resets ability cooldown
	*
	* This function resets ability cooldown
	*/
	void resetCooldownCounter();

	/**
	* @brief  lowers ability cooldown
	*
	* This function lowers ability cooldown by 1
	*/
	void roundPassed();

	/**
	* @brief  checks if ability can be used
	*
	* This function checks if ability can be used based on its cooldown
	*
	* @return bool
	*/
	bool canUseAbility();

	/**
	* @brief  Hard resets cooldown to 0
	*
	* This function resets ability cooldown to 0
	*/
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