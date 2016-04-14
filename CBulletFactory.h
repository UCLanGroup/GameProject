#pragma once
#include "NETTIK_Networking.hpp"
#include <unordered_map>
#include "CBullet.h"
#include "CWeapon.h"
#include "MessageQueue.h"
using std::placeholders::_1;

class CBulletFactory
{
public:
	enum EBulletOwnership
	{
		kBulletOwnershipPlayer,
		kBulletOwnershipEnemy
	};

private:

	BulletList mPBullets; //Player Projectiles
	BulletList mEBullets; //Enemy Projectiles

	NETTIK::IController* mPController = nullptr;
	VirtualInstance* mPGame = nullptr;
	IEntityManager*  mPManager = nullptr;

	void Add(CBullet* projectile, EBulletOwnership owner);

	void Remove(CBullet* projectile, EBulletOwnership owner);

	static CBulletFactory mInstance;

public:

	BulletList* GetPlayerBullets();
	BulletList* GetEnemyBullets();
	void GetBulletLists(BulletList*& player, BulletList*& enemy);

	static CBulletFactory* Instance();

	//! Invoked when: Client constructs new player.
	void NewBullet(CBullet* bullet);

	//! Invoked when: Client destructs new player.
	void RemoveBullet(CBullet* bullet);

	//! Sets up the controller pointer reference.
	void Init(NETTIK::IController* pController);

};


inline void CBulletFactory::GetBulletLists(BulletList*& player, BulletList*& enemy)
{
	player = &mPBullets;
	enemy = &mEBullets;
}

inline BulletList* CBulletFactory::GetPlayerBullets()
{
	return &mPBullets;
}

inline BulletList* CBulletFactory::GetEnemyBullets()
{
	return &mEBullets;
}

inline CBulletFactory* CBulletFactory::Instance()
{
	return &mInstance;
}
