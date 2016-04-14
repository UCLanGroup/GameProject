#pragma once
#include "CBaseProjectile.h"
#include "NetObject.h"
#include "CNetVarBase.h"
#include "CNetVarVector.h"
#include <list>

// Description:	Moves towards target haphazardly and can be shot down.
//
// Movement:	Constantly turns towards target in the same direction
//				for a set period of time causing it to wiggle towards
//				the target
//
// Collision:	Player projectiles

class CMissile : public CBaseProjectile
{
private:
	IEntity* mTarget = 0;
	IParticleEmitter* mEmitter = 0;
	bool mClockwise = false;
	float mTimer = 0.0f;

	std::list<unique_ptr<CBaseProjectile>>* mpPlayerBullets = 0;

public:

	CMissile();

	void Init();
	void Cleanup();

	virtual void Update(float delta);
	virtual void CheckCollision();

	void SetTarget(IEntity* target);
	void SetLists(std::list<unique_ptr<CBaseProjectile>>* playerBullets);

	IEntity* GetTarget();
	bool IsClockwise();

	virtual void Reset();

	virtual ~CMissile();
};