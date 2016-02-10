#pragma once
// Last updated: 04.02.16

#include <vector>
#include <memory>
#include <TL-Engine.h>

using namespace tle;

//Types
template <typename T>
using vector_ptr = std::vector<std::unique_ptr<T>>; // Combines vector and unique_ptr

// Globals
extern tle::I3DEngine* gEngine;


// Constants
		// Window
const string WINDOWCAPTION	= "Shooty Game WT";

		// Intro screen
const string INTROBG		= "menu.png";				// Temporary background image
const string INTROSTART		= "menustart.png";			// Temporary start text

		// Gameplay
const string UI				= "ui.png";					// Tempororay user interface


// Key codes
const EKeyCode KEY_EXIT = tle::Key_Escape;
const EKeyCode KEY_START = tle::Key_Space;