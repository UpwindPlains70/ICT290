//GUI lidrary
#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"

#include "DataHandler.h"
#include "GL/glut.h"
#include "TextureHandler.h"
#include "UpdateHandler.h"

/**
 * @brief Defines all User Interface menus
 *
 *
 * @author Peter Neve
 * @version 01
 * @date 24/09/2021 Peter Neve, Started
 */

void intialiseUI();
void shutdownUI();

void classSelectionUI();
void classTextureUI();

void TextCentered(const char* text);

extern bool playerSelection;

class UIHandler
{
};

