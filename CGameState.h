#pragma once
// Last updated: 04.02.16

#include "CGameStateHandler.h"


class CGameState
{
public:
	// Setup and destroy state
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	// Temporarily transition to another state
	virtual void Pause() = 0;
	virtual void Resume() = 0;

	// Game loop actions
	virtual void HandleEvents(CGameStateHandler* game) = 0;
	virtual void Update(CGameStateHandler* game) = 0;
	virtual void Draw(CGameStateHandler* game) = 0;

	void ChangeState(CGameStateHandler* game, CGameState* state)
	{
		game->ChangeState(state);
	}

protected: 
	CGameState() {}
};