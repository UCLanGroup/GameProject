// Professional Skills Assignment.cpp: A program using the TL-Engine
// Last updated: 04.02.16

#include <TL-Engine.h>	// TL-Engine include file and namespace

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CIntroState.h"
#include "IDebug.h"
using namespace tle;

// declared as extern in 'Globals.h'
I3DEngine* gEngine = 0;
sf::Music gMusic;

void main()
{
	IDebug::Open("game.log");
	Log("Log started at function: %s", __FUNCTION__);

	// Initialise the game
	gEngine = New3DEngine(kTLX);
	CGameStateHandler game;
	game.Init();

	
	// Intro screen
	game.ChangeState(CIntroState::Instance());

	// Main game loop
	while (gEngine->IsRunning())
	{
		if(gEngine->IsActive())
		{
			game.HandleEvents();
			game.Update();
			game.Draw();
		}
	}

	// Cleanup states before exit
	game.Cleanup();
	gEngine->Delete();
	gEngine = 0;
	IDebug::Close();
}