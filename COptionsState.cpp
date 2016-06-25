#include "Globals.h"
#include "CGameStateHandler.h"
#include "COptionsState.h"
#include "CMouseEvent.h"
#include <iostream>

COptionsState COptionsState::mOptionsState;

// Setup and destroy state
void COptionsState::Init()
{
	//Create fonts
	mFont60 = gEngine->LoadFont("Rockwell", 60U);
	mFont48 = gEngine->LoadFont("Rockwell", 48U);
	mFont36 = gEngine->LoadFont("Rockwell", 36U);
	mFont28 = gEngine->LoadFont("Rockwell", 28U);
	mFont24 = gEngine->LoadFont("Rockwell", 24U);

	//Create Sounds
	mMouseOverSound = gEngine->CreateSound(SOUND_MOUSE_OVER);
	mMouseOverSound->SetType(SoundType::Interface);
	mMouseClickSound = gEngine->CreateSound(SOUND_MOUSE_CLICK);
	mMouseClickSound->SetType(SoundType::Interface);

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

	//Fire key rebind
	mFireKeyPanel.reset(new CPanel());
	mFireKeyPanel->SetOrientation(Orientation::Horizontal);

	mFireKeyLabel.reset(new CLabel(mFont36, "Fire Key "));
	mFireKeyLabel->SetHorAlignment(Alignment::Left);
	mFireKeyLabel->SetWidth(200);
	mFireKeyPanel->Add(mFireKeyLabel.get());

	mFireKeyButton.reset(new CButton(mFont36, KeyBinds::ToString(KeyBinds::Fire)));
	mFireKeyButton->SetSounds(mMouseOverSound, mMouseClickSound);
	mFireKeyButton->SetHorAlignment(Alignment::Left);;
	mFireKeyButton->SetWidth(200);
	mFireKeyButton->SetEventHandler(this);
	mFireKeyPanel->Add(mFireKeyButton.get());

	mFrame->Add(mFireKeyPanel.get());

	//Up key rebind
	mUpKeyPanel.reset(new CPanel());
	mUpKeyPanel->SetOrientation(Orientation::Horizontal);

	mUpKeyLabel.reset(new CLabel(mFont36, "Up Key "));
	mUpKeyLabel->SetHorAlignment(Alignment::Left);
	mUpKeyLabel->SetWidth(200);
	mUpKeyPanel->Add(mUpKeyLabel.get());

	mUpKeyButton.reset(new CButton(mFont36, KeyBinds::ToString(KeyBinds::Up)));
	mUpKeyButton->SetSounds(mMouseOverSound, mMouseClickSound);
	mUpKeyButton->SetHorAlignment(Alignment::Left);;
	mUpKeyButton->SetWidth(200);
	mUpKeyButton->SetEventHandler(this);
	mUpKeyPanel->Add(mUpKeyButton.get());

	mFrame->Add(mUpKeyPanel.get());

	//Down key rebind
	mDownKeyPanel.reset(new CPanel());
	mDownKeyPanel->SetOrientation(Orientation::Horizontal);

	mDownKeyLabel.reset(new CLabel(mFont36, "Down Key "));
	mDownKeyLabel->SetHorAlignment(Alignment::Left);
	mDownKeyLabel->SetWidth(200);
	mDownKeyPanel->Add(mDownKeyLabel.get());

	mDownKeyButton.reset(new CButton(mFont36, KeyBinds::ToString(KeyBinds::Down)));
	mDownKeyButton->SetSounds(mMouseOverSound, mMouseClickSound);
	mDownKeyButton->SetHorAlignment(Alignment::Left);;
	mDownKeyButton->SetWidth(200);
	mDownKeyButton->SetEventHandler(this);
	mDownKeyPanel->Add(mDownKeyButton.get());

	mFrame->Add(mDownKeyPanel.get());

	//Left key rebind
	mLeftKeyPanel.reset(new CPanel());
	mLeftKeyPanel->SetOrientation(Orientation::Horizontal);

	mLeftKeyLabel.reset(new CLabel(mFont36, "Left Key "));
	mLeftKeyLabel->SetHorAlignment(Alignment::Left);
	mLeftKeyLabel->SetWidth(200);
	mLeftKeyPanel->Add(mLeftKeyLabel.get());

	mLeftKeyButton.reset(new CButton(mFont36, KeyBinds::ToString(KeyBinds::Left)));
	mLeftKeyButton->SetSounds(mMouseOverSound, mMouseClickSound);
	mLeftKeyButton->SetHorAlignment(Alignment::Left);;
	mLeftKeyButton->SetWidth(200);
	mLeftKeyButton->SetEventHandler(this);
	mLeftKeyPanel->Add(mLeftKeyButton.get());

	mFrame->Add(mLeftKeyPanel.get());

	//Right key rebind
	mRightKeyPanel.reset(new CPanel());
	mRightKeyPanel->SetOrientation(Orientation::Horizontal);

	mRightKeyLabel.reset(new CLabel(mFont36, "Right Key "));
	mRightKeyLabel->SetHorAlignment(Alignment::Left);
	mRightKeyLabel->SetWidth(200);
	mRightKeyPanel->Add(mRightKeyLabel.get());

	mRightKeyButton.reset(new CButton(mFont36, KeyBinds::ToString(KeyBinds::Right)));
	mRightKeyButton->SetSounds(mMouseOverSound, mMouseClickSound);
	mRightKeyButton->SetHorAlignment(Alignment::Left);;
	mRightKeyButton->SetWidth(200);
	mRightKeyButton->SetEventHandler(this);
	mRightKeyPanel->Add(mRightKeyButton.get());

	mFrame->Add(mRightKeyPanel.get());

	//Sound controls header
	mSoundLabel.reset(new CLabel(mFont48, "Sound"));
	mFrame->Add(mSoundLabel.get());

	//Master volume control
	mMasterVolumePanel.reset(new CPanel());
	mMasterVolumePanel->SetOrientation(Orientation::Horizontal);

	mMasterVolumeLabel.reset(new CLabel(mFont36, "Master Volume "));
	mMasterVolumeLabel->SetHorAlignment(Alignment::Left);
	mMasterVolumeLabel->SetWidth(280);
	mMasterVolumePanel->Add(mMasterVolumeLabel.get());

	mMasterVolumeSpinner.reset(new CSpinner(mFont36, static_cast<int>(gEngine->GetVolume(SoundType::Global))));
	mMasterVolumeSpinner->SetSounds(mMouseOverSound, mMouseClickSound);
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
	mMusicVolumeLabel->SetWidth(280);
	mMusicVolumePanel->Add(mMusicVolumeLabel.get());

	mMusicVolumeSpinner.reset(new CSpinner(mFont36, static_cast<int>(gEngine->GetVolume(SoundType::Music))));
	mMusicVolumeSpinner->SetSounds(mMouseOverSound, mMouseClickSound);
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
	mSFXVolumeLabel->SetWidth(280);
	mSFXVolumePanel->Add(mSFXVolumeLabel.get());

	mSFXVolumeSpinner.reset(new CSpinner(mFont36, static_cast<int>(gEngine->GetVolume(SoundType::SFX))));
	mSFXVolumeSpinner->SetSounds(mMouseOverSound, mMouseClickSound);
	mSFXVolumeSpinner->SetEventHandler(this);
	mSFXVolumeSpinner->SetMinValue(0);
	mSFXVolumeSpinner->SetMaxValue(100);
	mSFXVolumeSpinner->SetIncrement(5);
	mSFXVolumePanel->Add(mSFXVolumeSpinner.get());

	mFrame->Add(mSFXVolumePanel.get());

	//Interface volume control
	mInterfaceVolumePanel.reset(new CPanel());
	mInterfaceVolumePanel->SetOrientation(Orientation::Horizontal);

	mInterfaceVolumeLabel.reset(new CLabel(mFont36, "Interface Volume "));
	mInterfaceVolumeLabel->SetHorAlignment(Alignment::Left);
	mInterfaceVolumeLabel->SetWidth(280);
	mInterfaceVolumePanel->Add(mInterfaceVolumeLabel.get());

	mInterfaceVolumeSpinner.reset(new CSpinner(mFont36, static_cast<int>(gEngine->GetVolume(SoundType::Interface))));
	mInterfaceVolumeSpinner->SetSounds(mMouseOverSound, mMouseClickSound);
	mInterfaceVolumeSpinner->SetEventHandler(this);
	mInterfaceVolumeSpinner->SetMinValue(0);
	mInterfaceVolumeSpinner->SetMaxValue(100);
	mInterfaceVolumeSpinner->SetIncrement(5);
	mInterfaceVolumePanel->Add(mInterfaceVolumeSpinner.get());

	mFrame->Add(mInterfaceVolumePanel.get());

	//Return button
	mBackButton.reset(new CButton(mFont36, "Back"));
	mBackButton->SetSounds(mMouseOverSound, mMouseClickSound);
	mBackButton->SetEventHandler(this);
	mFrame->Add(mBackButton.get());
	mFrame->Resize();

	mPopFlag = false;
}

void COptionsState::Cleanup()
{
	mFrame.reset();
	mOptionsLabel.reset();
	mControlsLabel.reset();
	mSoundLabel.reset();
	mBackButton.reset();

	//Remove fonts
	gEngine->RemoveFont(mFont60);
	gEngine->RemoveFont(mFont48);
	gEngine->RemoveFont(mFont36);
	gEngine->RemoveFont(mFont28);
	gEngine->RemoveFont(mFont24);

	//Removes Sounds
	gEngine->RemoveSound(mMouseOverSound);
	gEngine->RemoveSound(mMouseClickSound);
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
	if (mFireKeyFlag || mUpKeyFlag || mDownKeyFlag || mLeftKeyFlag || mRightKeyFlag)
	{
		if (gEngine->AnyKeyHit())
		{
			EKeyCode keyHit = GetKeyHit();

			if (KeyBinds::IsKeyBindable(keyHit))
			{
				if (mFireKeyFlag)
				{
					if (KeyBinds::Fire == keyHit || !KeyBinds::IsKeyBinded(keyHit))
					{
						KeyBinds::Fire = keyHit;
						mFireKeyButton->SetText(KeyBinds::ToString(keyHit));
						mFireKeyFlag = false;
						mFrame->CheckEvent(CMouseEvent(0, CMouseEvent::Mouse_Moved, gEngine->GetMouseX(), gEngine->GetMouseY()));
					}
				}
				else if (mUpKeyFlag)
				{
					if (KeyBinds::Up == keyHit || !KeyBinds::IsKeyBinded(keyHit))
					{
						KeyBinds::Up = keyHit;
						mUpKeyButton->SetText(KeyBinds::ToString(keyHit));
						mUpKeyFlag = false;
						mFrame->CheckEvent(CMouseEvent(0, CMouseEvent::Mouse_Moved, gEngine->GetMouseX(), gEngine->GetMouseY()));
					}
				}
				else if (mDownKeyFlag)
				{
					if (KeyBinds::Down == keyHit || !KeyBinds::IsKeyBinded(keyHit))
					{
						KeyBinds::Down = keyHit;
						mDownKeyButton->SetText(KeyBinds::ToString(keyHit));
						mDownKeyFlag = false;
						mFrame->CheckEvent(CMouseEvent(0, CMouseEvent::Mouse_Moved, gEngine->GetMouseX(), gEngine->GetMouseY()));
					}
				}
				else if (mRightKeyFlag)
				{
					if (KeyBinds::Right == keyHit || !KeyBinds::IsKeyBinded(keyHit))
					{
						KeyBinds::Right = keyHit;
						mRightKeyButton->SetText(KeyBinds::ToString(keyHit));
						mRightKeyFlag = false;
						mFrame->CheckEvent(CMouseEvent(0, CMouseEvent::Mouse_Moved, gEngine->GetMouseX(), gEngine->GetMouseY()));
					}
				}
				else if (mLeftKeyFlag)
				{
					if (KeyBinds::Left == keyHit || !KeyBinds::IsKeyBinded(keyHit))
					{
						KeyBinds::Left = keyHit;
						mLeftKeyButton->SetText(KeyBinds::ToString(keyHit));
						mLeftKeyFlag = false;
						mFrame->CheckEvent(CMouseEvent(0, CMouseEvent::Mouse_Moved, gEngine->GetMouseX(), gEngine->GetMouseY()));
					}
				}
			}
		}
	}
	else
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

		if (gEngine->KeyHit(KEY_EXIT) || mPopFlag)
		{
			//Pause for half a second while the intro sound plays
			float timer = 0.0f;
			while (timer < 0.5f)
			{
				timer += gEngine->Timer();
			}

			game->PopState();
		}
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

}

//Handles events from the mouse being moved off of a component
void COptionsState::MouseExittedEvent(const CMouseEvent& mouseEvent)
{

}

//Handles events from the a component being clicked on
void COptionsState::MouseClickedEvent(const CMouseEvent& mouseEvent)
{
	if (mouseEvent.GetSource() == mFireKeyButton.get())
	{
		mFireKeyButton->SetText("");
		mFireKeyFlag = true;
	}
	else if (mouseEvent.GetSource() == mUpKeyButton.get())
	{
		mUpKeyButton->SetText("");
		mUpKeyFlag = true;
	}
	else if (mouseEvent.GetSource() == mDownKeyButton.get())
	{
		mDownKeyButton->SetText("");
		mDownKeyFlag = true;
	}
	else if (mouseEvent.GetSource() == mLeftKeyButton.get())
	{
		mLeftKeyButton->SetText("");
		mLeftKeyFlag = true;
	}
	else if (mouseEvent.GetSource() == mRightKeyButton.get())
	{
		mRightKeyButton->SetText("");
		mRightKeyFlag = true;
	}
	else if (mouseEvent.GetSource() == mMasterVolumeSpinner.get())
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
	else if (mouseEvent.GetSource() == mInterfaceVolumeSpinner.get())
	{
		gEngine->SetVolume(static_cast<float>(mInterfaceVolumeSpinner->GetValue()), SoundType::Interface);
	}
	else if (mouseEvent.GetSource() == mBackButton.get())
	{
		mPopFlag = true;
	}
}

//Handles events from the mouse being moved while over a component
void COptionsState::MouseMovedEvent(const CMouseEvent& mouseEvent)
{

}

EKeyCode GetKeyHit()
{
	for (int i = 0; i < 256; ++i)
	{
		if(gEngine->KeyHit(static_cast<EKeyCode>(i)))
		{
			return static_cast<EKeyCode>(i);
		}
	}
	return static_cast<EKeyCode>(0);
}