#ifndef MOVEMENTHANDLER_H
#define MOVEMENTHANDLER_H

#include "CollisionHandler.h"
#include "DisplayHandler.h"
#include "backends/imgui_impl_glut.h"
#include "UpdateHandler.h"
#include "UIHandler.h"

	/**
	 * @brief Handles all movement controls
	 *
	 * @author Shay Leary
	 * @version 01
	 * @date March 2005, Finished
	 *
	 * @author Peter Neve
	 * @version 02
	 * @date 20/08/2021 Peter Neve, fixed quit issue (closing bool - used in main.cpp display)
	 * 
	 * @author Peter Neve
	 * @version 02
	 * @date 28/08/2021 Peter Neve, Refactor
	 * 
	 * @author Peter Neve
	 * @version 03
	 * @date 24/09/2021 implemented mygui control funcs
	 * 
	 * @author Peter Neve
	 * @version 04
	 * @date 20/10/2021, refactored movement into Tour and Game only available when in world
	 * 
	 */

	/**
	 * @brief Capture keyboard key (no arrow keys)
	 *
	 * Uses TourControls and GameControls
	 * 
	 * @return void
	 */
void keys(unsigned char key, int x, int y);

	/**
	 * @brief defines key behaviour while in bush court
	 *
	 * @return void
	 */
void TourControls(unsigned char key, int x, int y);

	/**
	 * @brief Defines keyboard behaviour while in game
	 *
	 * @return void
	 */
void GameControls(unsigned char key, int x, int y);

	/**
	 * @brief Controls AOE arrow object movement
	 *
	 * @return void
	 */
void ArrowControls(unsigned char key, int x, int y);

	/**
	 * @brief Capture special key presses (arrow keys)
	 *
	 * @return void
	 */
void movementKeys(int key, int x, int y);

	/**
	 * @brief Capture special key release (arrow key)
	 *
	 * @return void
	 */
void releaseKey(int key, int x, int y);	

	/**
	 * @brief Capture normal keyboard key release (not arrow key)
	 *
	 * @return void
	 */
void releaseKeys(unsigned char key, int x, int y);

	/**
	 * @brief Capture mouse click
	 *
	 * @return void
	 */
void Mouse(int button, int state, int x, int y);

		/**
		 * @brief  Mouse movement (incomplete / unused)
		 *
		 * @return void
		 */
void mouseMove(int x, int y);

	/// screen width and height
extern int width, height;

	/// display campus map
extern bool DisplayMap;

	/// display welcome screen
extern bool DisplayWelcome;

	/// display ECL block
extern bool displayECL;

	///control display quit
extern bool closing;

/// USE THESE STTEINGS TO CHANGE SPEED (on different spec computers)
/// Set speed (steps)
extern GLdouble movementSpeed;
extern GLdouble rotationSpeed;

#endif // !MOVEMENTHANDLER_H