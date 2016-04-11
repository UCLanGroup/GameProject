#pragma once
#include <IEngine.h>
#include "CGameState.h"
#include <memory>

#include "CPanel.h"
#include "CLabel.h"

using namespace tle_ui;

class CPausedState : public CGameState
{
private:

	static CPausedState mPausedState;

	std::unique_ptr<CPanel> mFrame;
	std::unique_ptr<CLabel> mPausedLabel;

	IFont* mFont;

	float mDelta = 0.0f;

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

	static CPausedState* Instance()
	{
		return &mPausedState;
	}

protected: CPausedState() {}
};