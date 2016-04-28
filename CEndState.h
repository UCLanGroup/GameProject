#pragma once
#include <IEngine.h>
#include "CGameState.h"
#include <memory>

#include "CPanel.h"
#include "CLabel.h"
#include "IMouseEventHandler.h"

using namespace tle_ui;

class CEndState : public CGameState, public IMouseEventHandler
{
private:
	using CLabel_ptr = std::unique_ptr<CLabel>;
	using CPanel_ptr = std::unique_ptr<CPanel>;

	static CEndState mEndState;

	CPanel_ptr mFrame;
	CLabel_ptr mMessageLabel;
	CLabel_ptr mScoreLabel;

	//UI Interface sounds
	tle::ISound* mMouseOverSound;
	tle::ISound* mMouseClickSound;

	tle::IFont* mFont90;
	tle::IFont* mFont60;

	float mDelta = 0.0f;

	bool mWinner = false;

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

	//Misc

	void SetEndState(bool win, int score);

	//UI Event handling

	//Handles events from the mouse being moved over a component
	void MouseEnteredEvent(const CMouseEvent& mouseEvent);

	//Handles events from the mouse being moved off of a component
	void MouseExittedEvent(const CMouseEvent& mouseEvent);

	//Handles events from the a component being clicked on
	void MouseClickedEvent(const CMouseEvent& mouseEvent);

	//Handles events from the mouse being moved while over a component
	void MouseMovedEvent(const CMouseEvent& mouseEvent);

	static CEndState* Instance()
	{
		return &mEndState;
	}

protected:
	CEndState() {}

};