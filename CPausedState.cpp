#include "Globals.h"
#include "CGameStateHandler.h"
#include "CPausedState.h"
#include "CIntroState.h"
#include "COptionsState.h"
#include "CMouseEvent.h"
#include <iostream>

CPausedState CPausedState::mPausedState;

// Setup and destroy state
void CPausedState::Init()
{
	//Disable auto updating of animations and particle emitters
	gEngine->PauseAutoUpdates();

	//Create fonts
	mFont60 = gEngine->LoadFont("Rockwell", 60U);
	mFont48 = gEngine->LoadFont("Rockwell", 48U);
	mFont36 = gEngine->LoadFont("Rockwell", 36U);

	mMouseOverSound = gEngine->CreateSound(SOUND_MOUSE_OVER);
	mMouseOverSound->SetType(SoundType::Interface);
	mMouseClickSound = gEngine->CreateSound(SOUND_MOUSE_CLICK);
	mMouseClickSound->SetType(SoundType::Interface);

	//Create UI container
	mFrame.reset(new CPanel());
	mFrame->SetSize(gEngine->GetWidth(), gEngine->GetHeight());

	mPausedLabel.reset(new CLabel(mFont60, "Paused"));
	mPausedLabel->SetHeight(90);
	mPausedLabel->SetVertAlignment(Alignment::Top);
	mFrame->Add(mPausedLabel.get());

	mResumeButton.reset(new CButton(mFont36, "Resume"));
	mResumeButton->SetEventHandler(this);
	mResumeButton->SetSounds(mMouseOverSound, mMouseClickSound);
	mFrame->Add(mResumeButton.get());

	mOptionsButton.reset(new CButton(mFont36, "Options"));
	mOptionsButton->SetEventHandler(this);
	mOptionsButton->SetSounds(mMouseOverSound, mMouseClickSound);
	mFrame->Add(mOptionsButton.get());

	mQuitButton.reset(new CButton(mFont36, "Quit"));
	mQuitButton->SetEventHandler(this);
	mQuitButton->SetSounds(mMouseOverSound, mMouseClickSound);
	mFrame->Add(mQuitButton.get());

	mPopFlag = false;
	mOptionsFlag = false;
	mQuitFlag = false;
}

void CPausedState::Cleanup()
{
	mFrame.reset();
	mPausedLabel.reset();
	mResumeButton.reset();
	mOptionsButton.reset();
	mQuitButton.reset();

	//Remove fonts
	gEngine->RemoveFont(mFont60);
	gEngine->RemoveFont(mFont48);
	gEngine->RemoveFont(mFont36);

	//Removes Sounds
	gEngine->RemoveSound(mMouseOverSound);
	gEngine->RemoveSound(mMouseClickSound);

	//Re-enable auto updating of animations and particle emitters
	gEngine->UnpauseAutoUpdates();
}

// Temporarily transition to another state
void CPausedState::Pause()
{

}

//Resumes from a paused state
void CPausedState::Resume()
{
	mPopFlag = false;
	mOptionsFlag = false;
	mQuitFlag = false;

	mResumeButton->SetFocus(false);
	mOptionsButton->SetFocus(false);
	mQuitButton->SetFocus(false);
}

// Game loop actions

//Handles the events from the engine
void CPausedState::HandleEvents(CGameStateHandler* game)
{
	if (gEngine->GetMouseMovementX() != 0 || gEngine->GetMouseMovementY() != 0)
	{
		mFrame->CheckEvent(CMouseEvent(0, CMouseEvent::Mouse_Moved, gEngine->GetMouseX(), gEngine->GetMouseY()));
	}
	
	if (gEngine->KeyHit(tle::Mouse_LButton))
	{
		mFrame->CheckEvent(CMouseEvent(0, CMouseEvent::Mouse_Clicked, gEngine->GetMouseX(), gEngine->GetMouseY()));
	}

	mFrame->KeyEvent(GetKeyHit());

	if(gEngine->KeyHit(KEY_PAUSE) || mPopFlag)
	{
		game->PopState();
	}

	if (gEngine->KeyHit(KEY_EXIT) || mQuitFlag)
	{
		game->ChangeState(CIntroState::Instance());
	}

	if (mOptionsFlag)
	{
		game->PushState(COptionsState::Instance());
	}
}

//Updates any game logic
void CPausedState::Update(CGameStateHandler* game)
{
	mDelta = gEngine->Timer();
}

//Draws any components that need to be explicitly draw each frame
void CPausedState::Draw(CGameStateHandler* game)
{
	mFrame->Draw();
	gEngine->DrawScene();
}

//Handles events from the mouse being moved over a component
void CPausedState::MouseEnteredEvent(const CMouseEvent& mouseEvent)
{

}

//Handles events from the mouse being moved off of a component
void CPausedState::MouseExittedEvent(const CMouseEvent& mouseEvent)
{

}

//Handles events from the a component being clicked on
void CPausedState::MouseClickedEvent(const CMouseEvent& mouseEvent)
{
	if (mouseEvent.GetSource() == mResumeButton.get())
	{
		mPopFlag = true;
	}
	else if (mouseEvent.GetSource() == mOptionsButton.get())
	{
		mOptionsFlag = true;
	}
	else if (mouseEvent.GetSource() == mQuitButton.get())
	{
		mQuitFlag = true;
	}
}

//Handles events from the mouse being moved while over a component
void CPausedState::MouseMovedEvent(const CMouseEvent& mouseEvent)
{

}