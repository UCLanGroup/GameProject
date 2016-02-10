// Last updated: 04.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CIntroState.h"
#include "CPlayState.h"

CIntroState CIntroState::mIntroState;

void CIntroState::Init()
{
	// Menu screen goes here
	mBackground = gEngine->CreateSprite(INTROBG, 0.0f, 0.0f, 1.0f);
	mText = gEngine->CreateSprite(INTROSTART, 0.0f, 0.0f, 0.9f);
}

void CIntroState::Cleanup() 
{
	gEngine->RemoveSprite(mBackground);
	gEngine->RemoveSprite(mText);
}


void CIntroState::Pause() {}

void CIntroState::Resume() {}


void CIntroState::HandleEvents(CGameStateHandler* game)
{
	// Keypresses go here
	if (gEngine->KeyHit(KEY_EXIT))
	{
		game->Quit();
	}

	if (gEngine->KeyHit(KEY_START))
	{
		game->ChangeState(CPlayState::Instance());
	}
}

void CIntroState::Update(CGameStateHandler* game)
{
	mDelta = gEngine->Timer();

	// Animations go here
	mMove += mDelta;

	// Start text
	if (mMove > 0.0001f)
	{
		if (mMoveUp)
		{
			mText->MoveY(15.0f * -mDelta);
			if (mText->GetY() < -5.0f)
			{
				mMoveUp = !mMoveUp;
			}
		}
		else
		{
			mText->MoveY(15.0f * mDelta);
			if (mText->GetY() > 5.0f)
			{
				mMoveUp = !mMoveUp;
			}
		}
		mMove = 0.0f;
	}

}

void CIntroState::Draw(CGameStateHandler* game)
{
	// Draw the scene
	gEngine->DrawScene();
}