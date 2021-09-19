#include "DataHandler.h"

vector<Class> allClasses;
vector<EntityAbility> allAbilities;
vector<Enemy> allEnemies;
map<int, LevelEnemy> enemyLevelMap;

using namespace std;

void GetCharacterData()
{
	fstream classFile("data/Class/classes.csv");
	string tmp;
	string tempString;
	string tempName;
	int tempHP;
	int tempArmor;
	int tempMovement;
	EntityAbility tempAbility;
	string tempAbilityName;
	vector<string> tempAbilityNameList;
	Class tempClass;
	if (!classFile)
	{
		cout << "Error" << endl;
		return;
	}
	while (!classFile.eof())
	{
		getline(classFile, tmp);
		stringstream element(tmp);
		getline(element, tempString, ',');
		istringstream(tempString) >> tempName;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempHP;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempArmor;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempMovement;
		while (true)
		{
			getline(element, tempString, ',');
			if (tempString == "");
			{
				break;
			}
			istringstream(tempString) >> tempAbilityName;
			tempAbilityNameList.push_back(tempAbilityName);
		}

		tempClass.resetClass();
		tempClass.name = tempName;
		tempClass.hp = tempHP;
		tempClass.armor = tempArmor;
		for (int i = 0; i < tempAbilityNameList.size(); i++)
		{
			tempAbilityName = tempAbilityNameList.at(i);
			tempAbility = GetAbility(tempAbilityName);
			tempClass.abilityList.push_back(tempAbility);
		}

		allClasses.push_back(tempClass);
	}

	classFile.close();
}

EntityAbility GetAbility(string name)
{
	EntityAbility anAbility;
	for (int i = 0; i < allAbilities.size(); i++)
	{
		anAbility = allAbilities.at(i);
		if (name == anAbility.getName())
		{
			return anAbility;
		}
	}
	cout << "Error" << endl;
	return;
}

Enemy GetEnemy(string name)
{
	Enemy anEnemy;
	for (int i = 0; i < allEnemies.size(); i++)
	{
		anEnemy = allEnemies.at(i);
		if (name == anEnemy.getName())
		{
			return anEnemy;
		}
	}
	cout << "Error" << endl;
	return;
}

void GetEnemyData()
{
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
	if (!enemyFile)
	{
		cout << "Error" << endl;
		return;
	}
	while (!enemyFile.eof())
	{
		getline(enemyFile, tmp);
		stringstream element(tmp);
		getline(element, tempString, ',');
		istringstream(tempString) >> tempName;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempHP;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempArmor;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempMovement;
		while (true)
		{
			getline(element, tempString, ',');
			if (tempString == "");
			{
				break;
			}
			istringstream(tempString) >> tempAbilityName;
			tempAbilityNameList.push_back(tempAbilityName);
		}

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

		allEnemies.push_back(tempEnemy);
	}

	enemyFile.close();
}

void GetEnemyPerLevelData()
{
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
	if (!EPLFile)
	{
		cout << "Error" << endl;
		return;
	}
	while (!EPLFile.eof())
	{
		getline(EPLFile, tmp);
		stringstream element(tmp);
		getline(element, tempString, ',');
		istringstream(tempString) >> tempLevel;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempMin;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempMax;

		getline(EPLFile, tmp);
		stringstream element(tmp);
		while (true)
		{
			getline(element, tempString, ',');
			if (tempString == "");
			{
				break;
			}
			istringstream(tempString) >> tempEnemyName;
			tempEnemyNameList.push_back(tempEnemyName);
		}

		tempLevelEnemy.resetEnemy();
		tempLevelEnemy.min = tempMin;
		tempLevelEnemy.max = tempMax;
		for (int i = 0; i < tempEnemyNameList.size(); i++)
		{
			tempEnemyName = tempEnemyNameList.at(i);
			tempEnemy = GetEnemy(tempEnemyName);
			tempLevelEnemy.presetList.push_back(tempEnemy);
		}

		enemyLevelMap[tempLevel] = tempLevelEnemy;
	}

	EPLFile.close();
}

void GetAbilityData()
{
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
	if (!abilityFile)
	{
		cout << "Error" << endl;
		return;
	}
	while (!abilityFile.eof())
	{
		getline(abilityFile, tmp);
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

		allAbilities.push_back(tempAbility);
	}

	abilityFile.close();
}