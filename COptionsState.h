#pragma once
#include <IEngine.h>
#include "KeyBinds.h"
#include "CGameState.h"
#include <memory>

#include "CPanel.h"
#include "CLabel.h"
#include "CSpinner.h"
#include "IMouseEventHandler.h"

using namespace tle_ui;

EKeyCode GetKeyHit();

class COptionsState : public CGameState, public IMouseEventHandler
{
private:
	using CLabel_ptr = std::unique_ptr<CLabel>;
	using CPanel_ptr = std::unique_ptr<CPanel>;
	using CButton_ptr = std::unique_ptr<CButton>;
	using CSpinner_ptr = std::unique_ptr<CSpinner>;

	static COptionsState mOptionsState;

	CPanel_ptr mFrame;

	//Option menu header
	CLabel_ptr mOptionsLabel;

	//Controls rebinds header
	CLabel_ptr mControlsLabel;

	//Fire key control
	CPanel_ptr mFireKeyPanel;
	CLabel_ptr mFireKeyLabel;
	CButton_ptr mFireKeyButton;

	//Up key control
	CPanel_ptr mUpKeyPanel;
	CLabel_ptr mUpKeyLabel;
	CButton_ptr mUpKeyButton;

	//Down key control
	CPanel_ptr mDownKeyPanel;
	CLabel_ptr mDownKeyLabel;
	CButton_ptr mDownKeyButton;

	//Left key control
	CPanel_ptr mLeftKeyPanel;
	CLabel_ptr mLeftKeyLabel;
	CButton_ptr mLeftKeyButton;

	//Right key control
	CPanel_ptr mRightKeyPanel;
	CLabel_ptr mRightKeyLabel;
	CButton_ptr mRightKeyButton;

	//Sound controls header
	CLabel_ptr mSoundLabel;

	//Master volume control
	CPanel_ptr mMasterVolumePanel;
	CLabel_ptr mMasterVolumeLabel;
	CSpinner_ptr mMasterVolumeSpinner;

	//Music volume control
	CPanel_ptr mMusicVolumePanel;
	CLabel_ptr mMusicVolumeLabel;
	CSpinner_ptr mMusicVolumeSpinner;
	
	//SFX volume control
	CPanel_ptr mSFXVolumePanel;
	CLabel_ptr mSFXVolumeLabel;
	CSpinner_ptr mSFXVolumeSpinner;

	//Interface volume control
	CPanel_ptr mInterfaceVolumePanel;
	CLabel_ptr mInterfaceVolumeLabel;
	CSpinner_ptr mInterfaceVolumeSpinner;

	//Return button
	CButton_ptr mBackButton;

	tle::IFont* mFont60;
	tle::IFont* mFont48;
	tle::IFont* mFont36;
	tle::IFont* mFont28;
	tle::IFont* mFont24;

	//UI Interface sounds
	tle::ISound* mMouseOverSound;
	tle::ISound* mMouseClickSound;

	float mDelta = 0.0f;

	bool mPopFlag = false;
	bool mFireKeyFlag = false;
	bool mUpKeyFlag = false;
	bool mDownKeyFlag = false;
	bool mRightKeyFlag = false;
	bool mLeftKeyFlag = false;
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