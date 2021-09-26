#include "UpdateHandler.h"

int level = 1;
enum state { NotReady, Ready, Initialising, StartTurn, Action, Attack, Win, Lose, AttackAOE};
//state gameState = NotReady;
state gameState = Initialising;
map<int, bool> isPCTurnMap;
map<int, bool> turnDeadMap;
map<int, int> turnIDMap;
vector<Player> playerList;
bool pcHasAction;
Player nowPlayer;
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
			if (nowPlayer.canMove())
			{
				/// <Task 17> (Anyone)
				/// if keyboard 'w'
				///		nowPlayer.posZ += 1
				///		nowPlayer.MovementLeft--
				///	if keyboard 's'
				///		nowPlayer.posZ -= 1
				///		nowPlayer.MovementLeft--
				///	if keyboard 'a'
				///		nowPlayer.posX -= 1
				///		nowPlayer.MovementLeft--
				///	if keyboard 'd'
				///		nowPlayer.posX += 1
				///		nowPlayer.MovementLeft--
				/// </Task 17>
			}
			if (pcHasAction == true)
			{
				/// <Task 18> (Anyone)
				/// if keyboard '1'
				///		nowAbilityID = 0
				///		nowAbility = nowPlayer.GetAbility(0)
				///		if cooldownLeft
				///			if Ability.Unique = true
				///				uniqueAbility()
				///			elseif Ability.aoe > 1
				///				State = AttackAOE
				///			else
				///				State = Attack
				///	if keyboard '2'
				///		nowAbilityID = 1
				///		nowAbility = nowPlayer.GetAbility(1)
				///		if cooldownLeft
				///			if Ability.Unique = true
				///				uniqueAbility()
				///			elseif Ability.aoe > 1
				///				State = AttackAOE
				///			else
				///				State = Attack
				/// if keyboard '3'
				///		nowAbilityID = 2
				///		nowAbility = nowPlayer.GetAbility(2)
				///		if cooldownLeft
				///			if Ability.Unique = true
				///				uniqueAbility()
				///			elseif Ability.aoe > 1
				///				State = AttackAOE
				///			else
				///				State = Attack
				/// </Task 18>
			}
			if (nowPlayer.canMove() == false && pcHasAction == false)
			{
				playerList[turnIDMap[turn]] = nowPlayer;
				endTurn();
			}
			/// <Task 19> (Anyone)
			/// if keyboard '`'
			///		playerList[turnIDMap[turn]] = nowPlayer;
			///		endTurn();
			/// </Task 19>
			break;
		case Attack:
			/// <Task 20> (Anyone)
			/// show enemy select screen
			/// get player to decide on enemy to hit
			/// if decided:
			///		nowPlayer.GetAbility(nowAbilityID).used()
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
			///		nowPlayer.GetAbility(nowAbilityID).used()
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
	nowPlayer = pc;
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
		/// <Task 15> (Raymond)
		/// move enemy
		ai.AITurn(nowMap);
		/// </Task 15>

		/// <Task 14> (Raymond)
		/// randomly choose ability from enemy that is an ability in range of closest target
		/// if there is an ability and it has no cooldown left
		/// set as ability
		/// attack
		/// </Task 14>
		ai.AIAttack(nowMap);
	}
	ai.setStun(0);
	nowEnemies[turnIDMap[turn]] = ai;
	endTurn();
}

void upgrade()
{
	/// <Task 23> (Mark)
	/// needs to be filled in with upgrading each character and displaying the update
	/// </Task 23>
}

void uniqueAbility()
{
	/// <Task 24> (Mark)
	/// needs to be filled in with special actions and what happens
	/// </Task 24>
}

void attack(int id)
{
	/// <Task 25> (Mark)
	/// pcHasAction = false
	///	foreach duplicate
	///	if tohit
	///		damage
	///		stun
	/// </Task 25>
}
