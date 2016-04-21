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

	mResumeLabel.reset(new CLabel(mFont36, "Resume"));
	mResumeLabel->SetEventHandler(this);
	mResumeLabel->SetSounds(mMouseOverSound, mMouseClickSound);
	mFrame->Add(mResumeLabel.get());

	mOptionsLabel.reset(new CLabel(mFont36, "Options"));
	mOptionsLabel->SetEventHandler(this);
	mOptionsLabel->SetSounds(mMouseOverSound, mMouseClickSound);
	mFrame->Add(mOptionsLabel.get());

	mQuitLabel.reset(new CLabel(mFont36, "Quit"));
	mQuitLabel->SetEventHandler(this);
	mQuitLabel->SetSounds(mMouseOverSound, mMouseClickSound);
	mFrame->Add(mQuitLabel.get());

	mPopFlag = false;
	mOptionsFlag = false;
	mQuitFlag = false;
}

void CPausedState::Cleanup()
{
	mFrame.reset();
	mPausedLabel.reset();
	mResumeLabel.reset();
	mOptionsLabel.reset();
	mQuitLabel.reset();

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

	mResumeLabel->SetColor(tle::kWhite);
	mOptionsLabel->SetColor(tle::kWhite);
	mQuitLabel->SetColor(tle::kWhite);
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
	if (mouseEvent.GetSource() == mResumeLabel.get())
	{
		mResumeLabel->SetColor(tle::kRed);
	}
	else if (mouseEvent.GetSource() == mOptionsLabel.get())
	{
		mOptionsLabel->SetColor(tle::kRed);
	}
	else if (mouseEvent.GetSource() == mQuitLabel.get())
	{
		mQuitLabel->SetColor(tle::kRed);
	}
}

//Handles events from the mouse being moved off of a component
void CPausedState::MouseExittedEvent(const CMouseEvent& mouseEvent)
{
	if (mouseEvent.GetSource() == mResumeLabel.get())
	{
		mResumeLabel->SetColor(tle::kWhite);
	}
	else if (mouseEvent.GetSource() == mOptionsLabel.get())
	{
		mOptionsLabel->SetColor(tle::kWhite);
	}
	else if (mouseEvent.GetSource() == mQuitLabel.get())
	{
		mQuitLabel->SetColor(tle::kWhite);
	}
}

//Handles events from the a component being clicked on
void CPausedState::MouseClickedEvent(const CMouseEvent& mouseEvent)
{
	if (mouseEvent.GetSource() == mResumeLabel.get())
	{
		mPopFlag = true;
	}
	else if (mouseEvent.GetSource() == mOptionsLabel.get())
	{
		mOptionsFlag = true;
	}
	else if (mouseEvent.GetSource() == mQuitLabel.get())
	{
		mQuitFlag = true;
	}
}

//Handles events from the mouse being moved while over a component
void CPausedState::MouseMovedEvent(const CMouseEvent& mouseEvent)
{

}