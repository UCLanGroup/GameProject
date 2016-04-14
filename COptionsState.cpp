#include "Globals.h"
#include "CGameStateHandler.h"
#include "COptionsState.h"
#include "CMouseEvent.h"
#include <iostream>

COptionsState COptionsState::mOptionsState;

// Setup and destroy state
void COptionsState::Init()
{
	//Disable auto updating of animations and particle emitters
	gEngine->PauseAutoUpdates();

	//Create fonts
	mFont60 = gEngine->LoadFont("Rockwell", 60U);
	mFont48 = gEngine->LoadFont("Rockwell", 48U);
	mFont36 = gEngine->LoadFont("Rockwell", 36U);
	mFont28 = gEngine->LoadFont("Rockwell", 28U);
	mFont24 = gEngine->LoadFont("Rockwell", 24U);

	//Create UI container
	mFrame.reset(new CPanel());
	mFrame->SetSize(gEngine->GetWidth(), gEngine->GetHeight());

	mOptionsLabel.reset(new CLabel(mFont60, "Options"));
	mOptionsLabel->SetHeight(90);
	mOptionsLabel->SetVertAlignment(Alignment::Top);
	mFrame->Add(mOptionsLabel.get());

	mControlsLabel.reset(new CLabel(mFont36, "Controls"));
	mControlsLabel->SetEventHandler(this);
	mFrame->Add(mControlsLabel.get());

	mSoundLabel.reset(new CLabel(mFont36, "Sound"));
	mSoundLabel->SetEventHandler(this);
	mFrame->Add(mSoundLabel.get());

	mBackLabel.reset(new CLabel(mFont36, "Back"));
	mBackLabel->SetEventHandler(this);
	mFrame->Add(mBackLabel.get());

	mPopFlag = false;

	menuState = MenuState::Options;
}

void COptionsState::Cleanup()
{
	mFrame.reset();
	mOptionsLabel.reset();
	mControlsLabel.reset();
	mSoundLabel.reset();
	mBackLabel.reset();

	//Remove fonts
	gEngine->RemoveFont(mFont60);
	gEngine->RemoveFont(mFont48);
	gEngine->RemoveFont(mFont36);

	//Re-enable auto updating of animations and particle emitters
	gEngine->UnpauseAutoUpdates();
}

// Temporarily transition to another state
void COptionsState::Pause()
{

}

//Resumes from a paused state
void COptionsState::Resume()
{

}

// Game loop actions

//Handles the events from the engine
void COptionsState::HandleEvents(CGameStateHandler* game)
{
	if (gEngine->GetMouseMovementX() != 0 || gEngine->GetMouseMovementY() != 0)
	{
		mFrame->CheckEvent(CMouseEvent(0, CMouseEvent::Mouse_Moved, gEngine->GetMouseX(), gEngine->GetMouseY()));
	}

	if (gEngine->KeyHit(tle::Mouse_LButton))
	{
		mFrame->CheckEvent(CMouseEvent(0, CMouseEvent::Mouse_Clicked, gEngine->GetMouseX(), gEngine->GetMouseY()));
	}

	if (gEngine->KeyHit(KEY_EXIT) || mPopFlag)
	{
		game->PopState();
	}
}

//Updates any game logic
void COptionsState::Update(CGameStateHandler* game)
{
	mDelta = gEngine->Timer();
}

//Draws any components that need to be explicitly draw each frame
void COptionsState::Draw(CGameStateHandler* game)
{
	mFrame->Draw();
	gEngine->DrawScene();
}

//Handles events from the mouse being moved over a component
void COptionsState::MouseEnteredEvent(const CMouseEvent& mouseEvent)
{
	//if (mouseEvent.GetSource() == mResumeLabel.get())
	//{
	//	mResumeLabel->SetColor(tle::kRed);
	//}
	//else if (mouseEvent.GetSource() == mOptionsLabel.get())
	//{
	//	mOptionsLabel->SetColor(tle::kRed);
	//}
	//else if (mouseEvent.GetSource() == mQuitLabel.get())
	//{
	//	mQuitLabel->SetColor(tle::kRed);
	//}
}

//Handles events from the mouse being moved off of a component
void COptionsState::MouseExittedEvent(const CMouseEvent& mouseEvent)
{
	//if (mouseEvent.GetSource() == mResumeLabel.get())
	//{
	//	mResumeLabel->SetColor(tle::kWhite);
	//}
	//else if (mouseEvent.GetSource() == mOptionsLabel.get())
	//{
	//	mOptionsLabel->SetColor(tle::kWhite);
	//}
	//else if (mouseEvent.GetSource() == mQuitLabel.get())
	//{
	//	mQuitLabel->SetColor(tle::kWhite);
	//}
}

//Handles events from the a component being clicked on
void COptionsState::MouseClickedEvent(const CMouseEvent& mouseEvent)
{
	//if (mouseEvent.GetSource() == mResumeLabel.get())
	//{
	//	mPopFlag = true;
	//}
	//else if (mouseEvent.GetSource() == mOptionsLabel.get())
	//{
	//	//
	//}
	//else if (mouseEvent.GetSource() == mQuitLabel.get())
	//{
	//	mQuitFlag = true;
	//}
}

//Handles events from the mouse being moved while over a component
void COptionsState::MouseMovedEvent(const CMouseEvent& mouseEvent)
{

}