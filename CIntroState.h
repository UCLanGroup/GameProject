#pragma once
// Last updated: 04.02.16

#include <TL-Engine.h>

#include "CGameState.h"

using namespace tle;

class CIntroState : public CGameState
{
private:
	static CIntroState mIntroState;

	ISprite* mBackground;

	float mDelta = 0.0f;		// Delta time (to render previous frame)
	float mMove = 0.0f;			// For background animation
	bool mMoveRight = true;

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

	static CIntroState* Instance()
	{
		return &mIntroState;
	}

protected: CIntroState() {}
};