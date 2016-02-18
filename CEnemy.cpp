#define _USE_MATH_DEFINES
#include "CEnemy.h"
#include "CMeshCache.h"
#include <algorithm>

const int kHealth = 1;
const float kSpeed = 1.0f;
const int kValue = 10;
const float kRadius = 5.0f;

CEnemy::CEnemy()
{
	//Model
	mMesh = CMeshCache::GetInstance()->LoadMesh(DEFAULT_ENEMY_MESH);
	mModel = mMesh->CreateModel(OFF_SCREEN_X, OFF_SCREEN_Y, OFF_SCREEN_Z);
	mRadius = kRadius;

	//All other stats are reset
	Reset();
}

CEnemy::CEnemy(Path* path, Vector3& offset) : CEnemy()
{
	//Pathing
	mpPath = path;
	mOffset = offset;
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
	if (mPathPos < static_cast<int>(mpPath->size() - 2))
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

		Vector3 newPos = ((A * (mMoveTimer * mMoveTimer * mMoveTimer)) + (B * (mMoveTimer * mMoveTimer)) + (C * mMoveTimer) + D) * 0.5f;
		newPos = newPos + mOffset;

		/*
		//Attempt using dot product to rotate towards new position

		Vector3 oldPos(mModel->GetX(), mModel->GetLocalY(), mModel->GetZ());
		float matrix[16];
		mModel->GetMatrix(&(matrix[0]));
		Vector3 forward(matrix[0], matrix[1], matrix[2]); //Get the direction the model is facing
		Vector3 direction = newPos - oldPos;

		float dot = (forward * direction) / (forward.Length() * direction.Length());
		float angle = acosf(dot);

		if (angle > 0.01f)
		{
			if (dot > 0.0f)
			{
				mModel->RotateLocalY(angle);
			}
			else
			{
				mModel->RotateLocalY(-angle);
			}
		}*/

		//Calculate bearing from north
		float xDif = newPos.GetX() - mModel->GetX();
		float zDif = newPos.GetZ() - mModel->GetZ();
		float angle = 90.0f - atan2f(zDif, xDif) * (180.0f / static_cast<float>(M_PI));
		
		//Reset orientation then apply new angle
		mModel->ResetOrientation();
		mModel->RotateY(angle);

		mModel->SetPosition(newPos.GetX(), newPos.GetY(), newPos.GetZ());
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

void CEnemy::TakeDamage(int damage)
{
	mHealth -= damage;
	if (mHealth <= 1)
	{
		mFinished = true;
	}
}

//Sets

void CEnemy::SetMesh(string meshFile)
{
	SetMesh( CMeshCache::GetInstance()->LoadMesh(meshFile) );
}

void CEnemy::SetMesh(IMesh* mesh)
{
	if (mMesh != mesh && mesh != 0)
	{
		if (mModel != 0)
		{
			mMesh->RemoveModel(mModel);
		}
		mMesh = mesh;
		mModel = mMesh->CreateModel();
	}
}

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

void CEnemy::SetPath(Path* path, Vector3& offset)
{
	mpPath = path;
	mOffset = offset;
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

//Inherited from IResource

void CEnemy::Reset()
{
	//Pathing
	mPathPos = 0;
	mMoveTimer = 0.0f;
	mFinished = false;

	//Default
	mHealth = kHealth;
	mSpeed = kSpeed;
	mValue = kValue;
}

void CEnemy::Hide()
{
	mModel->SetPosition(OFF_SCREEN_X, OFF_SCREEN_Y, OFF_SCREEN_Z);
}

CEnemy::~CEnemy()
{
	if (mMesh != 0 && gEngine != 0)
	{
		mMesh->RemoveModel(mModel);
	}
}