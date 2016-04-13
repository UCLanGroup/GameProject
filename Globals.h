#pragma once
// Last updated: 04.02.16

#include <vector>
#include <memory>
#include <IEngine.h>
#include <SFML/Audio.hpp>

using namespace tle;

// Globals
extern sf::Music gMusic;
extern tle::IEngine* gEngine;

// Constants
		//File paths
const string MEDIA_FOLDER		= ".\\Media";

		// Window
const string WINDOW_CAPTION		= "Shooty Game WT";

		// Intro screen
const string INTRO_BG			= "menu.png";				// Temporary background image
const string INTRO_START		= "menustart.png";			// Temporary start text

		// Sound
const string MUSIC				= MEDIA_FOLDER + "\\music.flac";
const string SOUND_SHOOT		= MEDIA_FOLDER + "\\shoot.flac";
const string SOUND_START		= MEDIA_FOLDER + "\\start.flac";

		// Gameplay
const string UI					= "ui.png";					// Tempororay user interface
const string UI2				= "ui2.png";
const string LOADING_SCREEN		= "loading_screen.png";
const string LOADING_BAR		= "loading_bar.png";
const string LOADING_BARBACK	= "loading_barback.png";
const string HEALTHBAR			= "healthbar.png";

const string GROUND_SKIN		= "ground.png";

const string GROUND_MESH		= "ground.x";
const string SKYBOX_MESH		= "skybox.x";
const string GRASS_TEX			= "grass.jpg";
const string METAL_TEX			= "stone.jpg";

const string DUMMY_MESH			= "dummy.x";
const string PLAYER_MESH		= "mig29.x";
const string PLAYER_TEX			= "mig29.jpg";
const string PLAYER_INVUL_TEX	= "mig29Invul";
const string BULLET_MESH		= "Bullet.x";
const string MISSILE_MESH		= "missile1.x";
const string SHIELD_MESH		= "Shield.x";
const string LASER_BEAM_TEX		= "LaserBeam.png";

const string F16_ENEMY_MESH		= "f16.x";
const string HAVOC_BOSS_MESH	= "Mi28Havoc.x";

const string SHOTGUN_POWER_UP	= "SpreadShotPowerUp.png";
const string LASER_POWER_UP = "LaserPowerUp.png";
const string UPGRADE_POWER_UP = "UpgradePowerUp.png";

		//Explosions
const string EXPLOSION_MESH		= "Explosion.x";
const string EXPLOSION_SPRITE	= "Explosion";
const int EXPLOSION_SPRITE_COUNT = 34;
const float EXPLODE_RATE = 0.03f;

		//Collision
const float AREA_BOUNDS_TOP		= 100.0f;
const float AREA_BOUNDS_RIGHT	= 120.0f;
const float AREA_BOUNDS_LEFT	= -120.0f;
const float AREA_BOUNDS_BOTTOM	= -70.0f;

const float OFF_SCREEN_X		= 1000.0f;
const float OFF_SCREEN_Y		= 1000.0f;
const float OFF_SCREEN_Z		= 1000.0f;

// Key codes
const EKeyCode KEY_EXIT = tle::Key_Escape;
const EKeyCode KEY_START = tle::Key_Space;
const EKeyCode KEY_PAUSE = tle::Key_P;

const EKeyCode KEY_LEFT = tle::Key_Left;
const EKeyCode KEY_RIGHT = tle::Key_Right;
const EKeyCode KEY_UP = tle::Key_Up;
const EKeyCode KEY_DOWN = tle::Key_Down;

const EKeyCode KEY_FIRE = tle::Key_Space;