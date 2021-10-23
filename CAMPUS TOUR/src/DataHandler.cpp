#include "DataHandler.h"

//Initialising
vector<Class> allClasses;
vector<EntityAbility> allAbilities;
vector<Enemy> allEnemies;
map<int, LevelEnemy> enemyLevelMap;
map<string, int> upgradeHP;

using namespace std;

//retrieve and sort through classes.csv
void GetCharacterData()
{
	fstream classFile("data/Class/classes.csv");
	string tmp;
	string tempString;
	string tempName;
	int tempHP;
	int tempArmor;
	int tempMovement;
	int bonus;
	EntityAbility tempAbility;
	string tempAbilityName;
	vector<string> tempAbilityNameList;
	Class tempClass;

	//error if no file
	if (!classFile)
	{
		cout << "Error: get character data" << endl;
		return;
	}

	//Each line of file
	while (!classFile.eof())
	{
		getline(classFile, tmp);
		if(tmp.empty())
			continue;
		//retrieve class data
		stringstream element(tmp);
		getline(element, tempString, ',');
		istringstream(tempString) >> tempName;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempHP;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempArmor;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempMovement;

		//Can be more then 1 ability
		while (!element.eof())
		{
			getline(element, tempString, ',');
			istringstream(tempString) >> tempAbilityName;
			tempAbilityNameList.push_back(tempAbilityName);
		}

		//reset previous data from tempClass
		tempClass.resetClass();

		//fill tempClass
		tempClass.name = tempName;
		tempClass.hp = tempHP;
		tempClass.armor = tempArmor;
		tempClass.movement = tempMovement;
		for (int i = 0; i < tempAbilityNameList.size(); i++)
		{
			tempAbilityName = tempAbilityNameList.at(i);
			tempAbility = GetAbility(tempAbilityName);
			tempClass.abilityList.push_back(tempAbility);
		}

		//add bonus to class using hp data
		bonus = tempClass.hp / 3;
		upgradeHP.insert(std::pair<string, int>(tempClass.name, bonus));

		//add tempClass to list of classes
		allClasses.push_back(tempClass);
		tempAbilityNameList.clear();
	}

	//close file
	classFile.close();
}

//get an ability by using its name
EntityAbility GetAbility(string name)
{
	EntityAbility anAbility;

	//look through each possible ability
	for (int i = 0; i < allAbilities.size(); i++)
	{
		anAbility = allAbilities.at(i);
		if(name == anAbility.getName())
		{
			return anAbility;
		}
	}

	//use last ability if no ability is found
	return anAbility;
}

//get an enemy by using its name
Enemy GetEnemy(string name)
{
	Enemy anEnemy;

	//look through each possible enemy
	for (int i = 0; i < allEnemies.size(); i++)
	{
		anEnemy = allEnemies.at(i);
		if (name == anEnemy.getName())
		{
			return anEnemy;
		}
	}

	//use last enemy if no ability is found
	return anEnemy;
}

//retrieve and sort through enemies.csv
void GetEnemyData()
{
	//Initialising
	fstream enemyFile("data/Levels/enemies.csv");
	string tmp;
	string tempString;
	string tempName;
	int tempHP;
	int tempArmor;
	int tempMovement;
	EntityAbility tempAbility;
	string tempAbilityName;
	vector<string> tempAbilityNameList;
	Enemy tempEnemy;

	//error if no file
	if (!enemyFile)
	{
		cout << "Error: get enemy data" << endl;
		return;
	}

	//go through each line
	while (!enemyFile.eof())
	{
		getline(enemyFile, tmp);
		if(tmp.empty())
			continue;

		//fill enemy list
		stringstream element(tmp);
		getline(element, tempString, ',');
		istringstream(tempString) >> tempName;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempHP;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempArmor;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempMovement;

		//for the case of more then 1 ability
		while (!element.eof())
		{
			getline(element, tempString, ',');
			istringstream(tempString) >> tempAbilityName;
			tempAbilityNameList.push_back(tempAbilityName);
		}

		//reset and set temporary enemy class
		tempEnemy.reset();
		tempEnemy.setMaxHP(tempHP);
		tempEnemy.setName(tempName);
		tempEnemy.resetHP();
		tempEnemy.setArmor(tempArmor);
		tempEnemy.setMovement(tempMovement);
		for (int i = 0; i < tempAbilityNameList.size(); i++)
		{
			tempAbilityName = tempAbilityNameList.at(i);
			tempAbility = GetAbility(tempAbilityName);
			tempEnemy.pushAbility(tempAbility);
		}

		//add enemy to list
		allEnemies.push_back(tempEnemy);
		tempAbilityNameList.clear();
	}

	//close file
	enemyFile.close();
}

//retrieve and sort through enemiesPerLevel.csv
void GetEnemyPerLevelData()
{
	//Initialising
	fstream EPLFile("data/Levels/enemiesPerLevel.csv");
	string tmp;
	string tempString;
	string tempName;
	int tempLevel;
	int tempMin;
	int tempMax;
	Enemy tempEnemy;
	string tempEnemyName;
	vector<string> tempEnemyNameList;
	LevelEnemy tempLevelEnemy;

	//error if no file
	if (!EPLFile)
	{
		cout << "Error: get enemy per level data" << endl;
		return;
	}

	//go through each line
	while (!EPLFile.eof())
	{
		getline(EPLFile, tmp);
		if(tmp.empty())
			continue;

		//fill enemy list per level
		stringstream element1(tmp);
		getline(element1, tempString, ',');
		istringstream(tempString) >> tempLevel;
		getline(element1, tempString, ',');
		istringstream(tempString) >> tempMin;
		getline(element1, tempString, ',');
		istringstream(tempString) >> tempMax;
		getline(EPLFile, tmp);
		stringstream element(tmp);

		//for the case of more then 1 ability
		while (!element.eof())
		{
			getline(element, tempString, ',');
			istringstream(tempString) >> tempEnemyName;
			tempEnemyNameList.push_back(tempEnemyName);
		}

		//reset and set temporary enemy class
		tempLevelEnemy.resetEnemy();
		tempLevelEnemy.min = tempMin;
		tempLevelEnemy.max = tempMax;
		for (int i = 0; i < tempEnemyNameList.size(); i++)
		{
			tempEnemyName = tempEnemyNameList.at(i);
			tempEnemy = GetEnemy(tempEnemyName);
			tempLevelEnemy.presetList.push_back(tempEnemy);
		}

		//add enemy per level to list
		enemyLevelMap[tempLevel] = tempLevelEnemy;
		tempEnemyNameList.clear();
	}
	
	//close file
	EPLFile.close();
}

//retrieve and sort through abilities.csv
void GetAbilityData()
{
	//Initialising
	fstream abilityFile("data/Class/abilities.csv");
	string tmp;
	string tempString;
	string tempName;
	int tempRange;
	int tempAOE;
	int tempDuplicate;
	int tempDamage;
	int tempToHit;
	int tempStun;
	int tempCooldown;
	int tempUnique;
	EntityAbility tempAbility;

	//error if no file
	if (!abilityFile)
	{
		cout << "Error: get ability data" << endl;
		return;
	}
	getline(abilityFile, tmp);

	//go through each line
	while (!abilityFile.eof())
	{
		getline(abilityFile, tmp);
		if(tmp.empty())
			continue;

		//fill ability list
		stringstream element(tmp);
		getline(element, tempString, ',');
		istringstream(tempString) >> tempName;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempRange;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempAOE;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempDuplicate;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempDamage;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempToHit;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempStun;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempCooldown;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempUnique;

		tempAbility = EntityAbility(tempName, tempRange, tempAOE, tempDuplicate, tempStun, tempCooldown, tempUnique, tempToHit, tempDamage);

		//add to ability list
		allAbilities.push_back(tempAbility);
	}

	//close file
	abilityFile.close();
}