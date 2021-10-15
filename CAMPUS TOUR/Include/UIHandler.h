//GUI lidrary

#pragma once

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"

#include "DataHandler.h"
#include "GL/glut.h"
#include "TextureHandler.h"
#include "UpdateHandler.h"
#include <filesystem>
#include <iostream>
#include <string>

/**
 * @brief Defines all User Interface menus
 *
 *
 * @author Peter Neve
 * @version 01
 * @date 24/09/2021 Started
 * 
 * @author Peter Neve
 * @version 02
 * @date 25/09/2021 add class image preview (issue: game crashes if image not found)
 */

 /**
		  * @brief  Initialise all basic ImGui functionality & style (dark)
		  *
		  * @return void
		  */
void intialiseUI();

/**
		 * @brief  Shutdown all ImGui functions
		 *
		 * @return void
		 */
void shutdownUI();

/**
		 * @brief  Defines UI for character selection menu
		 *
		 * accepts player name input, class selection (with preview), all character stats and abilities
		 * Allows players to create more than one character (displays list of current names at bottom)
		 * Fetures 'save', 'clear' 'finish' buttons
		 * Save: store current player info and add to player list (cannot save player with empty name)
		 * Clear: Remove all players
		 * Finish: Only works if their is one or more players, closes the UI
		 *
		 * @return void
		 */
void classSelectionUI();

/**
		 * @brief  Defines UI for character preview
		 * 
		 * Inludes player name, class type, and image preview of class character
		 *
		 * @return void
		 */
void characterPreviewUI();

/**
		 * @brief  Centers text to middle of the UI
		 *
		 * This function allows text to stay centred (horizontally) with UI despite its size
		 *
		 * @return void
		 */
void TextCentered(const char* text);

/**
		 * @brief  Load class preview texture
		 *
		 * This function allows images to be loaded for display in character selection menu
		 * Issue: game crashes if the file is not found
		 *
		 * @return void
		 */
void loadClassPreview();

void playerHUD();
//display select enemy stats
void enemyStats();

/**
		 * @brief  Turn order decider
		 *
		 * This function displays a number for players (in order)
		 * ISSUE: last player does not see their turn number before UI disapears 
		 *
		 * @return void
		 */
void turnOrderUI();

//Turn roll
void playerActionUI();

	//Ends player turn if selected
void displayEnemyListUI();

extern bool playerSelection;
extern bool assignTurnStage;

extern bool displayListOfEnemies;
