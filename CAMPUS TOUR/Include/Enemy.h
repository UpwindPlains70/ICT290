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

/**
 * @brief Defines all Enemy modules and AI
 *
 *
 * @author Raymond Lau
 * @version 01
 * @date 20/09/2021 Started
 * 
 * @author Raymond Lau
 * @version 02
 * @date 28/9/2021 added Enemy AI
 * 
 * @author Mark Burns
 * @version 03
 * @date 03/10/2021 edited enemy movement i.e. moveUp, moveDown, moveLeft, moveRight
 * 
 * @author Raymond Lau
 * @version 04
 * @date 18/10/2021 added Enemy AI attack capabilities and dice rolling
 */

class Enemy
{
public:
	Enemy();

	Enemy(string, int, int, int, int, int, int, int);

	~Enemy();

	/**
	* @brief  Sets Enemy name
	*
	* This function sets enemy names stated on the enemy.csv file
	*
	* @param  string
	*/
	void setName(string);

	/**
	* @brief  returns enemy name
	*
	* This function returns the name of the enemy obj
	*
	* @return string
	*/
	string getName();

	/**
	* @brief  resets enemy hp
	*
	* This function resets the enemy hp to default state, stated in the enemy.csv file
	*/
	void resetHP();

	/**
	* @brief  returns enemy hp
	*
	* This function returns current enemy hp
	*
	* @return int
	*/
	int getHP();

	/**
	* @brief  Sets enemy max hp
	*
	* This function sets enemy max hp
	*
	* @param int
	*/
	void setMaxHP(int);

	/**
	* @brief  returns enemy max hp
	*
	* This function returns enemy's max hp
	*
	* @return int
	*/
	int getMaxHP();

	/**
	* @brief  Sets enemy armour class
	*
	* This function sets enemy armour class
	*
	* @param int
	*/
	void setArmor(int);

	/**
	* @brief  returns enemy armour class
	*
	* This function returns enemy's armour class
	*
	* @return int
	*/
	int getArmor();

	/**
	* @brief  returns enemy current number of abilities
	*
	* This function returns enemy's current number of abilities
	*
	* @return int
	*/
	int getNumAbilities();

	/**
	* @brief  Sets enemy current stun value
	*
	* This function sets enemy current stun value
	*
	* @param int
	*/
	void setStun(int);

	/**
	* @brief  returns enemy current stun value
	*
	* This function returns enemy current stun value
	*
	* @return int
	*/
	int getStun();

	/**
	* @brief  Sets enemy current position X value
	*
	* This function sets enemy current position X value
	*
	* @param int
	*/
	void setPosX(int);

	/**
	* @brief  returns enemy current position X value
	*
	* This function returns enemy current position X value
	*
	* @return int
	*/
	int getPosX();

	/**
	* @brief  Sets enemy current position Z value
	*
	* This function sets enemy current position Z value
	*
	* @param int
	*/
	void setPosZ(int);

	/**
	* @brief  returns enemy current position Z value
	*
	* This function returns enemy current position Z value
	*
	* @return int
	*/
	int getPosZ();

	/**
	* @brief  Sets enemy current max movement
	*
	* This function sets enemy max movement
	*
	* @param int
	*/
	void setMovement(int);

	/**
	* @brief  returns enemy max movement
	*
	* This function returns enemy max movement
	*
	* @return int
	*/
	int getMovement();

	/**
	* @brief  Sets enemy current turn number
	*
	* This function sets enemy current turn number, allocated randomly in update handler
	*
	* @param int
	*/
	void setTurn(int);

	/**
	* @brief  returns enemy current turn number
	*
	* This function returns enemy current turn number, allocated randomly in update handler
	*
	* @return int
	*/
	int getTurn();

	/**
	* @brief  Adds an ability to a enemy
	*
	* This function allocates an ability to the enemy, for use in battle
	*
	* @param EntityAbility
	*/
	void pushAbility(EntityAbility);

	/**
	* @brief  removes an ability to a enemy
	*
	* This function removes an ability from the enemy
	*
	* @param EntityAbility
	*/
	void popAbility();

	void setAbility(EntityAbility, int);

	EntityAbility getAbility(int);

	/**
	* @brief  reduces/damages enemy health
	*
	* This function reduces the health of the enemy
	*
	* @param int dam
	*/
	void damageEnemy(int dam);

	/**
	* @brief  heals enemy health
	*
	* This function increases the health of the enemy
	*
	* @param int heal
	*/
	void healEnemy(int heal);

	/**
	* @brief  resets enemy object
	*
	* This function resets enemy object into a blank slate
	*/
	void reset();

	/**
	* @brief  Alters enemy's current armour class
	*
	* This function alters enemy's current armour class
	*
	* @param int
	*/
	void shield(int);

	/**
	* @brief  resets all alterations to enemy's armour class
	*
	* This function reverts enemy's current armour class to initial AC
	*/
	void unshield();

	/**
	* @brief  Initiates enemy AI for the turn
	*
	* This function activates the AI for the enemy object during its "turn"
	*
	* @param LevelMap* nowMap, vector<Player> playerList
	*/
	void AITurn(LevelMap* nowMap, vector<Player> playerList);

	/*float getRotation();
	void setRotation(float newRot);
	void rotateEnemy(int X, int Z);*/

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
	//float rotation;
	vector <EntityAbility> abilities;
private:
	/**
	* @brief  Moves enemy up the grid
	*
	* This function moves the enemy object up the grid
	*
	* @param LevelMap* nowMap
	*/
	void moveUp(LevelMap* nowMap);

	/**
	* @brief  Moves enemy down the grid
	*
	* This function moves the enemy object down the grid
	*
	* @param LevelMap* nowMap
	*/
	void moveDown(LevelMap* nowMap);

	/**
	* @brief  Moves enemy left from the grid
	*
	* This function moves the enemy object left from the grid
	*
	* @param LevelMap* nowMap
	*/
	void moveLeft(LevelMap* nowMap);

	/**
	* @brief  Moves enemy right from the grid
	*
	* This function moves the enemy object right from the grid
	*
	* @param LevelMap* nowMap
	*/
	void moveRight(LevelMap* nowMap);

	/**
	* @brief  Checks ranges of abilities if character is within range
	*
	* This function checks all abilities ranges if a player is in range
	*
	* @param vector<Player> playerList
	*
	* @return bool
	*/
	bool checkRange(vector<Player> playerList);

	/**
	* @brief  Gets closest player position
	*
	* This function acquires the closest player position and returns it
	*
	* @param vector<Player> p
	*
	* @return int*
	*/
	int* getTargetPos(vector<Player> p);

	/**
	* @brief  Moves enemy obj to closest player
	*
	* This function uses the position acquired by getTargetPos and moves closer based on the amount of allocated movement the enemy obj has
	*
	* @param vector<Player> p
	*
	* @return int*
	*/
	int moveToTarget(int tempMove, LevelMap* nowMap, vector<Player> playerList);

	/**
	* @brief  Enemy AI attack functions
	*
	* This function is called by AIAttack when a basic ability is used to attack
	*
	* @param EntityAbility ability, Player& player, LevelMap* nowMap
	*/
	void attack(EntityAbility ability, Player& player, LevelMap* nowMap);

	/**
	* @brief  Enemy AI attack functions for knockback attacks
	*
	* This function is called by AIAttack when a ability with knockback is used to attack
	*
	* @param EntityAbility ability, Player& player, LevelMap* nowMap
	*/
	void kbAttack(EntityAbility ability, Player& player, LevelMap* nowMap);

	/**
	* @brief  Activates enemy AI attack functions
	*
	* This function is called by AIturn when an player is within range to allow the enemy to attack the player with on of its abilities
	*
	* @param LevelMap* nowMap, vector<Player>& playerList, int& summon
	*/
	void AIAttack(LevelMap* nowMap, vector<Player>& playerList, int& summon);

	/**
	* @brief  Searches for a random number between a min and max number
	*
	* This function is searches for a random number between a allocated min and max number
	*
	* @param int min, int max
	* 
	* @return int
	*/
	int random_int(int min, int max);

	/**
	* @brief  Used by all characters in the attempt to hit an opponent
	*
	* This function mimics the D20 roll of a regular DND roll
	* 
	* @param int bonus, int AC
	*
	* @return int
	*/
	int rollTheDice(int bonus, int AC);
};

#endif