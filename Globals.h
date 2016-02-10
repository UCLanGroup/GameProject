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
const string GROUNDSKIN		= "ground.png";

const string GROUNDMESH		= "ground.x";
const string PLAYERMESH		= "mig29.x";
const string BULLET_MESH	= "Bullet.x";

const float AREA_BOUNDS_TOP		= 300.0f;
const float AREA_BOUNDS_RIGHT	= 300.0f;
const float AREA_BOUNDS_LEFT	= -300.0f;
const float AREA_BOUNDS_BOTTOM	= -300.0f;


// Key codes
const EKeyCode KEY_EXIT = tle::Key_Escape;
const EKeyCode KEY_START = tle::Key_Space;

const EKeyCode KEY_LEFT = tle::Key_Left;
const EKeyCode KEY_RIGHT = tle::Key_Right;
const EKeyCode KEY_UP = tle::Key_Up;
const EKeyCode KEY_DOWN = tle::Key_Down;

const EKeyCode KEY_FIRE = tle::Key_Space;