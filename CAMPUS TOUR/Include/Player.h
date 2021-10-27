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

	/**
	* @brief  Sets Player name
	*
	* This function sets player name
	*
	* @param  string
	*/
	void setName(string);

	/**
	* @brief  returns player name
	*
	* This function returns the registered name
	*
	* @return string
	*/
	string getName();

	/**
	* @brief  Resets HP to max
	*
	* This function returns hp to max
	*/
	void resetHP();

	/**
	* @brief  returns player hp
	*
	* This function returns current player hp
	*
	* @return int
	*/
	int getHP();

	/**
	* @brief  Sets player max hp
	*
	* This function sets player max hp
	*
	* @param int
	*/
	void setMaxHP(int);

	/**
	* @brief  returns player max hp
	*
	* This function returns player's max hp
	*
	* @return int
	*/
	int getMaxHP();

	/**
	* @brief  Sets player armour class
	*
	* This function sets player armour class
	*
	* @param int
	*/
	void setArmor(int);

	/**
	* @brief  returns player armour class
	*
	* This function returns player's armour class
	*
	* @return int
	*/
	int getArmor();

	/**
	* @brief  return number of abilities the player has
	* 
	* return int
	*
	*/
	int getNumAbilities();

	/**
	* @brief  Sets player current stun value
	*
	* This function sets player current stun value
	*
	* @param int
	*/
	void setStun(int);

	/**
	* @brief  returns player current stun value
	*
	* This function returns player current stun value
	*
	* @return int
	*/
	int getStun();

	/**
	* @brief  Sets player current position X value
	*
	* This function sets player current position X value
	*
	* @param int
	*/
	void setPosX(int);

	/**
	* @brief  returns player current position X value
	*
	* This function returns player current position X value
	*
	* @return int
	*/
	int getPosX();

	/**
	* @brief  Sets player current position Z value
	*
	* This function sets player current position Z value
	*
	* @param int
	*/
	void setPosZ(int);

	/**
	* @brief  returns player current position Z value
	*
	* This function returns player current position Z value
	*
	* @return int
	*/
	int getPosZ();

	/**
	* @brief  Sets player current max movement
	*
	* This function sets player max movement
	*
	* @param int
	*/
	void setMovement(int);

	/**
	* @brief  returns player max movement
	*
	* This function returns player max movement
	*
	* @return int
	*/
	int getMovement();

	/**
	* @brief  returns player leftover movement
	*
	* This function returns player current leftover movement
	*
	* @return int
	*/
	int getMovementLeft();

	/**
	* @brief  Sets player current turn number
	*
	* This function sets player current turn number, allocated randomly in update handler
	*
	* @param int
	*/
	void setTurn(int);

	/**
	* @brief  returns player current turn number
	*
	* This function returns player current turn number, allocated randomly in update handler
	*
	* @return int
	*/
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

	/**
	* @brief  sets the ability
	*
	* This function sets the ability for the player
	*
	* @param EntityAbility
	*/
	void setAbility(EntityAbility, int);

	/**
	* @brief  returns ability's identifier
	*
	* This function returns ability's identifier
	*
	* @return int
	*/
	EntityAbility getAbility(int);

	/**
	* @brief  Sets class name for player
	*
	* @param string
	*/
	void setClassName(string);

	/**
	* @brief  Returns player's class name
	*
	* @return int*
	*/
	string getClassName();

	/**
	* @brief  reduces/damages player health
	*
	* This function reduces the health of the player
	*
	* @param int dam
	*/
	void damagePlayer(int);

	/**
	* @brief  heals player health
	*
	* This function increases the health of the player
	*
	* @param int heal
	*/
	void healPlayer(int);

	/**
	* @brief resets movement left to max movement
	* 
	* @param int heal
	*/
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

	/**
	* @brief Causes movement left to be 0
	*/
	void noMovementLeft();

	/**
	* @brief returns size of all listed abilities in ability list
	* 
	* @return int
	*/
	int getNumberOfAbilities();

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
	* @brief  returns a bool stating if damage is to be boosted
	* 
	* @return bool
	*/
	bool damageBoosted();

	/**
	* @brief  sets if damage is to be boosted
	*
	* @param bool
	*/
	void setDamageBoost(bool);

	/**
	* @brief  checks range based on a x and z input
	*
	* @return int x, int z
	*/
	int checkRange(int x, int z);

	/**
	* @brief  Sets rotation of player
	*
	* @param float
	*/
	void setRotation(float);

	/**
	* @brief  returns current rotation of character
	*
	* @return float const
	*/
	float getRotation() const;

	/**
	* @brief rotates character based on movement
	*
	* @return int x, int z
	*/
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