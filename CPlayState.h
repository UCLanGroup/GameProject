#pragma once
// Last updated: 04.02.16

#include <TL-Engine.h>

#include "CGameState.h"
#include "CPlayer.h"
#include "CProjectile.h"
#include "CEnemyManager.h"
#include "CExplosionPool.h"

using namespace tle;

class CPlayState : public CGameState
{
private:
	static CPlayState mPlayState;

	ICamera* mCam;
	ISprite* mUI;
	IMesh* mFloorMesh;
	IModel* mFloor;

	CPlayer mPlayer1;

	unique_ptr<CEnemyManager> mEnemyManager;

	CExplosionPool* mExplosions;

	vector_ptr<CProjectile> mPBullets; //Player Projectiles
	vector_ptr<CProjectile> mEBullets; //Enemy Projectiles

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

	inline CPlayer* GetPlayer1() { return &mPlayer1; }
	//inline CPlayer* GetPlayer2() { return &mPlayer2; }

	static CPlayState* Instance()
	{
		return &mPlayState;
	}

protected: CPlayState() {}
};