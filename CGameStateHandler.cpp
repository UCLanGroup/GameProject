// Last updated: 04.02.16

#include <TL-Engine.h>

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CGameState.h"

using namespace tle;

void CGameStateHandler::Init()
{
	// Create the window
	gEngine->StartWindowed(1280, 1024);

	gEngine->SetWindowCaption(WINDOWCAPTION);

	// Add default folder for meshes and other media
	gEngine->AddMediaFolder( ".\\Media" );
}

void CGameStateHandler::Cleanup()
{
	// Cleanup states
	while (!mpGameStates.empty())
	{
		mpGameStates.back()->Cleanup();
		mpGameStates.pop_back();
	}
}

void CGameStateHandler::ChangeState(CGameState* state)
{
	// Cleanup current state
	if (!mpGameStates.empty())
	{
		mpGameStates.back()->Cleanup();
		mpGameStates.pop_back();
	}

	// Initialise new state
	mpGameStates.push_back(state);
	mpGameStates.back()->Init();
}

void CGameStateHandler::PushState(CGameState* state)
{
	// Pause current state
	if (!mpGameStates.empty())
	{
		mpGameStates.back()->Pause();
	}

	// Initialise new state
	mpGameStates.push_back(state);
	mpGameStates.back()->Init();
}

void CGameStateHandler::PopState()
{
	// Cleanup current state
	if (!mpGameStates.empty())
	{
		mpGameStates.back()->Cleanup();
		mpGameStates.pop_back();
	}

	// Resume previous state
	if (!mpGameStates.empty())
	{
		mpGameStates.back()->Resume();
	}
}

void CGameStateHandler::HandleEvents()
{
	mpGameStates.back()->HandleEvents(this);
}

void CGameStateHandler::Update()
{
	mpGameStates.back()->Update(this);
}

void CGameStateHandler::Draw()
{
	mpGameStates.back()->Draw(this);
}

void CGameStateHandler::Quit()
{
	gEngine->Stop();
}
