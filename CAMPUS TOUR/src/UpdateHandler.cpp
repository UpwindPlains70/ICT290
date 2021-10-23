#include "UpdateHandler.h"


state gameState = NotGame;
map<int, bool> isPCTurnMap;
map<int, bool> turnDeadMap;
map<int, int> turnIDMap;
vector<Player> playerList;
bool pcHasAction;
vector<Enemy> nowEnemies;
int maxTurn;
int nowAbilityID;
int turn;
int sessionRound = 1;
LevelMap* nowMap = nullptr;

int AOEArrowPosX;
int AOEArrowPosZ;
int originalArrowPosX;
int originalArrowPosZ;

vector<int> turnList;

bool firstRun = true;
bool displayActionMenu = false;
bool allowedToRoll = true;

bool displayEnt;
LevelEnemy nowLM;
int randNum;
int randX;
int randZ;
bool canIJKL;
bool canAction;
bool canEndTurn;

using namespace std;

void DisplayLinup() 
{
	DisplayPlayerModel("Samurai", 123, 9000, -21, 0); // just for testing, can remove all these characters calls at any time
	DisplayPlayerModel("Zombie", 200, 9000, -21, 0);
	DisplayPlayerModel("Wizard", 280, 9000, -21, 0);
	DisplayPlayerModel("Skeleton", 360, 9000, -21, 0);
	DisplayPlayerModel("FireGolum", 440, 9000, -21, 0);
	DisplayPlayerModel("EarthGolum", 60, 9000, -21, 0);
	DisplayPlayerModel("WaterGolum", -20, 9000, -21, 0);
	DisplayPlayerModel("Berserker", -100, 9000, -21, 0);
	DisplayPlayerModel("Shield", -190, 9000, -21, 0);
	DisplayPlayerModel("Monk", -270, 9000, -21, 0);
	DisplayPlayerModel("Swashbuckler", -350, 9000, -21, 0);
	DisplayPlayerModel("Archer", -430, 9000, -21, 0);
	DisplayPlayerModel("Artillery", -430, 9000, -150, 0);
	DisplayPlayerModel("Bard", -350, 9000, -150, 0);
	DisplayPlayerModel("Cleric", -270, 9000, -150, 0);
	DisplayPlayerModel("Druid", -190, 9000, -150, 0);
	DisplayPlayerModel("Tree", -110, 9000, -150, 0);
	DisplayPlayerModel("LavaBoss", -30, 9000, -150, 0);
	DisplayPlayerModel("EarthBoss", -30, 9000, -230, 0);
	DisplayPlayerModel("WaterBoss", 50, 9000, -230, 0);
	DisplayPlayerModel("AirBoss", 130, 9000, -230, 0);
	DisplayPlayerModel("AnimatedArmor", 180, 9000, -230, 0);
	DisplayPlayerModel("AirGolum", 260, 9000, -230, 0);
	DisplayPlayerModel("FireMage", 340, 9000, -230, 0);
	DisplayPlayerModel("TelekineticMage", 440, 9000, -230, 0);
	DisplayPlayerModel("AirMage", 440, 9000, -360, 0);
	DisplayPlayerModel("WaterMage", 360, 9000, -360, 0);
	DisplayPlayerModel("EarthMage", 280, 9000, -360, 0);
	DisplayPlayerModel("WaterElemental", 200, 9000, -360, 0);
	DisplayPlayerModel("EarthElemental", 120, 9000, -360, 0);
	DisplayPlayerModel("FireElemental", 40, 9000, -360, 0);
	DisplayPlayerModel("AirElemental", -40, 9000, -360, 0);
	DisplayPlayerModel("Shadow", -120, 9000, -360, 0);
}

void Update()
{
	//DisplayLinup();
	switch (gameState) {
		case NotGame:
			break;
		case NotReady:
				//stuck until finished button is pressed
			classSelectionUI();
			ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

			canIJKL = false;
			canAction = false;
			canEndTurn = false;
			
			displayEnt = false;

			break;
		case Ready:
			/// <Task 4> (Anyone)
			/// Keep back doors locked until now.
			/// </Task 4>
			//cout << "Ready" << endl;
			if (currLevel != 0) {
				//cout << "Change" << endl;
				gameState = Initialising;
			}
			break;
		case Initialising:
			
			if (firstRun) {
				assignTurnStage = true;
				firstRun = false;
					//Load copy of current level
				srand(time(NULL));
				mapID = rand() % mapList[currLevel].size();
				nowMap = new LevelMap(mapList[currLevel].at(mapID));

					//Clear list (turns, enemies)
				isPCTurnMap.clear();
				turnIDMap.clear();
				turnDeadMap.clear();
				nowEnemies.clear();

				addToLog("Level: " + to_string(currLevel));
				addToLog("Map Chosen: " + to_string(mapID));

				//Assign Enemies for current level
				nowLM = enemyLevelMap[currLevel];
				randNum = random_int(nowLM.min, nowLM.max);
				for (int i = 0; i < randNum; i++)
				{
					nowEnemies.push_back(nowLM.presetList[rand() % nowLM.presetList.size()]);
					addToLog("Enemy Added: " + nowEnemies[i].getName());
				}

				maxTurn = playerList.size() + nowEnemies.size();

				for (int i = 1; i <= maxTurn; ++i)
					turnList.push_back(i);

				displayEnt = true;

				//Position enemies
				do {
					randX = rand() % nowMap->GetX();
					randZ = rand() % nowMap->GetZ();
				} while (nowMap->GetValue(randX, randZ) != 0);
				nowEnemies[0].setPosX(randX);
				nowEnemies[0].setPosZ(randZ);
				nowMap->SetValue(randX, randZ, 3);
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
						addToLog(nowEnemies[i].getName() + " is placed at (" + to_string(randX) + ", " + to_string(randZ) + ")");
						nowEnemies[i].setPosX(randX);
						nowEnemies[i].setPosZ(randZ);
						nowMap->SetValue(randX, randZ, 3);
					}
				}

				//Position players
				do {
					randX = rand() % nowMap->GetX();
					randZ = rand() % nowMap->GetZ();
				} while (nowMap->GetValue(randX, randZ) != 0);
				playerList[0].setPosX(randX);
				playerList[0].setPosZ(randZ);
				nowMap->SetValue(randX, randZ, 2);
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
						addToLog(playerList[i].getName() + " is placed at (" + to_string(randX) + ", " + to_string(randZ) + ")");
						for (int c = 0; c < playerList[i].getNumAbilities(); c++)
						{
							EntityAbility ability = playerList[i].getAbility(c);
							ability.zeroCooldownCounter();
							playerList[i].setAbility(ability, c);
						}
						nowMap->SetValue(randX, randZ, 2);
					}
				}
				
				displayCharacters = true; 
			}
			
			if(!assignTurnStage) 
			{
				for (int i = 1; i <= maxTurn; i++)
				{
					turnDeadMap.insert(std::pair<int, bool>(i, false));
				}
				gameState = StartTurn;
				firstRun = true;
				turn = 1;
			}
				break;
		case StartTurn:
				//Display player & enemy stats
			//playerHUD();
			//ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

			//set player turn

			//pc turn doesnt turn 0
			//cout << "PC turn: " << isPCTurnMap[turn] << endl;

			if (turnDeadMap[turn] == false)
			{
				if (isPCTurnMap[turn] == false)
				{
					enemyTurn();
				}
				else
				{
					playerTurn();
				}
			}
			else
			{
				endTurn();
			}
			
			break;
		case Action:
				//Display player & enemy stats
			//playerHUD();
			//ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
			if (playerList[turnIDMap[turn]].canMove())
			{
				canIJKL = true;
			}
			else
			{
				canIJKL = false;
			}
			if (pcHasAction == true)
			{
				canAction = true;
			}
			else
			{
				canAction = false;
			}
			if (playerList[turnIDMap[turn]].canMove() == false && pcHasAction == false)
			{
				endTurn();
			}
			canEndTurn = true;
			break;
		case Attack:
				//Display player & enemy stats
			//playerHUD();
			//ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

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
			if (currLevel == 10)
			{
				
				/// show final win screen
				popUpMessageState = TotalWin;
				
			}
			else
			{
				/// show currLevel win screen
				popUpMessageState = LevelWin; 				
			}
			break;
		case Lose:
				//Display lose screen
			popUpMessageState = Lost; 
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
	if (gameState >= Initialising)
		positionFloorObjects(nowEnemies, playerList);

	//Draw UI frame after floor to appear over not behind
	if (gameState == Initialising && assignTurnStage)
	{
		turnOrderUI();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}

	if (gameState > 3 && turnDeadMap[turn] != true && isPCTurnMap[turn] == true && DisplayExit == false && popUpMessageState == None) {
		playerHUD();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}

	updatePopUpMessage();
}

void endTurn()
{
	popUpMessage = true;
	if (nowEnemies.size() == 0)
	{
		gameState = Win;
	}
	else if (playerList.size() == 0)
	{
		gameState = Lose;
	}else
		gameState = StartTurn;

	displayActionMenu = false;
	++turn;
	if (turn > maxTurn)
	{
		turn = 1;
		++sessionRound;
	}
	allowedToRoll = true;
}

void playerTurn()
{
		// display pc actions
	displayActionMenu = true;
	playerList[turnIDMap[turn]].unshield();
	playerList[turnIDMap[turn]].resetMovementLeft();
	if (playerList[turnIDMap[turn]].getStun() == 1)
	{
		/// <Task 13> (Jason)
		/// show stun being removed
		/// </Task 13>
		playerList[turnIDMap[turn]].setStun(0);
		endTurn();
	}
	else if (playerList[turnIDMap[turn]].getStun() == 0.5)
	{
		/// <Task 13> (Jason)
		/// show stun being removed
		/// </Task 13>
		playerList[turnIDMap[turn]].noMovementLeft();
	}
	//if (nowEnemies.empty())
	//	endTurn();

	EntityAbility ability;
	for (int i = 0; i < playerList[turnIDMap[turn]].getNumberOfAbilities(); i++)
	{
		ability = playerList[turnIDMap[turn]].getAbility(i);
		ability.roundPassed();
		playerList[turnIDMap[turn]].setAbility(ability, i);
	}
	playerList[turnIDMap[turn]].setStun(0);
	pcHasAction = true;
	gameState = Action;
}

void enemyTurn()
{
	nowEnemies[turnIDMap[turn]].unshield();

	EntityAbility ability;
	
	cout << "ENEMY TURN HAPPENED: " << nowEnemies[turnIDMap[turn]].getName() << endl;

	if (nowEnemies[turnIDMap[turn]].getStun() == 1)
	{
		/// <Task 13> (Jason)
		/// show stun being removed
		/// </Task 13>
	}
	else if (nowEnemies[turnIDMap[turn]].getStun() == 0.5)
	{	
		/// <Task 14> (Raymond)
		/// randomly choose ability from enemy that is an ability in range of closest target
		/// if there is an ability and it has no cooldown left
		/// set as ability
		/// attack
		/// </Task 14>
		
		addToLog(nowEnemies[turnIDMap[turn]].getName() + " Moved");

		int summon;
		nowEnemies[turnIDMap[turn]].AIAttack(nowMap, playerList, summon);
		if (summon > 0)
		{
			turnIDMap.insert(std::pair<int, int>(maxTurn, nowEnemies.size()));
			isPCTurnMap.insert(std::pair<int, bool>(maxTurn, false));
			turnDeadMap.insert(std::pair<int, bool>(maxTurn, false));
			turnList.push_back(nowEnemies.size());
			maxTurn++;
			nowEnemies.push_back(enemyLevelMap[summon].presetList[rand() % enemyLevelMap[summon].presetList.size()]);
		}
		
		/// <Task 13> (Jason)
		/// show stun being removed
		/// </Task 13>
	}
	else
	{
		// move enemy
		addToLog(nowEnemies[turnIDMap[turn]].getName() + " Moved and Attacked");
		nowEnemies[turnIDMap[turn]].AITurn(nowMap, playerList);

		/// randomly choose ability from enemy that is an ability in range of closest target

		int summon;
		nowEnemies[turnIDMap[turn]].AIAttack(nowMap, playerList, summon);
		if (summon > 0)
		{
			turnIDMap.insert(std::pair<int, int>(maxTurn, nowEnemies.size()));
			isPCTurnMap.insert(std::pair<int, bool>(maxTurn, false));
			turnDeadMap.insert(std::pair<int, bool>(maxTurn, false));
			turnList.push_back(nowEnemies.size());
			maxTurn++;
			nowEnemies.push_back(enemyLevelMap[summon].presetList[rand() % enemyLevelMap[summon].presetList.size()]);
		}
	}
	
	nowEnemies[turnIDMap[turn]].setStun(0);

		//Check each player
	for (int i = 0; i < playerList.size(); i++)
	{
		if (playerList[i].getHP() <= 0) 
		{
				//Mark turn as dead, remove from turnID mapand now enemy list
			turnDeadMap[playerList[i].getTurn()] = true;
			turnIDMap.erase(playerList[i].getTurn());

			for (int i = 0; i < playerList.size(); ++i)
				if (turnIDMap[playerList[i].getTurn()] != 0)
					turnIDMap[playerList[i].getTurn()] -= 1;
			
			playerList.erase(playerList.begin() + i);
		}
	}

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
	srand(time(NULL));
	for (int i = 0; i < playerList.size(); i++)
	{
		Player player = playerList[i];
		bonusHP = upgradeHP[player.getClassName()];
		bonusHP += playerList[i].getMaxHP();
		playerList[i].setMaxHP(bonusHP);
		playerList[i].resetHP();
		for (int c = 0; c < player.getNumAbilities(); c++)
		{
			ability = player.getAbility(c);
			ability.zeroCooldownCounter();
			player.setAbility(ability, c);
		}
		upgrades = 2;
		int abilityNum;
		while (upgrades > 0)
		{
			upgradeUsed = false;
			roll = random_int(1, (7 * player.getNumAbilities()) + 2);

			switch (roll) {
			case 1:
				player.setMovement(player.getMovement() + 1);
				upgradeUsed = true;
				break;
			case 2:
				player.setArmor(player.getArmor() + 1);
				upgradeUsed = true;
				break;
			default:
				if (roll > 2 && roll < 10)
				{
					ability = player.getAbility(0);
					roll -= 2;
					abilityNum = 0;
				}
				else if (roll > 9 && roll < 17)
				{
					ability = player.getAbility(1);
					roll -= 9;
					abilityNum = 1;
				}
				else if (roll > 16 && roll < 24)
				{
					ability = player.getAbility(2);
					roll -= 16;
					abilityNum = 2;
				}

				if (roll == 1)
				{
					if (ability.getRange() > 1)
					{
						upgradeUsed = true;
						ability.setRange(ability.getRange() + 1);
						player.setAbility(ability, abilityNum);
					}
				}
				else if (roll == 2)
				{
					if (ability.getAOE() > 0)
					{
						upgradeUsed = true;
						ability.setAOE(ability.getAOE() + 1);
						player.setAbility(ability, abilityNum);
					}
				}
				else if (roll == 3)
				{
					upgradeUsed = true;
					ability.setDuplicate(ability.getDuplicate() + 1);
					player.setAbility(ability, abilityNum);
				}
				else if (roll == 4)
				{
					if (ability.getDamage() > 0)
					{
						upgradeUsed = true;
						ability.setDamage(ability.getDamage() + 1);
						player.setAbility(ability, abilityNum);
					}
				}
				else if (roll == 5)
				{
					upgradeUsed = true;
					ability.setToHit(ability.getToHit() + 1);
					player.setAbility(ability, abilityNum);
				}
				else if (roll == 6)
				{
					if (ability.getStun() == 0.5)
					{
						upgradeUsed = true;
						ability.setStun(1);
						player.setAbility(ability, abilityNum);
					}
				}
				else if (roll == 7)
				{
					if (ability.getCooldown() > 1)
					{
						upgradeUsed = true;
						ability.setCooldown(ability.getCooldown() - 1);
						player.setAbility(ability, abilityNum);
					}
				}
				break;
			}

			if (upgradeUsed == true)
			{
				upgrades--;
			}
		}
		playerList[i] = player;
	}
}

void uniqueAbility()
{
	EntityAbility ability = playerList[turnIDMap[turn]].getAbility(nowAbilityID);
	if (ability.getName() == "castle")
	{
		playerList[turnIDMap[turn]].shield(20);
		addToLog("Castle has been used, player's Armor is now 20");
		ability.used();
		pcHasAction = false;
	}
	else if (ability.getName() == "shield")
	{
		playerList[turnIDMap[turn]].shield(playerList[turnIDMap[turn]].getArmor() + 3);
		addToLog("Shield has been used, player's Armor is now "+ to_string(playerList[turnIDMap[turn]].getArmor()));
		ability.used();
		pcHasAction = false;
	}
	else if (ability.getName() == "wall")
	{
		/// redraw nowMap
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
			pcHasAction = false;
		}
	}
	else if (ability.getName() == "counter")
	{
		playerList[turnIDMap[turn]].shield(20);
		displayListOfEnemies = true;
		addToLog("Counter has been used, player's Armor is now 20");
		ability.used();
		pcHasAction = false;
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
		addToLog("Reload has been used, all ability cooldowns are reset");
		ability.used();
		pcHasAction = false;
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
		addToLog("Players in facinity are healed by 1");
		ability.used();
		pcHasAction = false;
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
		addToLog("Anyone dead has been revived");
		ability.used();
		pcHasAction = false;
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
		addToLog("Random player now does double damage");
		ability.used();
		pcHasAction = false;
	}
	playerList[turnIDMap[turn]].setAbility(ability, nowAbilityID);
}

void attack(int id)
{
	pcHasAction = false;
	EntityAbility ability = playerList[turnIDMap[turn]].getAbility(nowAbilityID);
	ability.used();
	playerList[turnIDMap[turn]].setAbility(ability, nowAbilityID);
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

		//Mark turn as dead, remove from turnID map and now enemy list
	if (nowEnemies[id].getHP() <= 0) {
		turnDeadMap[nowEnemies[id].getTurn()] = true;
		turnIDMap.erase(nowEnemies[id].getTurn());

		for (int i = 0; i < nowEnemies.size(); ++i)
			if(turnIDMap[nowEnemies[i].getTurn()] != 0)
				turnIDMap[nowEnemies[i].getTurn()] -= 1;

		nowEnemies.erase(nowEnemies.begin() + id);
	}
	ability.used();
	pcHasAction = false;
	playerList[turnIDMap[turn]].setAbility(ability, nowAbilityID);
}

void updatePopUpMessage()
{
	if (popUpMessage) {

		
		switch (popUpMessageState) {

		case Lost: {
			LoseScreen();
			ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
			//cam.DisplayWelcomeScreen(641, 638, 1, tp.GetTexture(Lost_Screen));
			break;
		}
		case TotalWin: {
			GameWinScreen();
			ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
			//cam.DisplayWelcomeScreen(641, 638, 1, tp.GetTexture(Final_Win_Screen));
			break;
		}
		case LevelWin: {
			LevelWinScreen();
			ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
			//cam.DisplayWelcomeScreen(641, 638, 1, tp.GetTexture(Current_Level_Win_Screen));
			break;
		}
		case None: {
			//cam.DisplayWelcomeScreen(641, 638, 1, tp.GetTexture(Lost_Screen));    // just for testing the screen code 
			break;
		}
		}

	}
}

int rollTheDice(int bonus, int AC)
{
	// 0 = no damage, 1 = damage, 2 = critical
	int roll = random_int(1, 20);
	addToLog("You rolled a " + to_string(roll));
	if (roll == 1)
	{
		addToLog("Critical Miss!");
		return 0;
	}
	else if (roll == 20)
	{
		addToLog("Critical Hit!");
		return 2;
	}
	else
	{
		roll += bonus;
		addToLog("Your hit was a " + to_string(roll));
		addToLog("The Armor is " + to_string(AC));
		if (roll >= AC)
		{
			addToLog("You hit");
			return 1;
		}
		else
		{
			addToLog("You missed");
			return 0;
		}
	}
}

void movePlayer(int X, int Z)
{
	int posX = playerList[turnIDMap[turn]].getPosX();
	int posZ = playerList[turnIDMap[turn]].getPosZ();
	int newPosX = playerList[turnIDMap[turn]].getPosX() + X;
	int newPosZ = playerList[turnIDMap[turn]].getPosZ() + Z;

	if (newPosX >= 0 && newPosX < nowMap->GetX() && newPosZ >= 0 && newPosZ < nowMap->GetZ())
	{
		if (nowMap->GetValue(newPosX, newPosZ) == 0)
		{
			playerList[turnIDMap[turn]].rotatePlayer(X, Z);
			playerList[turnIDMap[turn]].setPosX(newPosX);
			playerList[turnIDMap[turn]].setPosZ(newPosZ);
			playerList[turnIDMap[turn]].movePlayer();
			nowMap->SetValue(posX, posZ, 0);
			nowMap->SetValue(newPosX, newPosZ, 2);
		}
	}
}

void moveArrow(int X, int Z)
{
	int rangeX = originalArrowPosX - AOEArrowPosX;
	int rangeZ = originalArrowPosZ - AOEArrowPosZ;
	EntityAbility nowAbility = playerList[turnIDMap[turn]].getAbility(nowAbilityID);
	if (rangeX < 0)
	{
		rangeX *= -1;
	}
	if (rangeZ < 0)
	{
		rangeZ *= -1;
	}
	if ((rangeX + rangeZ) <= nowAbility.getRange())
	{
		AOEArrowPosX += X;
		AOEArrowPosZ += Z;
	}
}

void abilityPressed(int id)
{
	nowAbilityID = id;// -1;
	EntityAbility nowAbility = playerList[turnIDMap[turn]].getAbility(nowAbilityID);
	if (nowAbility.getUnique())
	{
		uniqueAbility();
	}
	else if(nowAbility.getAOE() > 1)
	{
		displayAOE = true;
		AOEArrowPosX = playerList[turnIDMap[turn]].getPosX();
		AOEArrowPosZ = playerList[turnIDMap[turn]].getPosZ();
	}
	else
	{
		displayListOfEnemies = true;
	}
}

void AOEAbility()
{
	EntityAbility nowAbility = playerList[turnIDMap[turn]].getAbility(nowAbilityID);
	int rangeX;
	int rangeZ;
	for (int i = 0; i < nowEnemies.size(); i++)
	{
		rangeX = nowEnemies[i].getPosX() - AOEArrowPosX;
		rangeZ = nowEnemies[i].getPosZ() - AOEArrowPosZ;
		if (rangeX < 0)
		{
			rangeX *= -1;
		}
		if (rangeZ < 0)
		{
			rangeZ *= -1;
		}
		if ((rangeX + rangeZ) <= nowAbility.getAOE())
		{
			attack(i);
		}
	}
}

int random_int(int min, int max)
{
	return min + rand() % (max + 1 - min);
}