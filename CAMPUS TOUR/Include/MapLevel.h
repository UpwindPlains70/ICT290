#pragma once

/**
	 * @brief defines all functions relating to level map
	 *
	 * @author Mark Burns
	 * @version 01
	 * @date 17/09/2021, Started
	 */
class LevelMap
{
private:
	/// 0 = empty, 1 = wall, 2 = player, 3 = enemy.
	///two-dimension of 
	int** array;
		///X size of map
	int X;
		///Z size of map
	int Z;
		
		/**
		 * @brief copy constuctor
		 *
		 * @return void
		 */
	void CopyMap(const LevelMap& copy);
public:
			/**
		 * @brief  Custom constructor 
		 *
		 *
		 *
		 * @param int - x size
		 * @param int - z size
		 * @return void
		 */
	LevelMap(int x, int z);		
	
		/**
		 * @brief  get X value
		 *
		 * @return void
		 */
	int GetX() const;	
	
		/**
		 * @brief  get max Z value
		 *
		 * @return void
		 */
	int GetZ() const;	
	
		/**
		 * @brief  get value of maps tile
		 *
		 * @return void
		 */
	int GetValue(int x, int z) const;	
	
		/**
		 * @brief  Set tile value of map 
		 *
		 * @return void
		 */
	void SetValue(int x, int z, int value);	
	
		/**
		 * @brief  copy constructor
		 *
		 * @return void
		 */
	LevelMap(const LevelMap& copy);	
	
		/**
		 * @brief deconstructor
		 *
		 * @return void
		 */
	~LevelMap();	
	
		/**
		 * @brief  = overload
		 *
		 *	Performs deep copy
		 *
		 * @return void
		 */
	const LevelMap& operator =(const LevelMap& copy);
};