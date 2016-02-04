// Professional Skills Assignment.cpp: A program using the TL-Engine
// Last updated: 04.02.16

#include <TL-Engine.h>	// TL-Engine include file and namespace

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CIntroState.h"

using namespace tle;

// declared as extern in 'Globals.h'
I3DEngine* gEngine = New3DEngine(kTLX);



void main()
{
	// Initialise the game
	CGameStateHandler game;
	game.Init();
	
	// Intro screen
	game.ChangeState(CIntroState::Instance());

	// Main game loop
	while (gEngine->IsRunning())
	{
		game.HandleEvents();
		game.Update();
		game.Draw();
	}

	// Cleanup states before exit
	game.Cleanup();
	gEngine->Delete();
}
