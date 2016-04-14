#include "GameNetwork.h"
#include "CBulletFactory.h"
GameNetwork GameNetwork::mInstance;

void GameNetwork::Init()
{
	CBulletFactory::Instance()->Init(mPController);

	BulletList* mPBullets;
	BulletList* mEBullets;
	CBulletFactory::Instance()->GetBulletLists(mPBullets, mEBullets);

	mPlayers.Init(mPController);
	mPlayers.ForwardLists(mPBullets, mEBullets);
}
