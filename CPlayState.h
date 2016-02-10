#pragma once
// Last updated: 04.02.16

#include <TL-Engine.h>

#include "CGameState.h"

using namespace tle;

class CPlayState : public CGameState
{
private:
	static CPlayState mPlayState;

	ISprite* mBackground;

	float mDelta = 0.0f;		// Delta time (to render previous frame)

public:
	// Setup and destroy state
	void Init();
	void Cleanup();

	// Temporarily transition to another state
	void Pause();
	void Resume();

	// Game loop actions
	void HandleEvents(CGameStateHandler* game);
	void Update(CGameStateHandler* game);
	void Draw(CGameStateHandler* game);

	static CPlayState* Instance()
	{
		return &mPlayState;
	}

protected: CPlayState() {}
};