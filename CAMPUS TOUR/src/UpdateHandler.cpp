#include "UpdateHandler.h"

int currLevel = 1;
int mapID = 0;
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
int sessionRound = 1;
LevelMap* nowMap = nullptr;

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
	DisplayPlayerModel("Samurai", 123, 9000, -21); // just for testing, can remove all these characters calls at any time
	DisplayPlayerModel("Zombie", 200, 9000, -21);
	DisplayPlayerModel("Wizard", 280, 9000, -21);
	DisplayPlayerModel("Skeleton", 360, 9000, -21);
	DisplayPlayerModel("FireGolum", 440, 9000, -21);
	DisplayPlayerModel("EarthGolum", 60, 9000, -21);
	DisplayPlayerModel("WaterGolum", -20, 9000, -21);
	DisplayPlayerModel("Beserker", -100, 9000, -21);
	DisplayPlayerModel("Shield", -190, 9000, -21);
	DisplayPlayerModel("Monk", -270, 9000, -21);
	DisplayPlayerModel("Swashbuckler", -350, 9000, -21);
	DisplayPlayerModel("Archer", -430, 9000, -21);
	DisplayPlayerModel("Artillery", -430, 9000, -150);
	DisplayPlayerModel("Bard", -350, 9000, -150);
	DisplayPlayerModel("Cleric", -270, 9000, -150);
	DisplayPlayerModel("Druid", -190, 9000, -150);
}

void Update()
{
	//DisplayLinup();
	switch (gameState) {
		case NotReady:
				//stuck until finished button is pressed
			classSelectionUI();
			ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

			canIJKL = false;
			canAction = false;
			canEndTurn = false;
			
			displayEnt = false;

			//nowMap = new LevelMap(mapList[level].at(rand() % mapList[level].size()));

			break;
		case Ready:
			/// <Task 4> (Anyone)
			/// Keep back doors locked until now.
			/// </Task 4>
			
			//if (levelZeroClear())
				gameState = Initialising;

			break;
		case Initialising:
			
			if (firstRun) {
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

				//Assign Enemies for current level
				nowLM = enemyLevelMap[currLevel];
				randNum = rand() % (nowLM.max - nowLM.min) + nowLM.min;
				for (int i = 0; i < randNum; i++)
				{
					nowEnemies.push_back(nowLM.presetList[rand() % nowLM.presetList.size()]);
				}

				maxTurn = playerList.size() + nowEnemies.size();

				for (int i = 1; i <= maxTurn; ++i)
					turnList.push_back(i);

				displayEnt = true;

				//Poisition enemies
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

				//Position players
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
				
				displayCharacters = true; 
		
				/// </Task 16>

			}//	figure out turn order (Every level)
			
			if (assignTurnStage)
			{
				turnOrderUI();
				ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
			}
			else 
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
			if (isPCTurnMap.find(turn) != isPCTurnMap.end())
				isPCTurnMap[turn] = true;

			if (turnDeadMap[turn] == false)
			{
				if (isPCTurnMap[turn] == false)
				{
					enemyTurn(nowEnemies[turnIDMap[turn]]);
				}
				else
				{
					playerTurn(playerList[turnIDMap[turn]]);
				}
				//endTurn();
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
			if (pcHasAction == true)
			{
				canAction = true;
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
				/// <Task 21> (Jason)
				/// show final win screen
				popUpMessageState = TotalWin;
				/// </Task 21>
			}
			else
			{
				/// show currLevel win screen
				popUpMessageState = LevelWin; 

					//increase random player stat
				upgrade();
				currLevel++;
				gameState = Initialising;
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

	positionFloorObjects(nowEnemies, playerList);

	if (gameState > 3) {
		playerHUD();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}
	//updateModels(); 
	updatePopUpMessage();
}

void endTurn()
{
	//playerList[turnIDMap[turn]] = playerList[turnIDMap[turn]];
	popUpMessage = true; 
	if (nowEnemies.size() == 0)
	{
		gameState = Win;
	}
	if (playerList.size() == 0)
	{
		gameState = Lose;
	}

	displayActionMenu = false;
	++turn;
	++sessionRound;
	gameState = StartTurn;
	if (turn > maxTurn)
	{
		turn = 1;
	}
	allowedToRoll = true;
}

void playerTurn(Player pc)
{
		// display pc actions
	displayActionMenu = true;

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
		ai.AIAttack(nowMap);
		
		
		/// <Task 13> (Jason)
		/// show stun being removed
		/// </Task 13>
	}
	else
	{
		// move enemy
		ai.AITurn(nowMap, playerList);

		/// randomly choose ability from enemy that is an ability in range of closest target
		ai.AIAttack(nowMap);
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

void updateModels() { // called at the end of the update function

	/// <Task 16> (Jason)
				/// start drawing players and enemies in their positions

	//DisplayPlayerModel("Zombie", 123, 9000, -21);  // example usage with a zombie 

	if (displayCharacters) { // displayCharacters is a boolean value that is either set true or false in the Update() function

		if (playerList.size() > 0) {
			for (int i = 0; i < playerList.size(); i++) {
				//cout << "X: " << playerList[i].getPosX() << " Z: " << playerList[i].getPosZ() << endl;
				playerEffects(playerList[i]);
				DisplayPlayerModel(playerList[i].getClassName(), playerList[i].getPosX(), 9000, playerList[i].getPosZ());
			}
		}
		if (nowEnemies.size() > 0) {
			for (int i = 0; i < nowEnemies.size(); i++) {
				//cout << nowEnemies[i].getName() << endl;
				enemyEffects(nowEnemies[i]);
				DisplayPlayerModel("Skeleton", nowEnemies[i].getPosX(), 9000, nowEnemies[i].getPosZ());
			}
		}
	}
	/// </Task 16>
}

void updatePopUpMessage()
{
	if (popUpMessage) {

		
		switch (popUpMessageState) {

		case Lost: {
			cam.DisplayWelcomeScreen(641, 638, 1, tp.GetTexture(Lost_Screen));
			break;
		}
		case TotalWin: {
			cam.DisplayWelcomeScreen(641, 638, 1, tp.GetTexture(Final_Win_Screen));
			break;
		}
		case LevelWin: {
			cam.DisplayWelcomeScreen(641, 638, 1, tp.GetTexture(Current_Level_Win_Screen));
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

void movePlayer(int X, int Z)
{
	playerList[turnIDMap[turn]].setPosZ(playerList[turnIDMap[turn]].getPosZ() + Z);
	playerList[turnIDMap[turn]].setPosX(playerList[turnIDMap[turn]].getPosX() + X);
	playerList[turnIDMap[turn]].movePlayer();
}

void abilityPressed(int id)
{
	nowAbilityID = id - 1;
	EntityAbility nowAbility = playerList[turnIDMap[turn]].getAbility(nowAbilityID);
	if (nowAbility.canUseAbility())
	{
		if (nowAbility.getUnique())
		{
			uniqueAbility();
		}
		else if(nowAbility.getAOE() > 1)
		{
			gameState = AttackAOE;
		}
		else
		{
			gameState = Attack;
		}
	}
}