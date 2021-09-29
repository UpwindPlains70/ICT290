#include "UpdateHandler.h"

int currLevel = 1;
int mapID;
//enum state { NotReady, Ready, Initialising, StartTurn, Action, Attack, Win, Lose, AttackAOE};
state gameState = NotReady;
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
vector<int> turnList;

bool firstRun = true;
bool displayActionMenu = false;
bool allowedToRoll = true;

using namespace std;

void Update()
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
	switch (gameState) {
		case NotReady:
				//stuck until finished button is pressed
			classSelectionUI();
			ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

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

				/// <Task 7> (Anyone)
				/// figure out enemies for currLevel
				/// place enemies into nowEnemies
				/// </Task 7>

				maxTurn = playerList.size() + nowEnemies.size();

				for (int i = 1; i <= maxTurn; ++i)
					turnList.push_back(i);

				/// <Task 9> (Raymond)
				/// Randomly choose location 
				/// Place first enemy
				///	If more enemies
				///	While('found' == false)
				///	Randomly choose location
				///	for (int i = -2; i <= 2; i++)
				///		for (int j = -2; j <= 2; j++)
				///			'newX' = 'locationX' + i
				///			'newY' = 'locationY' + j
				///			if (there is an enemy at map[newX][newY])
				///				'found' = true
				///	Repeat for each
				///	Do the same for players
				/// </Task 9>

				/// <Task 16> (Jason)
				/// start drawing players and enemies in their positions
				
				displayCharacters = true; 
		
				/// </Task 16>

			}//	figure out turn order (Every level)
			if(assignTurnStage)
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
				//set player turn
				if (isPCTurnMap.find(turn) != isPCTurnMap.end())
					isPCTurnMap[turn] = true;
			}
				break;
		case StartTurn:
				//Display player & enemy stats
			playerHUD();
			ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

			if (turnDeadMap[turn] == true)
			{
				if (isPCTurnMap[turn] == false)
				{
					enemyTurn(nowEnemies[turnIDMap[turn]]);
				}
				else
				{
					playerTurn(playerList[turnIDMap[turn]]);
				}
				endTurn();
			}
			
			break;
		case Action:
				//Display player & enemy stats
			playerHUD();
			ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
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
				//Display player & enemy stats
			playerHUD();
			ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

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
			if (currLevel == 10)
			{
				/// <Task 21> (Jason)
				/// show final win screen
				/// </Task 21>
			}
			else
			{
				/// <Task 22> (Jason)
				/// show currLevel win screen
				/// </Task 22>
				upgrade();
				currLevel++;
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

	updateModels(); 
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
	allowedToRoll = true;
}

void playerTurn(Player pc)
{
		// display pc actions
	displayActionMenu = true;

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

void updateModels() { // called at the end of the update function

	/// <Task 16> (Jason)
				/// start drawing players and enemies in their positions

	//DisplayPlayerModel("Zombie", 123, 9000, -21);  // example usage with a zombie 

	if (displayCharacters) { // displayCharacters is a boolean value that is either set true or false in the Update() function

		if (playerList.size() > 0) {
			for (int i = 0; i < playerList.size(); i++) {
				DisplayPlayerModel(playerList[i].getClassName(), playerList[i].getPosX(), 9000, playerList[i].getPosZ());
			}
		}
		if (nowEnemies.size() > 0) {
			for (int i = 0; i < nowEnemies.size(); i++) {
				DisplayPlayerModel(nowEnemies[i].getName(), nowEnemies[i].getPosX(), 9000, nowEnemies[i].getPosZ());
			}
		}


	}


	/// </Task 16>

}
