#include "Enemy.h"

#include <string>
#include <iostream>
using namespace std;

Enemy::Enemy() {
	reset();
}

Enemy::Enemy(string newName, int newMaxHP, int newArmor, int newStun, int newPosX, int newPosZ, int newMovement, int newTurn) {

	name = newName;
	maxHP = newMaxHP;
	armor = newArmor;
	originalAC = armor;
	hp = maxHP;
	stun = newStun;
	posX = newPosX;
	posZ = newPosZ;
	movement = newMovement;
	turn = newTurn;
	numAbilities = 0;
	//rotation = 0.0;
}

Enemy::~Enemy() {

}

void Enemy::setName(string newName) {
	name = newName;
}

string Enemy::getName() {
	return name;
}

void Enemy::setMaxHP(int newMaxHP) {
	maxHP = newMaxHP;
}

int Enemy::getMaxHP() {
	return maxHP;
}

void Enemy::setArmor(int newArmor) {
	armor = newArmor;
	originalAC = armor;
}

int Enemy::getArmor() {
	return armor;
}

int Enemy::getNumAbilities() {
	return numAbilities;
}

void Enemy::resetHP() {
	hp = maxHP;
}

int Enemy::getHP() {
	return hp;
}

void Enemy::damageEnemy(int dam) {
	hp -= dam;
	if (hp < 0)
	{
		hp = 0;
	}
}

void Enemy::healEnemy(int heal) {
	hp += heal;
	if (hp > maxHP)
	{
		hp = maxHP;
	}
}

void Enemy::setStun(int newStun) {
	stun = newStun;
}

int Enemy::getStun() {
	return stun;
}

void Enemy::setPosX(int newPosX) {
	posX = newPosX;
}

int Enemy::getPosX() {
	return posX;
}

void Enemy::setPosZ(int newPosZ) {
	posZ = newPosZ;
}

int Enemy::getPosZ() {
	return posZ;
}

void Enemy::setMovement(int newMovement) {
	movement = newMovement;
}

int Enemy::getMovement() {
	return movement;
}

void Enemy::setTurn(int newTurn) {
	turn = newTurn;
}

int Enemy::getTurn() {
	return turn;
}

void Enemy::pushAbility(EntityAbility newAbility) {
	abilities.push_back(newAbility);
	numAbilities++;
}

void Enemy::popAbility() {
	abilities.pop_back();
	numAbilities--;
}

void Enemy::setAbility(EntityAbility newAbility, int num) {
	abilities.at(num) = newAbility;
}

EntityAbility Enemy::getAbility(int num) {
	return abilities[num];
}

void Enemy::shield(int AC)
{
	originalAC = armor;
	armor = AC;
}

void Enemy::unshield()
{
	armor = originalAC;
}

void Enemy::reset()
{
	abilities.clear();
	name = "";
	numAbilities = 0;
	hp = 0;
	stun = 0;
	posX = 0;
	posZ = 0;
	movement = 0;
	turn = 0;
	armor = 0;
	maxHP = 0;
	originalAC = armor;
	//rotation = 0.0;
}

// 0 = empty, 1 = wall, 2 = ally, 3 = enemy.
//call to move piece //might change due to map orientation
void Enemy::moveUp(LevelMap* nowMap) {
	if (nowMap->GetValue(posX + 1, posZ) == 0) {
		//update map positions
		nowMap->SetValue(posX + 1, posZ, 3);
		nowMap->SetValue(posX, posZ, 0);
		//move
		posX++;
	}
	else {
		//check directions clockwise
		if (nowMap->GetValue(posX, posZ + 1) == 0) {
			moveRight(nowMap);
		}
		else {
			if (nowMap->GetValue(posX - 1, posZ) == 0) {
				moveDown(nowMap);
			}
			else {
				if (nowMap->GetValue(posX, posZ - 1) == 0) {
					moveLeft(nowMap);
				}
				else {
					// no move; End turn
				}
			}
		}
	}
}

void Enemy::moveDown(LevelMap* nowMap) {
	if (nowMap->GetValue(posX - 1, posZ) == 0) {
		//update map positions
		nowMap->SetValue(posX - 1, posZ, 3);
		nowMap->SetValue(posX, posZ, 0);
		//move
		posX--;
	}
	else {
		//check directions clockwise
		if (nowMap->GetValue(posX, posZ - 1) == 0) {
			moveLeft(nowMap);
		}
		else {
			if (nowMap->GetValue(posX + 1, posZ) == 0) {
				moveUp(nowMap);
			}
			else {
				if (nowMap->GetValue(posX, posZ + 1) == 0) {
					moveRight(nowMap);
				}
				else {
					// no move; End turn
				}
			}
		}
	}
}

void Enemy::moveLeft(LevelMap* nowMap) {
	if (nowMap->GetValue(posX, posZ - 1) == 0) {
		//update map positions
		nowMap->SetValue(posX, posZ - 1, 3);
		nowMap->SetValue(posX, posZ, 0);
		//move
		posZ = posZ--;
	}
	else {
		//check directions clockwise
			//Bounds checks
		if (nowMap->GetValue(posX + 1 < nowMap->GetX() ? posX + 1 : posX, posZ) == 0) {
			moveUp(nowMap);
		}
		else {
			if (nowMap->GetValue(posX, posZ + 1 < nowMap->GetZ() ? posZ + 1 : posZ) == 0) {
				moveRight(nowMap);
			}
			else {
				if (nowMap->GetValue(posX - 1 >= 0 ? posX - 1 : posX, posZ) == 0) {
					moveDown(nowMap);
				}
				else {
					// no move; End turn
				}
			}
		}
	}
}

void Enemy::moveRight(LevelMap* nowMap) {
	if (nowMap->GetValue(posX, posZ + 1) == 0) {
		//update map positions
		nowMap->SetValue(posX, posZ + 1, 3);
		nowMap->SetValue(posX, posZ, 0);
		//move
		posZ = posZ++;
	}
	else {
		//check directions clockwise
		if (nowMap->GetValue(posX - 1, posZ) == 0) {
			moveDown(nowMap);
		}
		else {
			if (nowMap->GetValue(posX, posZ - 1) == 0) {
				moveLeft(nowMap);
			}
			else {
				if (nowMap->GetValue(posX, posZ + 1) == 0) {
					moveRight(nowMap);
				}
				else {
					// no move; End turn
				}
			}
		}
	}
}

bool Enemy::checkRange(vector<Player> playerList) {
	int lowestRange = -1;
	int pX;
	int pZ;
	int disX;
	int disZ;
	for (int i = 0; i < playerList.size(); i++)
	{
		pX = playerList[i].getPosX();
		pZ = playerList[i].getPosZ();
		disX = pX - posX;
		disZ = pZ - posZ;
		if (disX < 0)
		{
			disX *= -1;
		}

		if (disZ < 0)
		{
			disZ *= -1;
		}
		if (lowestRange == -1)
		{
			lowestRange = disX + disZ;
		}
		else if (lowestRange > (disX + disZ))
		{
			lowestRange = disX + disZ;
		}
	}
	int maxRange = -1;
	int tempRange;
	for (int i = 0; i < abilities.size(); i++)
	{
		tempRange = abilities[i].getRange();
		if (maxRange == -1)
		{
			maxRange = tempRange;
		}
		else if (maxRange < tempRange)
		{
			maxRange = tempRange;
		}
	}

	if (maxRange >= lowestRange)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int*Enemy::getTargetPos(vector<Player> playerList) {
	int tarPosA[2];
	int tarPosB[2];
	//testing
	
	tarPosA[0] = playerList[0].getPosX() - posX;
	tarPosA[1] = playerList[0].getPosZ() - posZ;

	//for each enemy char *presumably a list *ONE ENEMY FOR TESTING, WILL CHANGE TO FIT MAIN PRODUCT
	for (int i = 0; i < playerList.size(); i++) {
		//check and store distance
		tarPosB[0] = playerList[i].getPosX() - posX;
		tarPosB[1] = playerList[i].getPosZ() - posZ;
		//if distanceOfLastTarget < distanceOfCurrentTarget
		if (tarPosA[0] < tarPosB[0] && tarPosA[1] < tarPosB[1]) {
			//distanceOfLastTarget = distanceOfCurrentTarget
			tarPosA[0] = tarPosB[0];
			tarPosA[1] = tarPosB[1];
		}
	}

	//return distanceOfLastTarget
	return tarPosA;
}

////LARGEST WORK IN PROGRESS
int Enemy::moveToTarget(int tempMove, LevelMap* nowMap, vector<Player> playerList) {
	bool inRange = false;
	bool inRangeTemp = false;

	int* distanceToTarget = getTargetPos(playerList);

	//disToTar = distanceToTarget;
	int disToTar[2];
	for (int i = 0; i < 2; i++) {
		disToTar[i] = distanceToTarget[i];
	}

	////move x first (UPDATE: place in animate function to stop teleport & include rotation)
	while (tempMove > 0 && inRange == false) {
		//move x 1 times
		printf("%d , %d\n", disToTar[0], disToTar[1]);
		//if (disToTar[0] >= disToTar[1]) {
			if (disToTar[0] > 0) {
				moveUp(nowMap);
				//printf("Up: %d\n", tempMove);
			}
			else if (disToTar[0] < 0) {
				moveDown(nowMap);
				//printf("Down\n");
			}
		//}
		//else if (disToTar[1] >= disToTar[0]) {
			if (disToTar[1] > 0) {
				moveRight(nowMap);
				//printf("Right\n");
			}
			else if (disToTar[1] < 0) {
				moveLeft(nowMap);
				//printf("Left\n");
			}
		//}

		//disToTar = getTargetPos
		distanceToTarget = getTargetPos(playerList);
		for (int i = 0; i < 2; i++) {
			disToTar[i] = distanceToTarget[i];
		}

		tempMove--;
		for (int i = 0; i < abilities.size(); i++) {
			//checkRange
			inRangeTemp = checkRange(playerList);
			if (inRangeTemp) {
				inRange = true;
			}
		}

	}
	//endWhile

	return tempMove;
}


/// <Task 15> (Raymond)
/// move enemy
/// </Task 15>
void Enemy::AITurn(LevelMap* nowMap, vector<Player> playerList) {
	bool inRange = false;
	bool inRangeTemp = false;

	//get move to a tempMove
	int tempMove = movement;
	while (!inRange && tempMove > 0) {
		//1 Check for enemies in range
		//for each ability
		for (int i = 0; i < abilities.size(); i++) {
			//checkRange
			cout << "ability: " << abilities[i].getName() << endl;
			inRangeTemp = checkRange(playerList);
			if (inRangeTemp) {
				inRange = true;
			}
		}

		if (!inRange) {
			//2 Find enemy's distance on grid
			//3 Use acquire distance to move
			tempMove = moveToTarget(tempMove, nowMap, playerList);
		}
		cout << inRange << "::" << tempMove << endl;
	}

}


/// <Task 14> (Raymond)
/// randomly choose ability from enemy that is an ability in range of closest target
/// if there is an ability and it has no cooldown left
/// set as ability
/// attack
/// </Task 14>
void Enemy::AIAttack(LevelMap* nowMap, vector<Player>& playerList, int& summon) {
	summon = 0;
	vector<EntityAbility> availableAbilities;
	EntityAbility nowAbility;
	int lowestRange = -1;
	int pX;
	int pZ;
	int disX;
	int disZ;
	int playerAttackedID;
	for (int i = 0; i < playerList.size(); i++)
	{
		pX = playerList[i].getPosX();
		pZ = playerList[i].getPosZ();
		disX = pX - posX;
		disZ = pZ - posZ;
		if (disX < 0)
		{
			disX *= -1;
		}

		if (disZ < 0)
		{
			disZ *= -1;
		}
		if (lowestRange == -1)
		{
			lowestRange = disX + disZ;
			playerAttackedID = i;
		}
		else if (lowestRange > (disX + disZ))
		{
			lowestRange = disX + disZ;
			playerAttackedID = i;
		}
	}
	for (int i = 0; i < abilities.size(); i++)
	{
		if (abilities[i].getRange() <= lowestRange && abilities[i].getUnique() == false)
		{
			availableAbilities.push_back(abilities[i]);
		}
		if (abilities[i].getName() == "summonLevel1" || 
			abilities[i].getName() == "barrierBoss" || 
			abilities[i].getName() == "coneBoss" || 
			abilities[i].getName() == "cone")
		{
			availableAbilities.push_back(abilities[i]);
		}
		if (lowestRange == 1 && abilities[i].getName() == "knockbackBoss")
		{
			availableAbilities.push_back(abilities[i]);
		}
		if (abilities[i].getName() == "grow" && hp < maxHP)
		{
			availableAbilities.push_back(abilities[i]);
		}

		nowAbility = availableAbilities[rand() % availableAbilities.size()];

		if (nowAbility.getUnique() == false)
		{
			attack(nowAbility, playerList[playerAttackedID], nowMap);
		}
		if (nowAbility.getName() == "summonLevel1")
		{
			summon = 1;
		}
		if (nowAbility.getName() == "barrierBoss")
		{
			shield(armor + 5);
		}
		if (nowAbility.getName() == "coneBoss" || nowAbility.getName() == "cone")
		{
			if (playerList[playerAttackedID].getPosX() == posX)
			{
				if (playerList[playerAttackedID].getPosZ() > posZ)
				{
					for (int i = 0; i < playerList.size(); i++)
					{
						if (playerList[i].getPosX() == posX && playerList[i].getPosZ() > posZ)
						{
							attack(nowAbility, playerList[i], nowMap);
						}
					}
				}
				else
				{
					for (int i = 0; i < playerList.size(); i++)
					{
						if (playerList[i].getPosX() == posX && playerList[i].getPosZ() < posZ)
						{
							attack(nowAbility, playerList[i], nowMap);
						}
					}
				}
			}
			else
			{
				if (playerList[playerAttackedID].getPosX() > posX)
				{
					for (int i = 0; i < playerList.size(); i++)
					{
						if (playerList[i].getPosZ() == posZ && playerList[i].getPosX() > posX)
						{
							attack(nowAbility, playerList[i], nowMap);
						}
					}
				}
				else
				{
					for (int i = 0; i < playerList.size(); i++)
					{
						if (playerList[i].getPosZ() == posZ && playerList[i].getPosX() < posX)
						{
							attack(nowAbility, playerList[i], nowMap);
						}
					}
				}
			}
		}
		if (nowAbility.getName() == "knockbackBoss")
		{
			kbAttack(nowAbility, playerList[playerAttackedID], nowMap);
		}
		if (nowAbility.getName() == "grow")
		{
			healEnemy(2);
		}
	}
}

void Enemy::kbAttack(EntityAbility ability, Player& player, LevelMap* nowMap)
{
	int toHit;
	int dam;
	toHit = ability.getToHit() + 2;
	int smallX, smallZ, tempX, tempZ, bigX, bigZ;
	smallX = posX;
	smallZ = posZ;
	bigX = player.getPosX();
	bigZ = player.getPosZ();

	if (smallX > bigX)
	{
		tempX = smallX;
		bigX = smallX;
		smallX = tempX;
	}

	if (smallZ > bigZ)
	{
		tempZ = smallZ;
		bigZ = smallZ;
		smallZ = tempZ;
	}

	for (int x = smallX; x <= bigX; x++)
	{
		for (int z = smallZ; z <= bigZ; z++)
		{
			if (nowMap->GetValue(x, z) > 0)
			{
				toHit--;
			}
		}
	}

	if (player.getStun() > 0)
	{
		toHit += 5;
	}
	int oldPosX;
	int oldPosZ;
	int roll = rollTheDice(toHit, player.getArmor());
	dam = roll * ability.getDamage();
	player.damagePlayer(dam);
	if ((roll > 0) && (player.getStun() < ability.getStun()))
	{
		player.setStun(ability.getStun());
	}
	if (roll > 0)
	{
		if (player.getPosX() == posX)
		{
			if (player.getPosZ() > posZ)
			{
				bool found = false;
				for (int i = nowMap->GetZ(); i > player.getPosZ(); i--)
				{
					if (nowMap->GetValue(posX, i) == 0)
					{
						oldPosX = player.getPosX();
						oldPosZ = player.getPosZ();
						player.setPosX(posX);
						player.setPosZ(i);
						nowMap->SetValue(oldPosX, oldPosZ, 0);
						nowMap->SetValue(posX, i, 2);
						found = true;
						break;
					}
				}
				if (!found)
				{
					player.setStun(1);
					player.damagePlayer(dam);
				}
			}
			else
			{
				bool found = false;
				for (int i = nowMap->GetZ(); i < player.getPosZ(); i++)
				{
					if (nowMap->GetValue(posX, i) == 0)
					{
						oldPosX = player.getPosX();
						oldPosZ = player.getPosZ();
						player.setPosX(posX);
						player.setPosZ(i);
						nowMap->SetValue(oldPosX, oldPosZ, 0);
						nowMap->SetValue(posX, i, 2);
						found = true;
						break;
					}
				}
				if (!found)
				{
					player.setStun(1);
					player.damagePlayer(dam);
				}
			}
		}
		else
		{
			if (player.getPosX() > posX)
			{
				bool found = false;
				for (int i = nowMap->GetX(); i > player.getPosX(); i--)
				{
					if (nowMap->GetValue(posZ, i) == 0)
					{
						oldPosX = player.getPosX();
						oldPosZ = player.getPosZ();
						player.setPosZ(posZ);
						player.setPosX(i);
						nowMap->SetValue(oldPosX, oldPosZ, 0);
						nowMap->SetValue(i, posZ, 2);
						found = true;
						break;
					}
				}
				if (!found)
				{
					player.setStun(1);
					player.damagePlayer(dam);
				}
			}
			else
			{
				bool found = false;
				for (int i = nowMap->GetX(); i < player.getPosX(); i++)
				{
					if (nowMap->GetValue(posZ, i) == 0)
					{
						oldPosX = player.getPosX();
						oldPosZ = player.getPosZ();
						player.setPosZ(posZ);
						player.setPosX(i);
						nowMap->SetValue(oldPosX, oldPosZ, 0);
						nowMap->SetValue(i, posZ, 2);
						found = true;
						break;
					}
				}
				if (!found)
				{
					player.setStun(1);
					player.damagePlayer(dam);
				}
			}
		}
	}
}

void Enemy::attack(EntityAbility ability, Player& player, LevelMap* nowMap)
{
	int toHit;
	int dam;
	toHit = ability.getToHit() + 2;
	int smallX, smallZ, tempX, tempZ, bigX, bigZ;
	smallX = posX;
	smallZ = posZ;
	bigX = player.getPosX();
	bigZ = player.getPosZ();

	if (smallX > bigX)
	{
		tempX = smallX;
		bigX = smallX;
		smallX = tempX;
	}

	if (smallZ > bigZ)
	{
		tempZ = smallZ;
		bigZ = smallZ;
		smallZ = tempZ;
	}

	for (int x = smallX; x <= bigX; x++)
	{
		for (int z = smallZ; z <= bigZ; z++)
		{
			if (nowMap->GetValue(x, z) > 0)
			{
				toHit--;
			}
		}
	}

	if (player.getStun() > 0)
	{
		toHit += 5;
	}

	for (int i = 0; i < ability.getDuplicate(); i++)
	{
		int roll = rollTheDice(toHit, player.getArmor());
		int dam = roll * ability.getDamage();
		player.damagePlayer(dam);
		if ((roll > 0) && (player.getStun() < ability.getStun()))
		{
			player.setStun(ability.getStun());
		}
	}
}

int Enemy::rollTheDice(int bonus, int AC)
{
	// 0 = no damage, 1 = damage, 2 = critical
	int roll = random_int(1, 20);
	if (roll == 1)
	{
		return 0;
	}
	else if (roll == 20)
	{
		return 2;
	}
	else
	{
		roll += bonus;
		if (roll >= AC)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int Enemy::random_int(int min, int max)
{
	return min + rand() % (max + 1 - min);
}

/*float Enemy::getRotation()
{
	return rotation;
}

void Enemy::setRotation(float newRot)
{
	rotation = newRot;
}

void Enemy::rotateEnemy(int X, int Z)
{
	if (X == 0 && Z == 1)	//forward rot
		rotation = 0;
	else if (X == -1 && Z == 0)	//Right rot
		rotation = 270.0;
	else if (X == 0 && Z == -1)  //backward rot
		rotation = 180.0;
	else	//Left rot
		rotation = 90.0;
}*/