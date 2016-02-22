// Last updated: 21.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CIntroState.h"
#include "CPlayState.h"

CIntroState CIntroState::mIntroState;

void CIntroState::Init()
{
	// Menu screen goes here
	mBackground = gEngine->CreateSprite(INTRO_BG, 0.0f, 0.0f, 1.0f);
	mText = gEngine->CreateSprite(INTRO_START, 0.0f, 300.0f, 0.9f);

	mFloorMesh = gEngine->LoadMesh(GROUND_MESH);
	mFloor = mFloorMesh->CreateModel(-6.0f, -10.0f, -5.5f);

	mPlaneMesh = gEngine->LoadMesh(PLAYER_MESH);
	mPlane = mPlaneMesh->CreateModel(0.0f, 10.0f, 150.0f);
	mPlane->Scale(6.0f);
	mPlane->RotateY(180.0f);

	mCam = gEngine->CreateCamera(kManual, 0.0f, 40.0f, 0.0f);
	mCam->RotateLocalX(10.0f);
}

void CIntroState::Cleanup() 
{
	//gEngine->RemoveSprite(mBackground);
	gEngine->RemoveSprite(mText);
	gEngine->RemoveCamera(mCam);
	mFloorMesh->RemoveModel(mFloor);
	gEngine->RemoveMesh(mFloorMesh);
	mPlaneMesh->RemoveModel(mPlane);
	gEngine->RemoveMesh(mPlaneMesh);
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
		mPlane->RotateY(15.0f * mDelta);

		if (mMoveUp)
		{
			mText->MoveY(15.0f * -mDelta);
			if (mText->GetY() < 295.0f)
			{
				mMoveUp = !mMoveUp;
			}
		}
		else
		{
			mText->MoveY(15.0f * mDelta);
			if (mText->GetY() > 305.0f)
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