#pragma once
// Last updated: 04.02.16

#include <vector>
#include <memory>
#include <TL-Engine.h>
#include "Vector3.h"

using namespace tle;

//Types
template <typename T>
using vector_ptr = std::vector<std::unique_ptr<T>>; // Combines vector and unique_ptr

// Globals
extern tle::I3DEngine* gEngine;


// Constants
		//File paths
const string MEDIA_FOLDER	= ".\\Media";

		// Window
const string WINDOW_CAPTION	= "Shooty Game WT";

		// Intro screen
const string INTRO_BG			= "menu.png";				// Temporary background image
const string INTRO_START		= "menustart.png";			// Temporary start text

		// Gameplay
const string UI					= "ui.png";					// Tempororay user interface
const string GROUND_SKIN		= "ground.png";

const string GROUND_MESH		= "ground.x";
const string PLAYER_MESH		= "mig29.x";
const string BULLET_MESH		= "Bullet.x";
const string SHIELD_MESH		= "Shield.x";

const string DEFAULT_ENEMY_MESH = "f16.x";
const string HAVOC_BOSS_MESH = "Mi28Havoc.x";

		//Explosions
const string EXPLOSION_MESH = "Explosion.x";
const string EXPLOSION_SPRITE = "Explosion";
const int EXPLOSION_SPRITE_COUNT = 34;
const float EXPLODE_RATE = 0.03f;

		//Collision
const float AREA_BOUNDS_TOP		= 100.0f;
const float AREA_BOUNDS_RIGHT	= 120.0f;
const float AREA_BOUNDS_LEFT	= -120.0f;
const float AREA_BOUNDS_BOTTOM	= -100.0f;

const float OFF_SCREEN_X		= 1000.0f;
const float OFF_SCREEN_Y		= 1000.0f;
const float OFF_SCREEN_Z		= 1000.0f;

// Key codes
const EKeyCode KEY_EXIT = tle::Key_Escape;
const EKeyCode KEY_START = tle::Key_Space;

const EKeyCode KEY_LEFT = tle::Key_Left;
const EKeyCode KEY_RIGHT = tle::Key_Right;
const EKeyCode KEY_UP = tle::Key_Up;
const EKeyCode KEY_DOWN = tle::Key_Down;

const EKeyCode KEY_FIRE = tle::Key_Space;