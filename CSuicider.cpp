#define _USE_MATH_DEFINES
#include "CSuicider.h"
#include "CPlayer.h"
#include <iostream>

const float kRotateSpeed = 110.0f;

CSuicider::CSuicider(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets) : CEnemy(players, playerBullets, enemyBullets)
{
	SetMesh(MIG142_ENEMY_MESH);

	//Ensure model is reset in the case it reuses a cached model
	mModel->ResetScale();
	mModel->ResetOrientation();

	mModel->RotateY((*mpPlayers)[0]->GetRotation());

	SetHealth(10);
	SetRadius(10.0f);
	SetValue(30);
	SetSpeed(50.0f);
}

void CSuicider::Move(float delta)
{
}

void CSuicider::Update(float delta)
{
	RotateTowards((*mpPlayers)[0]->GetCenterPoint(), delta * kRotateSpeed);
	mModel->MoveLocalZ(delta * GetSpeed());
}

void CSuicider::Reset()
{

}