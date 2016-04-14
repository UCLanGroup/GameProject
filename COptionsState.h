#pragma once
#include <IEngine.h>
#include "CGameState.h"
#include <memory>

#include "CPanel.h"
#include "CLabel.h"
#include "IMouseEventHandler.h"

using namespace tle_ui;

class COptionsState : public CGameState, public IMouseEventHandler
{
private:
	using CLabel_ptr = std::unique_ptr<CLabel>;
	using CPanel_ptr = std::unique_ptr<CPanel>;

	enum MenuState {Options, Controls, Sound, Graphics, Nick_Mode};
	MenuState menuState;

	static COptionsState mOptionsState;

	CPanel_ptr mFrame;
	CLabel_ptr mOptionsLabel;
	CLabel_ptr mControlsLabel;
	CLabel_ptr mSoundLabel;
	CLabel_ptr mBackLabel;

	tle::IFont* mFont60;
	tle::IFont* mFont48;
	tle::IFont* mFont36;
	tle::IFont* mFont28;
	tle::IFont* mFont24;

	float mDelta = 0.0f;

	bool mPopFlag = false;
	bool mBackFlag = false;

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

	static COptionsState* Instance()
	{
		return &mOptionsState;
	}

protected:
	COptionsState() {}

};