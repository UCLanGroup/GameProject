// Last updated: 04.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CIntroState.h"
#include "CPlayState.h"

CIntroState CIntroState::mIntroState;

void CIntroState::Init()
{
	// Menu screen goes here
	mBackground = gEngine->CreateSprite(INTROBG, 200.0f, 200.0f, 0.0f);
}

void CIntroState::Cleanup() 
{
	gEngine->RemoveSprite(mBackground);
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

	// GOOD ANIMATION TEMP
	mMove += mDelta;

	if (mMove > 0.0001f)
	{
		if (mMoveRight)
		{
	
			mBackground->MoveX(150.0f * mDelta);
			if (mBackground->GetX() > 800.0f)
			{
				mMoveRight = !mMoveRight;
			}
		}
		else
		{
			mBackground->MoveX(150.0f * -mDelta);
			if (mBackground->GetX() < 200.0f)
			{
				mMoveRight = !mMoveRight;
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