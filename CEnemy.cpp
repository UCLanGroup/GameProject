#include "CEnemy.h"
#include <algorithm>

CEnemy::CEnemy(Path* path, Vector3& offset)
{
	//Model
	mMesh = gEngine->LoadMesh(DEFAULT_ENEMY_MESH);
	mModel = mMesh->CreateModel(offset.GetX(), offset.GetY(), offset.GetZ());

	//Pathing
	mpPath = path;
	mOffset = offset;
	mPathPos = 0;
	mMoveTimer = 0.0f;
	mFinished = false;

	//Default
	mHealth = 1;
	mSpeed = 1.0f;
	mValue = 10;
}

//Sets

void CEnemy::SetHealth(int health)
{
	mHealth = health;
}

void CEnemy::SetSpeed(float speed)
{
	mSpeed = speed;
}

void CEnemy::AddWeapon(CWeapon w) //Perposely use copy constructor
{
	mWeapons.push_back(w);
}

void CEnemy::SetValue(int value)
{
	mValue = value;
}

//Gets

int CEnemy::GetHealth()
{
	return mHealth;
}

float CEnemy::GetSpeed()
{
	return mSpeed;
}

std::vector<CWeapon>* CEnemy::GetWeapons()
{
	return &mWeapons;
}

int CEnemy::GetValue()
{
	return mValue;
}

bool CEnemy::IsFinished()
{
	return mFinished;
}

//Updates

void CEnemy::Move(float delta)
{
	mMoveTimer += delta * mSpeed;
	if (mMoveTimer > 1.0f)
	{
		mMoveTimer -= 1.0f;
		mPathPos++;
	}
	if (mPathPos < mpPath->size() - 2)
	{
		//spline
		int highestPoint = mpPath->size() - 1;
		Vector3 p1 = (*mpPath)[min(highestPoint, mPathPos)];
		Vector3 p2 = (*mpPath)[min(highestPoint, mPathPos + 1)];
		Vector3 p3 = (*mpPath)[min(highestPoint, mPathPos + 2)];
		Vector3 p4 = (*mpPath)[min(highestPoint, mPathPos + 3)];

		Vector3 A = p4 - p1 + (p2 * 3.0f) - (p3 * 3.0f);
		Vector3 B = (p1 * 2.0f) - (p2 * 5.0f) + (p3 * 4) - p4;
		Vector3 C = p3 - p1;
		Vector3 D = p2 * 2;

		Vector3 L = ((A * (mMoveTimer * mMoveTimer * mMoveTimer)) + (B * (mMoveTimer * mMoveTimer)) + (C * mMoveTimer) + D) * 0.5f;
		L = L + mOffset;

		mModel->SetPosition(L.GetX(), L.GetY(), L.GetZ());
	}
	else
	{
		mFinished = true;
	}
}

void CEnemy::Update(float delta)
{
	Move(delta);
}

//Inherited from ICollidable

Vector3 CEnemy::GetCenterPoint()
{
	if (mModel == 0)
	{
		return Vector3();
	}
	return Vector3(mModel->GetX(), mModel->GetY(), mModel->GetZ());
}

bool CEnemy::GetMeshAndMatrix(tle::IMesh* mesh, float* matrix)
{
	if (mMesh != 0 && mModel != 0)
	{
		mesh = mMesh;
		mModel->GetMatrix(matrix);
		return true;
	}
	return false;
}

CEnemy::~CEnemy()
{
	if (mMesh != 0)
	{
		mMesh->RemoveModel(mModel);
	}
}