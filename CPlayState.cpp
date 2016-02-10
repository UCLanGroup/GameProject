// Last updated: 04.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CPlayState.h"

CPlayState CPlayState::mPlayState;

void CPlayState::Init()
{
	mFloorMesh = gEngine->LoadMesh(GROUNDMESH);
	mFloor = mFloorMesh->CreateModel(-6.0f, -10.0f, -5.5f);

	mUI = gEngine->CreateSprite(UI, 0.0f, 0.0f, 0.0f);

	mCam = gEngine->CreateCamera(kManual, 0.0f, 100.0f, 0.0f);
	mCam->RotateLocalX(90.0f);

	mPlayer1.Init();
	mPlayer1.model->Scale(1.0f);
	float x = mPlayer1.model->GetX();
}

void CPlayState::Cleanup()
{
	gEngine->RemoveSprite(mUI);
	gEngine->RemoveCamera(mCam);
	mFloorMesh->RemoveModel(mFloor);
	gEngine->RemoveMesh(mFloorMesh);
}

void CPlayState::Pause() {}

void CPlayState::Resume() {}

void CPlayState::HandleEvents(CGameStateHandler * game)
{
	// Keypresses go here


	if (gEngine->KeyHit(KEY_EXIT))
	{
		game->Quit();
	}
}

void CPlayState::Update(CGameStateHandler * game)
{
	mDelta = gEngine->Timer();

	// Animations go here

	mPlayer1.Move(mDelta);

}

void CPlayState::Draw(CGameStateHandler * game)
{
	// Draw the scene
	gEngine->DrawScene();
}
