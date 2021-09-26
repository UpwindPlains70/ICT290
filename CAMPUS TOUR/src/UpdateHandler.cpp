#include "UpdateHandler.h"

int level = 1;
enum state { NotReady, Ready, Initialising, StartTurn, Action, Attack, Win, Lose, AttackAOE};
state gameState = NotReady;
map<int, bool> isPCTurnMap;
map<int, bool> turnDeadMap;
map<int, int> turnIDMap;
vector<Player> playerList;
bool pcHasAction;
vector<Enemy> nowEnemies;
int maxTurn;
int nowAbilityID;
int turn;
LevelMap* nowMap = nullptr;
bool displayEnt;
int currLevel = 1;
int mapID = 0;
LevelEnemy nowLM;
int randNum;
int randX;
int randZ;

using namespace std;

void Update()
{
	switch (gameState) {
		case NotReady:
			/// <Task 1> (Peter)
			/// Get Number of Players
			/// </Task 1>
			
			displayEnt = false;

			nowMap = new LevelMap(mapList[level].at(rand() % mapList[level].size()));
			
			/// <Task 2> (Peter)
			/// Choose the first player's class and push_back the new player
			/// Repeat till all players are done
			/// </Task 2>

			/// <Task 3> (Peter)
			/// If all of above is done then:
			/// gameState = Ready;
			/// </Task 3>
			break;
		case Ready:
			/// <Task 4> (Anyone)
			/// Keep back doors locked until now.
			/// </Task 4>
			
			/// <Task 5> (Anyone)
			/// If teleport area:
			/// gameState = Initialising;
			/// </Task 5>

			break;
		case Initialising:
			//find preset map

			/// <Task 6> (Peter)
			/// draw map
			/// </Task 6>
			
			isPCTurnMap.clear();
			turnIDMap.clear();
			turnDeadMap.clear();
			nowEnemies.clear();

			nowLM = enemyLevelMap[currLevel];
			randNum = rand() % (nowLM.max - nowLM.min) + nowLM.min;
			for (int i = 0; i < randNum; i++)
			{
				nowEnemies.push_back(nowLM.presetList[rand() % nowLM.presetList.size()]);
			}

			/// <Task 8> (Peter)
			/// Display enemy stats(all at once or one at a time due to who is selected)
			/// </Task 8>

			displayEnt = true;

			randNum = rand() % nowMap->GetX();
			nowEnemies[0].setPosX(randNum);
			randNum = rand() % nowMap->GetZ();
			nowEnemies[0].setPosZ(randNum);
			if (nowEnemies.size() > 0) {
				for (int i = 1; i < nowEnemies.size(); i++)
				{
					bool found = false;
					while (!found) {
						randX = rand() % nowMap->GetX();
						randZ = rand() % nowMap->GetZ();

						for (int x = 0; x < nowMap->GetX(); x++)
						{
							for (int z = 0; z < nowMap->GetZ(); z++)
							{
								int xDis = randX - x;
								int zDis = randZ - z;
								if (xDis >= -2 && xDis <= 2)
								{
									if (zDis >= -2 && zDis <= 2)
									{
										if (nowMap->GetValue(randX, randZ) == 0)
										{
											found = true;
										}
									}
								}
							}
						}
					}
					nowEnemies[i].setPosX(randX);
					nowEnemies[i].setPosZ(randZ);
				}
			}

			randNum = rand() % nowMap->GetX();
			playerList[0].setPosX(randNum);
			randNum = rand() % nowMap->GetZ();
			playerList[0].setPosZ(randNum);
			if (playerList.size() > 0) {
				for (int i = 1; i < playerList.size(); i++)
				{
					bool found = false;
					while (!found) {
						randX = rand() % nowMap->GetX();
						randZ = rand() % nowMap->GetZ();
						for (int x = 0; x < nowMap->GetX(); x++)
						{
							for (int z = 0; z < nowMap->GetZ(); z++)
							{
								int xDis = randX - x;
								int zDis = randZ - z;
								if (xDis >= -2 && xDis <= 2)
								{
									if (zDis >= -2 && zDis <= 2)
									{
										if (nowMap->GetValue(randX, randZ) == 0)
										{
											found = true;
										}
									}
								}
							}
						}
					}
					playerList[i].setPosX(randX);
					playerList[i].setPosZ(randZ);
				}
			}
			
			/// <Task 16> (Jason)
			/// start drawing players and enemies in their positions
			/// </Task 16>
			
			maxTurn = playerList.size() + nowEnemies.size();

			/// <Task 10> (Peter)
			/// figure out turn order
			/// (use a vector of integers filled with each number up to number of entities)
			/// (then get random location in vector and get the turn from that)
			///	(then removing that turn as it is used makes life easier)
			///	Place turn in each enemyand characters
			/// </Task 10>
			
			for (int i = 1; i <= maxTurn; i++)
			{
				turnDeadMap.insert(std::pair<int, bool>(i, false));
			}
			gameState = StartTurn;
			turn = 1;
			break;
		case StartTurn:
			playerList[turnIDMap[turn]] = playerList[turnIDMap[turn]];
			if (turnDeadMap[turn] == true)
			{
				endTurn();
				if (isPCTurnMap[turn] == false)
				{
					enemyTurn(nowEnemies[turnIDMap[turn]]);
				}
				else
				{
					playerTurn(playerList[turnIDMap[turn]]);
				}
			}
			break;
		case Action:
			if (playerList[turnIDMap[turn]].canMove())
			{
				/// <Task 17> (Anyone)
				/// if keyboard 'w'
				///		playerList[turnIDMap[turn]].posZ += 1
				///		playerList[turnIDMap[turn]].MovementLeft--
				///	if keyboard 's'
				///		playerList[turnIDMap[turn]].posZ -= 1
				///		playerList[turnIDMap[turn]].MovementLeft--
				///	if keyboard 'a'
				///		playerList[turnIDMap[turn]].posX -= 1
				///		playerList[turnIDMap[turn]].MovementLeft--
				///	if keyboard 'd'
				///		playerList[turnIDMap[turn]].posX += 1
				///		playerList[turnIDMap[turn]].MovementLeft--
				/// </Task 17>
			}
			if (pcHasAction == true)
			{
				/// <Task 18> (Anyone)
				/// if keyboard '1'
				///		nowAbilityID = 0
				///		nowAbility = playerList[turnIDMap[turn]].GetAbility(0)
				///		if cooldownLeft
				///			if Ability.Unique = true
				///				uniqueAbility()
				///			elseif Ability.aoe > 1
				///				State = AttackAOE
				///			else
				///				State = Attack
				///	if keyboard '2'
				///		nowAbilityID = 1
				///		nowAbility = playerList[turnIDMap[turn]].GetAbility(1)
				///		if cooldownLeft
				///			if Ability.Unique = true
				///				uniqueAbility()
				///			elseif Ability.aoe > 1
				///				State = AttackAOE
				///			else
				///				State = Attack
				/// if keyboard '3'
				///		nowAbilityID = 2
				///		nowAbility = playerList[turnIDMap[turn]].GetAbility(2)
				///		if cooldownLeft
				///			if Ability.Unique = true
				///				uniqueAbility()
				///			elseif Ability.aoe > 1
				///				State = AttackAOE
				///			else
				///				State = Attack
				/// </Task 18>
			}
			if (playerList[turnIDMap[turn]].canMove() == false && pcHasAction == false)
			{
				playerList[turnIDMap[turn]] = playerList[turnIDMap[turn]];
				endTurn();
			}
			/// <Task 19> (Anyone)
			/// if keyboard '`'
			///		playerList[turnIDMap[turn]] = playerList[turnIDMap[turn]];
			///		endTurn();
			/// </Task 19>
			break;
		case Attack:
			/// <Task 20> (Anyone)
			/// show enemy select screen
			/// get player to decide on enemy to hit
			/// if decided:
			///		playerList[turnIDMap[turn]].GetAbility(nowAbilityID).used()
			///		if in range:
			///			attack(enemy)
			///			State = Action
			/// </Task 20>

			break;
		case Win:
			if (level == 10)
			{
				/// <Task 21> (Jason)
				/// show final win screen
				/// </Task 21>
			}
			else
			{
				/// <Task 22> (Jason)
				/// show level win screen
				/// </Task 22>
				upgrade();
				level++;
				gameState = Initialising;
			}
			break;
		case Lose:
			/// <Task 22> (Jason)
			/// show lose screen
			/// </Task 22>
			break;
		case AttackAOE:
			/// <Task 26> (Anyone)
			/// show aoe select screen
			/// if decided
			///		playerList[turnIDMap[turn]].GetAbility(nowAbilityID).used()
			///		foreach enemy in aoe
			///			attack(enemy)
			/// </Task 26>				
			break;
	}
}

void endTurn()
{
	/// <Task 11> (Jason)
	/// if so delete them from list
	///	and add their turn to 'turnDeadMap'
	///	remove model off board
	///	make that space empty on map
	/// </Task 11>
	playerList[turnIDMap[turn]] = playerList[turnIDMap[turn]];
	if (nowEnemies.size() == 0)
	{
		gameState = Win;
	}
	if (playerList.size() == 0)
	{
		gameState = Lose;
	}
	gameState = StartTurn;
	turn += 1;
	if (turn > maxTurn)
	{
		turn = 1;
	}
}

void playerTurn(Player pc)
{
	/// <Task 12> (Peter)
	/// display pc stats
	/// </Task 12>
	pc.unshield();
	pc.resetMovementLeft();
	if (pc.getStun() == 1)
	{
		/// <Task 13> (Jason)
		/// show stun being removed
		/// </Task 13>
		pc.setStun(0);
		playerList[turnIDMap[turn]] = pc;
		endTurn();
	}
	else if (pc.getStun() == 0.5)
	{
		/// <Task 13> (Jason)
		/// show stun being removed
		/// </Task 13>
		pc.noMovementLeft();
	}
	EntityAbility ability;
	for (int i = 0; i < pc.getNumberOfAbilities(); i++)
	{
		ability = pc.getAbility(i);
		ability.roundPassed();
		pc.setAbility(ability, i);
	}
	pc.setStun(0);
	pcHasAction = true;
	playerList[turnIDMap[turn]] = pc;
	gameState = Action;
}

void enemyTurn(Enemy ai)
{
	EntityAbility ability;
	
	if (ai.getStun() == 1)
	{
		/// <Task 13> (Jason)
		/// show stun being removed
		/// </Task 13>
	}
	else if (ai.getStun() == 0.5)
	{	
		/// <Task 14> (Raymond)
		/// randomly choose ability from enemy that is an ability in range of closest target
		/// if there is an ability and it has no cooldown left
		/// set as ability
		/// attack
		/// </Task 14>
		
		/// <Task 13> (Jason)
		/// show stun being removed
		/// </Task 13>
	}
	else
	{
		/// <Task 15> (Raymond)
		/// move enemy
		/// </Task 15>

		/// <Task 14> (Raymond)
		/// randomly choose ability from enemy that is an ability in range of closest target
		/// if there is an ability and it has no cooldown left
		/// set as ability
		/// attack
		/// </Task 14>
	}
	ai.setStun(0);
	nowEnemies[turnIDMap[turn]] = ai;
	endTurn();
}

void upgrade()
{
	int bonusHP;
	int roll;
	int abilityID;
	bool upgradeUsed;
	int randMax;
	EntityAbility ability;
	int upgrades;
	for (int i = 0; i < playerList.size(); i++)
	{
		Player player = playerList[i];
		bonusHP = upgradeHP[player.getClassName()];
		bonusHP += playerList[i].getMaxHP();
		playerList[i].setMaxHP(bonusHP);
		upgrades = 2;
		while (upgrades > 0)
		{
			upgradeUsed = false;
			roll = rand() % (playerList[i].getNumAbilities() + 2);
			if (roll == 0)
			{
				playerList[i].setArmor(playerList[i].getArmor() + 1);
				upgradeUsed = true;
			}
			else if (roll == 1)
			{
				playerList[i].setMovement(playerList[i].getMovement() + 1);
				upgradeUsed = true;
			}
			else
			{
				abilityID = roll - 2;
				ability = playerList[i].getAbility(abilityID);
				randMax = 1;

				if (ability.getRange() > 1)
				{
					randMax++;
				}
				if (ability.getAOE() > 1)
				{
					randMax++;
				}
				if (ability.getDuplicate() > 1)
				{
					randMax++;
				}
				if (ability.getCooldown() > 1)
				{
					randMax++;
				}
				if (ability.getDamage() > 0)
				{
					randMax++;
				}

				roll = rand() % (randMax);
				if (ability.getRange() > 1)
				{
					if (roll == 0)
					{
						ability.setRange(ability.getRange() + 1);
						upgradeUsed = true;
					}
					else
					{
						roll--;
					}
				}

				if (ability.getAOE() > 1 && upgradeUsed == false)
				{
					if (roll == 0)
					{
						ability.setAOE(ability.getAOE() + 1);
						upgradeUsed = true;
					}
					else
					{
						roll--;
					}
				}

				if (ability.getDuplicate() > 1 && upgradeUsed == false)
				{
					if (roll == 0)
					{
						ability.setDuplicate(ability.getDuplicate() + 1);
						upgradeUsed = true;
					}
					else
					{
						roll--;
					}
				}

				if (ability.getDamage() > 0 && upgradeUsed == false)
				{
					if (roll == 0)
					{
						ability.setDamage(ability.getDamage() + 1);
						upgradeUsed = true;
					}
					else
					{
						roll--;
					}
				}

				if (upgradeUsed == false)
				{
					if (roll == 0)
					{
						ability.setToHit(ability.getToHit() + 1);
						upgradeUsed = true;
					}
					else
					{
						roll--;
					}
				}

				if (ability.getCooldown() > 1 && upgradeUsed == false)
				{
					if (roll == 0)
					{
						ability.setCooldown(ability.getCooldown() - 1);
						upgradeUsed = true;
					}
					else
					{
						roll--;
					}
				}

				playerList[i].setAbility(ability, abilityID);
			}

			if (upgradeUsed == true)
			{
				upgrades--;
			}
		}
	}
}

void uniqueAbility()
{
	EntityAbility ability = playerList[turnIDMap[turn]].getAbility(nowAbilityID);
	if (ability.getName() == "castle")
	{
		playerList[turnIDMap[turn]].shield(20);
		ability.used();
	}
	else if (ability.getName() == "shield")
	{
		playerList[turnIDMap[turn]].shield(playerList[turnIDMap[turn]].getArmor() + 3);
		ability.used();
	}
	else if (ability.getName() == "wall")
	{
		int numOfSpots = 0;
		int nowX = playerList[turnIDMap[turn]].getPosX();
		int nowZ = playerList[turnIDMap[turn]].getPosZ();
		bool loop = true;
		int roll;
		if (nowMap->GetValue(nowX + 1, nowZ) == 0)
		{
			numOfSpots++;
		}
		if (nowMap->GetValue(nowX - 1, nowZ) == 0)
		{
			numOfSpots++;
		}
		if (nowMap->GetValue(nowX, nowZ + 1) == 0)
		{
			numOfSpots++;
		}
		if (nowMap->GetValue(nowX, nowZ - 1) == 0)
		{
			numOfSpots++;
		}
		if (numOfSpots > 0)
		{
			while (loop)
			{
				roll = rand() % (4);
				if ((nowMap->GetValue(nowX + 1, nowZ) == 0) && (roll == 0))
				{
					playerList[turnIDMap[turn]].setPosX(nowX + 1);
				}
				if ((nowMap->GetValue(nowX - 1, nowZ) == 0) && (roll == 1))
				{
					playerList[turnIDMap[turn]].setPosX(nowX - 1);
				}
				if ((nowMap->GetValue(nowX, nowZ + 1) == 0) && (roll == 2))
				{
					playerList[turnIDMap[turn]].setPosX(nowZ + 1);
				}
				if ((nowMap->GetValue(nowX, nowZ - 1) == 0) && (roll == 3))
				{
					playerList[turnIDMap[turn]].setPosX(nowZ - 1);
				}
			}
			nowMap->SetValue(nowX, nowZ, 1);
			ability.used();
		}
	}
	else if (ability.getName() == "counter")
	{
		playerList[turnIDMap[turn]].shield(20);
		gameState = Attack;
		ability.used();
	}
	else if (ability.getName() == "reload")
	{
		EntityAbility tempAbility;
		for (int i = 0; i < playerList[turnIDMap[turn]].getNumberOfAbilities(); i++)
		{
			tempAbility = playerList[turnIDMap[turn]].getAbility(i);
			tempAbility.resetCooldownCounter();
			playerList[turnIDMap[turn]].setAbility(tempAbility, i);
		}
		ability.used();
	}
	else if (ability.getName() == "heal")
	{
		int nowDisX;
		int nowDisZ;
		int nowX = playerList[turnIDMap[turn]].getPosX();
		int nowZ = playerList[turnIDMap[turn]].getPosZ();
		for (int i = 0; i < playerList.size(); i++)
		{
			nowDisX = playerList[i].getPosX() - nowX;
			if (nowDisX < 0)
			{
				nowDisX *= -1;
			}
			nowDisZ = playerList[i].getPosZ() - nowZ;
			if (nowDisZ < 0)
			{
				nowDisZ *= -1;
			}
			if ((nowDisX + nowDisZ <= ability.getAOE()))
			{
				playerList[i].healPlayer(1);
			}
		}
		ability.used();
	}
	else if (ability.getName() == "revive")
	{
		int min = playerList[0].getHP();
		int minID = 0;
		for (int i = 1; i < playerList.size(); i++)
		{
			if (playerList[i].getHP() < min)
			{
				min = playerList[i].getHP();
				minID = i;
			}
		}
		playerList[minID].resetHP();
	}
	else if (ability.getName() == "damageBoost")
	{
		int roll;
		bool used = false;
		while (!used)
		{
			int roll = rand() % playerList.size();
			if (!playerList[roll].damageBoosted())
			{
				used = true;
				playerList[roll].setDamageBoost(true);
			}
		}
		ability.used();
	}
	playerList[turnIDMap[turn]].setAbility(ability, nowAbilityID);
}

void attack(int id)
{
	pcHasAction = false;
	EntityAbility ability = playerList[turnIDMap[turn]].getAbility(nowAbilityID);
	int toHit;
	int dam;
	toHit = ability.getToHit() + 2;
	int smallX, smallZ, tempX, tempZ, bigX, bigZ;
	smallX = nowEnemies[id].getPosX();
	smallZ = nowEnemies[id].getPosZ();
	bigX = playerList[turnIDMap[turn]].getPosX();
	bigZ = playerList[turnIDMap[turn]].getPosZ();

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

	if (nowEnemies[id].getStun() > 0)
	{
		toHit += 5;
	}

	for (int i = 0; i < ability.getDuplicate(); i++)
	{
		int roll = rollTheDice(toHit, nowEnemies[id].getArmor());
		int dam = roll * ability.getDamage();
		if (playerList[turnIDMap[turn]].damageBoosted())
		{
			dam *= 2;
		}
		nowEnemies[id].damageEnemy(dam);
		if ((roll > 0) && (nowEnemies[id].getStun() < ability.getStun()))
		{
			nowEnemies[id].setStun(ability.getStun());
		}
	}
}

int rollTheDice(int bonus, int AC)
{
	// 0 = no damage, 1 = damage, 2 = critical
	int roll = rand() % (19) + 1;
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