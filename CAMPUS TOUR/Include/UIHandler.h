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
 * @author Peter Neve
 * @version 01
 * @date 24/09/2021 Started
 * 
 * @author Peter Neve
 * @version 02
 * @date 25/09/2021 add class image preview (issue: game crashes if image not found)
 * 
 * @author Peter Neve
 * @version 03
 * @date 19/10/2021 fixed turn order assignment (single confirmation click) & win/lose/final win screen with buttons
 * 
 * @author Peter Neve
 * @version 04
 * @date 20/10/2021 cooldown actions, & single action
 * 
 * @author Mark Burns
 * @version 05
 * @date 20/10/2021, AOE behaviour and confirmation button
 *  
 * @author Peter Neve
 * @version 06
 * @date 22/10/2021, added player ability listing to playerHUD
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

		/**
		 * @brief  Display player UI and call other UI elements
		 *
		 * This function displays current players stats and all active enemy stats
		 *
		 * calls enemyStats() and gameLog()
		 * on player turn calls playerActionUI()
		 * @return void
		 */
void playerHUD();

		/**
		 * @brief  Display enemy stats
		 *
		 * This function displays all active enemy stats
		 *
		 * @return void
		 */
void enemyStats();

		/**
		 * @brief  Display game log for last ten actions
		 *
		 *
		 * @return void
		 */
void gameLog();
		
		/**
		 * @brief  Add an action to the gamelog
		 *
		 * This function adds action logs to the game log removing the oldest log
		 * resticting it to ten entries
		 *
		 * @return void
		 */
void addToLog(string add);

		/**
		 * @brief  clear game log
		 *
		 * This function clears the game log for a fresh start
		 * 
		 * @return void
		 */
void clearLog();

		/**
		 * @brief  Turn order decider
		 *
		 * This function displays a number for each player and enemy indicating the turn number
		 * unable to leave until all numbers are assigned
		 *
		 * @return void
		 */
void turnOrderUI();

		/**
		 * @brief  Display player action UI panel
		 *
		 * This function displays an action panel where players can see their 
		 * remaining movement, in range abilities (selectable) and end turn button
		 *
		 * @return void
		 */
void playerActionUI();

	/**
	 * @brief  Display list of enemies within selected abilities range
	 *
	 * This function displays all enemies within range of ability and attacks the selected one.
	 * Players can go back or end their turn
	 *
	 * @return void
	 */
void displayEnemyListUI();

		/**
		 * @brief  Display AOE action menu
		 *
		 * This function displays an attack button to confirm AOE placement
		 * enables AOE positioning
		 *
		 * @return void
		 */
void displayAOEUI();

	///prevents code from loading when players are selecting classes
extern bool playerSelection;

	///prevents code from loading when turn order is being assigned
extern bool assignTurnStage;

	///allows list of enemies to display in action menu (controlled by pressing an ability)
extern bool displayListOfEnemies;

	///allows AOE indicator (arrow) to display and move
extern bool displayAOE;

	/// display exit screen
extern bool DisplayExit;

		/**
		 * @brief  Display level cleared screen
		 *
		 * This function displays an image notifying players of complete level
		 * includes lobby and quit button, also next level button
		 *
		 * @return void
		 */
void LevelWinScreen();

		/**
		 * @brief  Display game over screen 
		 *
		 * This function displays a game over screen due to all players being dead
		 * includes lobby and quit buttons
		 *
		 * @return void
		 */
void LoseScreen();

		/**
		 * @brief  Display Game complete screen
		 *
		 * This function displays an image congradulating player for beating the game
		 * includes lobby and quit button
		 *
		 * @return void
		 */
void GameWinScreen();

		/**
		 * @brief  Display quit button
		 *
		 * This function defines the behaviour of the quit button for when a level is over
		 * Closes the application after displaying group photo
		 *
		 * @return void
		 */
void QuitButton();

		/**
		 * @brief  Display lobby button  
		 *
		 * This function defines the behaviour of the lobby button for when a level is over
		 * returns the player back to bush court
		 * Keeps the previous player list (except dead players)
		 *
		 * @return void
		 */
void LobbyButton();