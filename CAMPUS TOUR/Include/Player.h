#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>
#include "EntityAbility.h"
using namespace std;

/**
 * @brief Defines player class
 *
 *
 * @author Mark Burns
 * @version 01
 * @date 20/09/2021 Started
 *
 * @author Peter Neve
 * @version 02
 * @date 25/09/2021, added getMovementLeft, setAbilities with existing vector
 * 
 * @author Peter Neve
 * @version 03
 * @date 20/10/2021, added rotation storage & funtionality
 * 
 */

class Player
{
public:
		/**
		 * @brief  Default constructor
		 *
		 */
	Player();

		/**
		* @brief  Player constructor
		*
		* This contructor creates a player with values
		*
		* @param  string - name
		* @param  string - class
		* @param  int - max HP
		* @param  int - max movement
		* @param  int - max armour
		* 
		*/
	Player(string, string, int, int, int);
		/**
		 * @brief  deconstructor
		 *
		 */
	~Player();

	void setName(string);

	string getName();

	void resetHP();

	int getHP();

	void setMaxHP(int);

	int getMaxHP();

	void setArmor(int);

	int getArmor();
		/**
		* @brief  return number of abilities the player has
		* 
		* return int
		*
		*/
	int getNumAbilities();

	void setStun(int);

	int getStun();

	void setPosX(int);

	int getPosX();

	void setPosZ(int);

	int getPosZ();

	void setMovement(int);

	int getMovement();

	int getMovementLeft();

	void setTurn(int);

	int getTurn();
		/**
		 * @brief  add abilities to player
		 *
		 * return void
		 */
	void pushAbility(EntityAbility);

		/**
		 * @brief  remove abilities from player
		 *
		 * return void
		 */
	void popAbility();

		/**
		* @brief  set list of abilities to player
		*
		* return void
		*/
	void setAbilities(vector<EntityAbility> newList);

	void setAbility(EntityAbility, int);

	EntityAbility getAbility(int);

	void setClassName(string);

	string getClassName();

	void damagePlayer(int);

	void healPlayer(int);

	void resetMovementLeft();
	
		/**
		 * @brief  Edits the players remaining movement
		 * 
		 * return void
		 */
	void movePlayer();
		/**
		 * @brief Limits who much a player can move
		 *
		 * return bool
		 */
	bool canMove();

	void noMovementLeft();

	int getNumberOfAbilities();

	void shield(int);

	void unshield();

	bool damageBoosted();

	void setDamageBoost(bool);

	int checkRange(int x, int z);

	void setRotation(float);
	float getRotation() const;
	void rotatePlayer(int X, int Z);
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
	int originalAC;
	bool damageBoost;
	float rotation;
	vector<EntityAbility> abilities;
};

#endif