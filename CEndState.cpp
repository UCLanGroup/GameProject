#include "Globals.h"
#include "CGameStateHandler.h"
#include "CEndState.h"
#include "CIntroState.h"
#include "COptionsState.h"
#include "CMouseEvent.h"
#include "CExplosionPool.h"
#include <iostream>

CEndState CEndState::mEndState;

// Setup and destroy state
void CEndState::Init()
{
	//Disable auto updating of animations and particle emitters
	gEngine->PauseAutoUpdates();

	//Create fonts
	mFont90 = gEngine->LoadFont("Rockwell", 90U);
	mFont60 = gEngine->LoadFont("Rockwell", 60U);

	mMouseOverSound = gEngine->CreateSound(SOUND_MOUSE_OVER);
	mMouseOverSound->SetType(SoundType::Interface);
	mMouseClickSound = gEngine->CreateSound(SOUND_MOUSE_CLICK);
	mMouseClickSound->SetType(SoundType::Interface);

	//Create UI container
	mFrame.reset(new CPanel());
	mFrame->SetSize(gEngine->GetWidth(), gEngine->GetHeight());

	mMessageLabel.reset(new CLabel(mFont90, ""));
	mMessageLabel->SetHeight(90);
	mMessageLabel->SetVertAlignment(Alignment::Top);
	mFrame->Add(mMessageLabel.get());

	mScoreLabel.reset(new CLabel(mFont60, ""));
	mScoreLabel->SetHeight(40);
	mFrame->Add(mScoreLabel.get());
	mFrame->Resize();

	mTextTimer = 0.0f;
}

void CEndState::Cleanup()
{
	mFrame.reset();
	mMessageLabel.reset();
	mScoreLabel.reset();

	//Remove fonts
	gEngine->RemoveFont(mFont90);
	gEngine->RemoveFont(mFont60);

	//Removes Sounds
	gEngine->RemoveSound(mMouseOverSound);
	gEngine->RemoveSound(mMouseClickSound);

	//Re-enable auto updating of animations and particle emitters
	gEngine->UnpauseAutoUpdates();
}

// Temporarily transition to another state
void CEndState::Pause()
{

}

void CEndState::Resume()
{

}

// Game loop actions

//Handles the events from the engine
void CEndState::HandleEvents(CGameStateHandler* game)
{
	if (gEngine->KeyHit(Key_Space))
	{
		game->ChangeState(CIntroState::Instance());
	}
	if (gEngine->KeyHit(Key_Escape))
	{
		game->Quit();
	}
}

//Updates any game logic
void CEndState::Update(CGameStateHandler* game)
{
	mDelta = gEngine->Timer();
	CExplosionPool::Instance()->Update(mDelta);

	mTextTimer += mDelta;

	if (mTextTimer > 0.2f)
	{
		mTextTimer -= 0.2f;
		if (mMessageBuffer.size())
		{
			std::string s = mMessageLabel->GetText();
			char c = mMessageBuffer.front();
			s.push_back(c);
			mMessageBuffer.erase(mMessageBuffer.begin());
			mMessageLabel->SetText(s);
			if(c == ' ') mTextTimer += 0.2f;
		}
		else if (mScoreBuffer.size())
		{
			std::string s = mScoreLabel->GetText();
			char c = mScoreBuffer.front();
			s.push_back(c);
			mScoreBuffer.erase(mScoreBuffer.begin());
			mScoreLabel->SetText(s);
			if (c == ' ') mTextTimer += 0.2f;
		}
		mFrame->Resize();
	}
}

//Draws any components that need to be explicitly draw each frame
void CEndState::Draw(CGameStateHandler* game)
{
	mFrame->Draw();
	gEngine->DrawScene();
}



void CEndState::SetEndState(bool win, int score)
{
	mWinner = win;
	if (win)
	{
		mMessageBuffer = "You Win!";
		mScoreBuffer = "Final Score: " + std::to_string(score);

		mMessageLabel->SetText("");
		mMessageLabel->SetColor(tle::kWhite);
		mScoreLabel->SetText("");
	}
	else
	{
		mMessageBuffer = "You Have Died";
		mScoreBuffer = "Final Score: " + std::to_string(score);

		mMessageLabel->SetText("");
		mMessageLabel->SetColor(tle::kRed);
		mScoreLabel->SetText("");
	}
	mFrame->Resize();
}

//Handles events from the mouse being moved over a component
void CEndState::MouseEnteredEvent(const CMouseEvent& mouseEvent)
{
}

//Handles events from the mouse being moved off of a component
void CEndState::MouseExittedEvent(const CMouseEvent& mouseEvent)
{
}

//Handles events from the a component being clicked on
void CEndState::MouseClickedEvent(const CMouseEvent& mouseEvent)
{
}

//Handles events from the mouse being moved while over a component
void CEndState::MouseMovedEvent(const CMouseEvent& mouseEvent)
{

}