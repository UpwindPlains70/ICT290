#include "UIHandler.h"


// Our state
static int classID = 0;
static const char* current_item = "";
static char playerName[25];
static char** abilities = nullptr;

bool playerSelection = false;
bool gameHUD = false;

bool assignTurnStage = true;
bool displayListOfEnemies = false;

	//turn list index
int i = 0;
int prevSelectedTurn = 0;
int playerTurnCount = 0;
int enemyTurnCount = 0;
int actionNumber = 0;

// display exit screen
bool DisplayExit = false;

void intialiseUI()
{
#ifdef __FREEGLUT_EXT_H__
	glutMouseWheelFunc(ImGui_ImplGLUT_MouseWheelFunc);
#endif

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGLUT_Init();
	ImGui_ImplOpenGL2_Init();

	io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF("packages/imgui-master/misc/fonts/Roboto-Medium.ttf", 150.0f);	//Dice number font & size
	io.Fonts->AddFontFromFileTTF("packages/imgui-master/misc/fonts/Roboto-Medium.ttf", 50.0f);  //Dice spin button font & size
	io.Fonts->AddFontFromFileTTF("packages/imgui-master/misc/fonts/Roboto-Medium.ttf", 35.0f);	//Action menu font & size
}
void shutdownUI()
{
	// Cleanup
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGLUT_Shutdown();
	ImGui::DestroyContext();
}

void TextCentered(const char* text) {
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(text);
}

void characterPreviewUI()
{
	ImGui::Begin("Character Preview", NULL, ImGuiWindowFlags_NoResize);
	TextCentered(playerName);
	TextCentered(allClasses[classID].name.c_str());

	ImGui::Image((void*)(intptr_t)tp.GetTexture(246), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));
	ImGui::End();
}

void loadClassPreview()
{
	string path = "data/Class/Class Previews/" + allClasses[classID].name + ".raw";
	char* tempPath = &path[0];

	image = tp.LoadTexture(tempPath, 1024, 1024, false);
	tp.CreateTexture(246, image, 1024, 1024);
}

void classSelectionUI()
{
	playerSelection = true;
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		//ImGui::ShowDemoWindow();

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoResize;

	//UI to input player name, select class & shows its information
	{
		ImGui::Begin("Player class selection", NULL, window_flags);    // Create a window
		ImGui::Text("Player Name: ");
		ImGui::SameLine();
		ImGui::InputText("##name", playerName, 25);
		ImGui::Text("Class:   \t");
		ImGui::SameLine();

		current_item = allClasses[classID].name.c_str();
		if (ImGui::BeginCombo("##classOptions", current_item, ImGuiWindowFlags_NoScrollbar)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < allClasses.size(); ++n)
			{
				bool is_selected = (strcmp(current_item, allClasses[n].name.c_str())); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(allClasses[n].name.c_str(), is_selected)) {		
					classID = n;
					loadClassPreview();
				}
					if (is_selected)
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
			}
			ImGui::EndCombo();
		}

		ImGui::Text("Health: %d", allClasses[classID].hp);               // Display classes health
		ImGui::Text("Armour: %d", allClasses[classID].armor);               // Display classes armour
		ImGui::Text("Movement: %d", allClasses[classID].movement);               // Display classes movement


		ImGui::Text("Ability List: (%d)", allClasses[classID].abilityList.size());
		ImGui::BeginChild("ChildL", ImVec2(ImGui::GetContentRegionAvail().x, 250));
			for (int i = 0; i < allClasses[classID].abilityList.size(); ++i)
				ImGui::Text("\t%s", allClasses[classID].abilityList[i].getName().c_str());
		ImGui::EndChild();

			//Adds player to player List
		if (ImGui::Button("Save Player")) {
			if (strlen(playerName) != 0) {
				Player tempPlayer(playerName, allClasses[classID].name, allClasses[classID].hp, allClasses[classID].movement, allClasses[classID].armor);

				tempPlayer.setAbilities(allClasses[classID].abilityList);
				playerList.push_back(tempPlayer);
				//cout << playerList.size() << endl;
				//clear player name when saved
				memset(playerName, 0, sizeof playerName);
			}
		}
			//Removes all players from playerList
		ImGui::SameLine();
		if (ImGui::Button("Clear Players"))
			playerList.clear();

			//Finalisez player selection for the game
		ImGui::SameLine();
		if (ImGui::Button("Finish Selection"))
		{
			if (playerList.size() != 0) 
			{
				playerSelection = false;
				gameState = Ready;
				gameHUD = true;
			}
		}

		ImGui::Text("Player List (%d): ", playerList.size());
		ImGui::SameLine();
		ImGui::BeginChild("playerListChild", ImVec2(ImGui::GetContentRegionAvail().x, 25), false,  ImGuiWindowFlags_HorizontalScrollbar);
		for (int i = 0; i < playerList.size(); ++i) {
			ImGui::Text("%s, ", playerList[i].getName().c_str());
			ImGui::SameLine();
		}
		ImGui::EndChild();

		ImGui::End();
	}

	// 3. Show character Preview window
	characterPreviewUI();

	// Rendering
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

	glutPostRedisplay();
}

//display player stats
void playerHUD()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoResize;
	
	//Simple window to show player stats
	{
		ImGui::Begin("Player Stats", NULL, window_flags);    // Create a window
		
			//Define game info (level no. & turn no.)
		ImGui::BeginChild("GameInfo", ImVec2(ImGui::GetContentRegionAvail().x, 25), false);
			ImGui::Text("Level: %d", currLevel);
			ImGui::SameLine();
			ImGui::Text("\tRound: %d", sessionRound);
		ImGui::EndChild();

		ImGui::BeginChild("PlayerInfoA", ImVec2(ImGui::GetContentRegionAvail().x, 55), false);
			ImGui::Text("Player Name: %s", playerList[turnIDMap[turn]].getName().c_str());
			ImGui::Text("Class:   \t%s", playerList[turnIDMap[turn]].getClassName().c_str());
			ImGui::Text("Turn pos:\t%d", playerList[turnIDMap[turn]].getTurn());
		ImGui::EndChild();

		ImGui::BeginChild("PlayerInfoB", ImVec2(ImGui::GetContentRegionAvail().x, 55), false);
			ImGui::Text("Health:  \t%d", playerList[turnIDMap[turn]].getHP());               // Display some text (you can use a format strings too)
			ImGui::Text("Armour:  \t%d", playerList[turnIDMap[turn]].getArmor());               // Display some text (you can use a format strings too)
			ImGui::Text("Movement:\t%d", playerList[turnIDMap[turn]].getMovement());               // Display some text (you can use a format strings too)
		ImGui::EndChild();

		ImGui::End();
	}

	enemyStats();

	if(displayActionMenu)
		playerActionUI();

	// Rendering
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

	glutPostRedisplay();
}

//display select enemy stats
void enemyStats()
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	//if (show_demo_window)
		//ImGui::ShowDemoWindow(&show_demo_window);
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoResize;

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		ImGui::Begin("Enemy Stats", NULL, window_flags);    // Create a window

		for(int i = 0; i < nowEnemies.size(); ++i)
		{
			ImGui::BeginChild("EnemyTitles" + i, ImVec2(ImGui::GetContentRegionAvail().x, 70), false, ImGuiWindowFlags_NoScrollbar);
			ImGui::Text("Enemy Name: %s", nowEnemies[i].getName().c_str());
			ImGui::Text("Turn pos:\t%d", nowEnemies[i].getTurn());
			ImGui::Text("Health:  \t%d", nowEnemies[i].getHP());               // Display some text (you can use a format strings too)
			ImGui::Text("Armour:  \t%d", nowEnemies[i].getArmor());               // Display some text (you can use a format strings too)
			ImGui::Text("Movement:\t%d", nowEnemies[i].getMovement());               // Display some text (you can use a format strings too)
			ImGui::EndChild();
		}
		ImGui::End();
	}
}

//Turn order decider
void turnOrderUI()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	//if (show_demo_window)
		//ImGui::ShowDemoWindow(&show_demo_window);
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	//window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGuiIO& io = ImGui::GetIO();

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		ImGui::Begin("Decide Turn Order", NULL, window_flags);    // Create a window

		srand(time(NULL));
			//Restrict to single calculation
		if (!turnList.empty()) 
		{
			//Assign players order first
			if (playerTurnCount < playerList.size())
			{
				for (i = 0; i < turnList.size(); ++i)
				{		//Define game info (level no. & turn no.)
					if (i == (rand() % turnList.size())) {
						prevSelectedTurn = turnList[i];
						if (playerTurnCount < playerList.size()) {
							turnList.erase(turnList.begin() + i);
							playerList[playerTurnCount].setTurn(prevSelectedTurn);
							//turn pointing to player index
							turnIDMap[prevSelectedTurn] = playerTurnCount;
							isPCTurnMap[prevSelectedTurn] = true;
							++playerTurnCount;
						}
					}
				}
			}

			//When all players are assigned, assign enemies
			if (playerTurnCount >= playerList.size())
			{
				for (i = 0; i < turnList.size(); ++i)
				{		//Define game info (level no. & turn no.)
					
					if (i == (rand() % turnList.size())) {
						prevSelectedTurn = turnList[i];
						//on match found remove from turn list
						turnList.erase(turnList.begin() + i);
						nowEnemies[enemyTurnCount].setTurn(prevSelectedTurn);
						turnIDMap[prevSelectedTurn] = enemyTurnCount;
						isPCTurnMap[prevSelectedTurn] = false;
						++enemyTurnCount;
					}
				}
			}
		}
		//Font size 150 (set in initialise UI)
			//Display player & enemy name : turn number

		ImGui::BeginChild("turnOrder", ImVec2(ImGui::GetContentRegionAvail().x, 120));
		ImGui::PushFont(io.Fonts->Fonts[3]);
		for (int i = 0; i < playerList.size(); ++i)
		{
			ImGui::BeginChild("turnOrderP" + i, ImVec2(ImGui::GetContentRegionAvail().x, 40), false, ImGuiWindowFlags_NoScrollbar);
			ImGui::Text("%s: %d", playerList[i].getName().c_str(), playerList[i].getTurn());
			ImGui::EndChild();
		}
		for (int i = 0; i < nowEnemies.size(); ++i)
		{
			ImGui::BeginChild("turnOrderE" + i, ImVec2(ImGui::GetContentRegionAvail().x, 40), false, ImGuiWindowFlags_NoScrollbar);
			ImGui::Text("%s: %d", nowEnemies[i].getName().c_str(), nowEnemies[i].getTurn());
			ImGui::EndChild();
		}
		ImGui::PopFont();
		ImGui::EndChild();

		//Place 'okay' button in middle of UI frame
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize("Okay").x;

		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.4f);
		//Font size 50 (set in initialise UI)
		//Okay button to close Turn order UI frame
		ImGui::PushFont(io.Fonts->Fonts[2]);
			//Only display okay button if all turns have been assigned
		if (turnList.empty()) {
			if (ImGui::Button("Okay"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			{
				assignTurnStage = false;
				enemyTurnCount = 0;
				playerTurnCount = 0;
			}
		}
		ImGui::PopFont();
		
		ImGui::End();
	}

	// Rendering
	ImGui::Render();
	io = ImGui::GetIO();
	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

	glutPostRedisplay();
}

//Player action menu (attack, move, end turn)
void playerActionUI()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize("Spin").x;

	ImGuiIO& io = ImGui::GetIO();
	//Roll 20 sides 'dice'
	/*{
		ImGui::Begin("Action Dice", NULL, window_flags);    // Create a window

			//Font size 150 (set in initialise UI)
		ImGui::PushFont(io.Fonts->Fonts[1]);
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.15f);
		ImGui::Text("%d", actionNumber);
		ImGui::PopFont();

		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.15f);
		//Font size 50 (set in initialise UI)
		ImGui::PushFont(io.Fonts->Fonts[2]);
		if (ImGui::Button("Spin") && allowedToRoll)                            // Buttons return true when clicked (most widgets return true when edited/activated)
		{
			srand(time(NULL));
			for (i = 1; i <= 20; ++i)
			{		//Define game info (level no. & turn no.)
				if (i == (rand() % 20 + 1)) {
					actionNumber = i;
					//cout << actionNumber << endl;
						//Limits to one roll per turn
					allowedToRoll = false;
					break;
				}
			}
		}
		ImGui::PopFont();

		ImGui::End();
	}
	*/

	//Simple window to show player actions
	{
		ImGui::Begin("Player Actions Menu", NULL, window_flags);    // Create a window


		ImGui::PushFont(io.Fonts->Fonts[3]);
		if (displayListOfEnemies)
			displayEnemyListUI();
		else
		{
			for (int i = 0; i < playerList[turnIDMap[turn]].getNumAbilities(); ++i)
			{
				ImGui::SameLine();
				if (playerList[turnIDMap[turn]].getAbility(i).canUseAbility() && canAction)
				{
					if (ImGui::Button((playerList[turnIDMap[turn]].getAbility(i).getName()).c_str())) {
						abilityPressed(i);
					}
				}
				else
				{
					ImGui::Button((playerList[turnIDMap[turn]].getAbility(i).getName()+": "+to_string(playerList[turnIDMap[turn]].getAbility(i).getCooldownCounter())).c_str());
				}
			}

			ImGui::Text("Remaining Movement: %d", playerList[turnIDMap[turn]].getMovementLeft());
		}

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + windowWidth - ImGui::CalcTextSize("End Turn").x);
		if (ImGui::Button("End Turn"))
		{
			endTurn();
		}

		ImGui::PopFont();
		ImGui::End();
	}

}

void displayEnemyListUI()
{
	for (int i = 0; i < nowEnemies.size(); ++i)
	{
		ImGui::SameLine();
		
		if (playerList[turnIDMap[turn]].getAbility(nowAbilityID).getRange() >= playerList[turnIDMap[turn]].checkRange(nowEnemies[i].getPosX(), nowEnemies[i].getPosZ())) {
			if (ImGui::Button(nowEnemies[i].getName().c_str())) {
				//attack this enemy
				attack(i);
				displayListOfEnemies = false;
			}
		}
	}

	if (ImGui::Button("Cancel"))
	{
		displayListOfEnemies = false;
	}
}

void LevelWinScreen()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();

	ImGuiIO& io = ImGui::GetIO();

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Level Cleared", NULL, window_flags);
	//cam.DisplayWelcomeScreen(641, 638, 1, tp.GetTexture(Current_Level_Win_Screen));
	ImGui::BeginChild("imageTextureC", ImVec2(ImGui::GetContentRegionAvail().x, 550));
		ImGui::Image((void*)(intptr_t)tp.GetTexture(Current_Level_Win_Screen), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));
	ImGui::EndChild();

	ImGui::PushFont(io.Fonts->Fonts[3]);
		//Teleport player back to bush court
	LobbyButton();
	QuitButton();
	ImGui::SameLine();
	if (ImGui::Button("Next Level")) {	
		//increase random player stat
		upgrade();
		++currLevel;
		assignTurnStage = true;
		gameState = Initialising;
		//Disable this screen
		popUpMessage = false;
		popUpMessageState = None;  // Stops the enum state from being anything else eg if it used to be TotalWin, it is now set to None
	}
	ImGui::PopFont();
	ImGui::End();

	// Rendering
	ImGui::Render();
	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

	glutPostRedisplay();
}

void LoseScreen()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();

	ImGuiIO& io = ImGui::GetIO();

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Level Cleared", NULL, window_flags);
	//cam.DisplayWelcomeScreen(641, 638, 1, tp.GetTexture(Lost_Screen));
	ImGui::BeginChild("imageTextureL", ImVec2(ImGui::GetContentRegionAvail().x, 550));
		ImGui::Image((void*)(intptr_t)tp.GetTexture(Lost_Screen), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));
	ImGui::EndChild();

	ImGui::PushFont(io.Fonts->Fonts[3]);
	//Teleport player back to bush court
	LobbyButton();
	QuitButton();

	ImGui::PopFont();
	ImGui::End();

	// Rendering
	ImGui::Render();
	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

	glutPostRedisplay();
}

void GameWinScreen()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();

	ImGuiIO& io = ImGui::GetIO();

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Level Cleared", NULL, window_flags);
	//cam.DisplayWelcomeScreen(641, 638, 1, tp.GetTexture(Final_Win_Screen));
	ImGui::BeginChild("imageTextureF", ImVec2(ImGui::GetContentRegionAvail().x, 550));
	ImGui::Image((void*)(intptr_t)tp.GetTexture(Final_Win_Screen), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));
	ImGui::EndChild();

	ImGui::PushFont(io.Fonts->Fonts[3]);
	//Teleport player back to bush court
	if (ImGui::Button("Back to Lobby")) {
		currLevel = 0;
		teleportToSpawn();
		//Disable this screen
		popUpMessage = false;
		popUpMessageState = None;  // Stops the enum state from being anything else eg if it used to be TotalWin, it is now set to None
		gameState = NotGame;
	}
	ImGui::SameLine();
	if (ImGui::Button("Quit Game")) {
		//Enable quit screen
		DisplayExit = true;
		//Disable this screen
		popUpMessage = false;
		popUpMessageState = None;  // Stops the enum state from being anything else eg if it used to be TotalWin, it is now set to None
	}
	ImGui::PopFont();
	ImGui::End();

	// Rendering
	ImGui::Render();
	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

	glutPostRedisplay();
}

void QuitButton()
{
	ImGui::SameLine();
	if (ImGui::Button("Quit Game")) {
		//Enable quit screen
		DisplayExit = true;
		//Disable this screen
		popUpMessage = false;
		popUpMessageState = None;  // Stops the enum state from being anything else eg if it used to be TotalWin, it is now set to None
	}
}

void LobbyButton()
{
	if (ImGui::Button("Back to Lobby")) {
		currLevel = 0;
		teleportToSpawn();
		//Disable this screen
		popUpMessage = false;
		popUpMessageState = None;  // Stops the enum state from being anything else eg if it used to be TotalWin, it is now set to None
		gameState = NotGame;
	}
}