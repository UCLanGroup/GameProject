#pragma once
#include <IEngine.h>
#include "CGameState.h"
#include <memory>

#include "CPanel.h"
#include "CLabel.h"
#include "CButton.h"
#include "IMouseEventHandler.h"

using namespace tle_ui;

class CPausedState : public CGameState, public IMouseEventHandler
{
private:
	using CLabel_ptr = std::unique_ptr<CLabel>;
	using CPanel_ptr = std::unique_ptr<CPanel>;
	using CButton_ptr = std::unique_ptr<CButton>;

	static CPausedState mPausedState;

	CPanel_ptr mFrame;
	CLabel_ptr mPausedLabel;
	CButton_ptr mResumeButton;
	CButton_ptr mOptionsButton;
	CButton_ptr mQuitButton;

	//UI Interface sounds
	tle::ISound* mMouseOverSound;
	tle::ISound* mMouseClickSound;

	IFont* mFont60;
	IFont* mFont48;
	IFont* mFont36;

	float mDelta = 0.0f;

	bool mPopFlag = false;
	bool mOptionsFlag = false;
	bool mQuitFlag = false;

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

	//UI Event handling

	//Handles events from the mouse being moved over a component
	void MouseEnteredEvent(const CMouseEvent& mouseEvent);

	//Handles events from the mouse being moved off of a component
	void MouseExittedEvent(const CMouseEvent& mouseEvent);

	//Handles events from the a component being clicked on
	void MouseClickedEvent(const CMouseEvent& mouseEvent);

	//Handles events from the mouse being moved while over a component
	void MouseMovedEvent(const CMouseEvent& mouseEvent);

	static CPausedState* Instance()
	{
		return &mPausedState;
	}

protected:
	CPausedState() {}

};