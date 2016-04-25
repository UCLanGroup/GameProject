#pragma once
// Last updated: 04.02.16

#include <IEngine.h>
#include <SFML/audio.hpp>


#include "CGameState.h"
#include "CPlayer.h"
#include "CProjectile.h"
#include "CEnemyManager.h"
#include "CExplosionPool.h"
#include "CClouds.h"
#include "CCheatManager.h"

using namespace tle;

class CPlayState : public CGameState
{
private:

	const float kCheatDisplayTime = 2.0f;

	const float kStartBarPosX = 90;
	const float kStartBarPosY = 936;
	const float kBarSpeed = 100.0f;
	const float kBarSize = 200.0f;
	const float kFloorSize = 1999.0f;
	const float kFloorStart = 500.0f;
	const float kFloorSpeed = -500.0f;
	const int kFloorAmount = 2;

	const float kFloorResetAmount = -kFloorSize + 1.0f;

	static CPlayState mPlayState;

	ICamera* mCam;
	ISprite* mUI;
	ISprite* mUI2;
	IMesh* mFloorMesh;
	vector<IModel*> mFloor;
	unique_ptr<CClouds> mClouds;

	IMusic* mMusic = nullptr;

	CCheatManager mCheatManager;
	CCheatManager::SCheat* mRecentCheat;
	
	float mRecentCheatDisplay = 0.0f;

	vector<ISprite*> mLifeSprites;
	ISprite* mpHealthBar;
	ISprite* mpShieldBar;

	IFont* mFont;

	CPlayer mPlayer1;
	//CPlayer mPlayer2;
	vector<CPlayer*> mPlayerList; //Used to pass a list of both players to enemies to keep track of

	unique_ptr<CEnemyManager> mEnemyManager;

	CExplosionPool* mExplosions;

	BulletList mPBullets; //Player Projectiles
	BulletList mEBullets; //Enemy Projectiles

	float mDelta = 0.0f;		// Delta time (to render previous frame)

public:
	// Setup and destroy state
	void Init();
	void Cleanup();

	// Temporarily transition to another state
	void Pause();
	void Resume();

	// Game loop actions
	void HandleEvents(CGameStateHandler* game);
	void Update(CGameStateHandler* game);
	void Draw(CGameStateHandler* game);

	void DrawText();
	void AnimateHealth(float delta);
	void AnimateShield(float delta);

	inline CPlayer* GetPlayer1() { return &mPlayer1; } //Don't call this in enemies, use the playerList passed to them
	//inline CPlayer* GetPlayer2() { return &mPlayer2; }

	static CPlayState* Instance()
	{
		return &mPlayState;
	}

protected: CPlayState() {}
};