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

	//Option menu header
	mOptionsLabel.reset(new CLabel(mFont60, "Options"));
	mOptionsLabel->SetHeight(90);
	mOptionsLabel->SetVertAlignment(Alignment::Top);
	mFrame->Add(mOptionsLabel.get());

	//Controls rebinds header
	mControlsLabel.reset(new CLabel(mFont48, "Controls"));
	mFrame->Add(mControlsLabel.get());

	//Sound controls header
	mSoundLabel.reset(new CLabel(mFont48, "Sound"));
	mFrame->Add(mSoundLabel.get());

	//Master volume control
	mMasterVolumePanel.reset(new CPanel());
	mMasterVolumePanel->SetOrientation(Orientation::Horizontal);

	mMasterVolumeLabel.reset(new CLabel(mFont36, "Master Volume "));
	mMasterVolumeLabel->SetHorAlignment(Alignment::Left);
	mMasterVolumeLabel->SetWidth(250);
	mMasterVolumePanel->Add(mMasterVolumeLabel.get());

	mMasterVolumeSpinner.reset(new CSpinner(mFont36, static_cast<int>(gEngine->GetVolume(SoundType::Global))));
	mMasterVolumeSpinner->SetEventHandler(this);
	mMasterVolumeSpinner->SetMinValue(0);
	mMasterVolumeSpinner->SetMaxValue(100);
	mMasterVolumeSpinner->SetIncrement(5);
	mMasterVolumePanel->Add(mMasterVolumeSpinner.get());

	mFrame->Add(mMasterVolumePanel.get());

	//Music volume control
	mMusicVolumePanel.reset(new CPanel());
	mMusicVolumePanel->SetOrientation(Orientation::Horizontal);

	mMusicVolumeLabel.reset(new CLabel(mFont36, "Music Volume "));
	mMusicVolumeLabel->SetHorAlignment(Alignment::Left);
	mMusicVolumeLabel->SetWidth(250);
	mMusicVolumePanel->Add(mMusicVolumeLabel.get());

	mMusicVolumeSpinner.reset(new CSpinner(mFont36, static_cast<int>(gEngine->GetVolume(SoundType::Music))));
	mMusicVolumeSpinner->SetEventHandler(this);
	mMusicVolumeSpinner->SetMinValue(0);
	mMusicVolumeSpinner->SetMaxValue(100);
	mMusicVolumeSpinner->SetIncrement(5);
	mMusicVolumePanel->Add(mMusicVolumeSpinner.get());

	mFrame->Add(mMusicVolumePanel.get());
	
	//SFX volume control
	mSFXVolumePanel.reset(new CPanel());
	mSFXVolumePanel->SetOrientation(Orientation::Horizontal);

	mSFXVolumeLabel.reset(new CLabel(mFont36, "SFX Volume "));
	mSFXVolumeLabel->SetHorAlignment(Alignment::Left);
	mSFXVolumeLabel->SetWidth(250);
	mSFXVolumePanel->Add(mSFXVolumeLabel.get());

	mSFXVolumeSpinner.reset(new CSpinner(mFont36, static_cast<int>(gEngine->GetVolume(SoundType::SFX))));
	mSFXVolumeSpinner->SetEventHandler(this);
	mSFXVolumeSpinner->SetMinValue(0);
	mSFXVolumeSpinner->SetMaxValue(100);
	mSFXVolumeSpinner->SetIncrement(5);
	mSFXVolumePanel->Add(mSFXVolumeSpinner.get());

	mFrame->Add(mSFXVolumePanel.get());

	//Return button
	mBackLabel.reset(new CLabel(mFont36, "Back"));
	mBackLabel->SetEventHandler(this);
	mFrame->Add(mBackLabel.get());
	mFrame->Resize();

	mPopFlag = false;
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
	gEngine->RemoveFont(mFont28);
	gEngine->RemoveFont(mFont24);

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
	if (mouseEvent.GetSource() == mBackLabel.get())
	{
		mBackLabel->SetColor(tle::kRed);
	}
}

//Handles events from the mouse being moved off of a component
void COptionsState::MouseExittedEvent(const CMouseEvent& mouseEvent)
{
	if (mouseEvent.GetSource() == mBackLabel.get())
	{
		mBackLabel->SetColor(tle::kWhite);
	}
}

//Handles events from the a component being clicked on
void COptionsState::MouseClickedEvent(const CMouseEvent& mouseEvent)
{
	if (mouseEvent.GetSource() == mMasterVolumeSpinner.get())
	{
		gEngine->SetVolume(static_cast<float>(mMasterVolumeSpinner->GetValue()), SoundType::Global);
	}
	else if (mouseEvent.GetSource() == mMusicVolumeSpinner.get())
	{
		gEngine->SetVolume(static_cast<float>(mMusicVolumeSpinner->GetValue()), SoundType::Music);
	}
	else if (mouseEvent.GetSource() == mSFXVolumeSpinner.get())
	{
		gEngine->SetVolume(static_cast<float>(mSFXVolumeSpinner->GetValue()), SoundType::SFX);
	}
	else if (mouseEvent.GetSource() == mBackLabel.get())
	{
		mPopFlag = true;
	}
}

//Handles events from the mouse being moved while over a component
void COptionsState::MouseMovedEvent(const CMouseEvent& mouseEvent)
{

}