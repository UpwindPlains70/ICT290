#include "UIHandler.h"


// Our state
static int classID;
static const char* current_item = "";
static char playerName[25];
static char** abilities = nullptr;

bool playerSelection = true;

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

void classTextureUI()
{
	ImGui::Begin("Character Preview", NULL, ImGuiWindowFlags_NoResize);
	TextCentered(playerName);
	TextCentered(allClasses[classID].name.c_str());

	ImGui::Image((void*)(intptr_t)tp.GetTexture(DungeonFloor), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));
	ImGui::End();
}

void classSelectionUI()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	//if (show_demo_window)
		//ImGui::ShowDemoWindow(&show_demo_window);
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoResize;

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		ImGui::Begin("Player class selection", NULL, window_flags);    // Create a window
		ImGui::Text("Player Name: ");
		ImGui::SameLine();
		ImGui::InputText("\t", playerName, 25);
		ImGui::Text("Class:   \t");
		ImGui::SameLine();
		if (ImGui::BeginCombo("\t.", current_item)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < allClasses.size(); ++n)
			{
				bool is_selected = (strcmp(current_item, allClasses[n].name.c_str())); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(allClasses[n].name.c_str(), is_selected)) {
					current_item = allClasses[n].name.c_str();
					classID = n;
				}
					if (is_selected)
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
			}
			ImGui::EndCombo();
		}

		ImGui::Text("Health: %d", allClasses[classID].hp);               // Display some text (you can use a format strings too)
		ImGui::Text("Armour: %d", allClasses[classID].armor);               // Display some text (you can use a format strings too)
		ImGui::Text("Movement: %d", allClasses[classID].movement);               // Display some text (you can use a format strings too)


		ImGui::Text("Ability List: (%d)", allClasses[classID].abilityList.size());
		ImGui::BeginChild("ChildL", ImVec2(ImGui::GetContentRegionAvail().x, 250));
			for (int i = 0; i < allClasses[classID].abilityList.size(); ++i)
				ImGui::Text("\t%s", allClasses[classID].abilityList[i].getName().c_str());
		ImGui::EndChild();


		//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//	counter++;
		//ImGui::Text("counter = %d", counter);

		if (ImGui::Button("Save Player")) {
			if (strlen(playerName) != 0) {
				Player tempPlayer(playerName, allClasses[classID].name, allClasses[classID].hp, allClasses[classID].movement, allClasses[classID].armor);
				playerList.push_back(tempPlayer);
				//clear player name when saved
				memset(playerName, 0, sizeof playerName);
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Clear Players"))
			playerList.clear();

		ImGui::SameLine();
		if (ImGui::Button("Finish Selection"))
		{
			if (playerList.size() != 0) 
			{
				playerSelection = false;
				gameState = Ready;
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

	// 3. Show another simple window.
	classTextureUI();

	// Rendering
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

	glutPostRedisplay();
}