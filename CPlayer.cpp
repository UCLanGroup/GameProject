#include "CPlayer.h"
#include <algorithm> //for min & max functions
#include <iostream>
#include <sstream>

void CPlayer::Init()
{
	//Model
	SetMesh(PLAYER_MESH);

	//Shield
	mShieldMesh = gEngine->LoadMesh(SHIELD_MESH);
	mShieldModel = mShieldMesh->CreateModel(0.0f, 0.0f, 0.0f);
	mShieldModel->Scale(12.0f);
	mShieldModel->AttachToParent(mModel);

	//Weapon
	mProjectileMesh = gEngine->LoadMesh(BULLET_MESH);
	mWeapon.reset(new CWeapon(this, mProjectileMesh, 1, 100.0f, 0.1f));

	//Stats
	mHealth = 100;
	mScore = 0;
	mLives = 3;
	mMaxHealth = 100;
	mShield = 50;
	mMaxShield = 50;
	mShieldRegenRate = 0.25f;
	mRegenTimer = 0.0f;
	mSpeed = 50.0f;
	mScore = 0;
	SetRadius(5.0f);

	// Draw life sprites
	for (int i = 0; i < mLives; i++)
	{
		int startPosX = 505;
		int startPosY = 932;
		int startPosInc = 35;
		ISprite* temp = gEngine->CreateSprite("life.png", startPosX + startPosInc * i, startPosY, 0.01f);
		mLifeSprites.push_back(temp);
}

	mpHealthBar = gEngine->CreateSprite("healthbar.png", mStartBarPosX, mStartBarPosY, 0.15f);
	mpShieldBar = gEngine->CreateSprite("shieldbar.png", mStartBarPosX, mStartBarPosY + 37.0f, 0.15f);

	//Text
	mFont = gEngine->LoadFont("Rockwell", 60U);
}

void CPlayer::Cleanup()
{
	GetMesh()->RemoveModel(mModel);
	mModel = 0;
	mShieldMesh->RemoveModel(mShieldModel);
	mShieldModel = 0;
	gEngine->RemoveFont(mFont);
	for (int i = mLives; i > 0; i--)
	{
		gEngine->RemoveSprite(mLifeSprites[i - 1]);
	}
	gEngine->RemoveSprite(mpHealthBar);
	gEngine->RemoveSprite(mpShieldBar);
}

void CPlayer::Move(float dt)
{
	if (gEngine->KeyHeld(KEY_UP))
	{
		mModel->MoveZ(mSpeed * dt);
		if (mModel->GetZ() > AREA_BOUNDS_TOP)
		{
			mModel->SetZ(AREA_BOUNDS_TOP);
		}
	}
	if (gEngine->KeyHeld(KEY_DOWN))
	{
		mModel->MoveZ(-mSpeed * dt);
		if (mModel->GetZ() < AREA_BOUNDS_BOTTOM)
		{
			mModel->SetZ(AREA_BOUNDS_BOTTOM);
		}
	}

	bool rotatePlane = true;
	float rotateSpeed = 400.0f;
	if (!gEngine->KeyHeld(KEY_LEFT) && !gEngine->KeyHeld(KEY_RIGHT))
	{
		rotatePlane = false;
	}

	// LEVEL PLANE WHEN NOT TURNING
	if (rotatePlane == false)
	{
		float rotAmount = rotateSpeed * dt;

		if (mRotation > 0.5f)
		{
			mModel->RotateZ(rotAmount);
			mRotation -= rotAmount;
		}
		else if (mRotation < -0.5f)
		{
			mModel->RotateZ(-rotAmount);
			mRotation += rotAmount;
		}
	}

	if (gEngine->KeyHeld(KEY_LEFT))
	{
		mModel->MoveX(-mSpeed * dt);
		if (mModel->GetX() < AREA_BOUNDS_LEFT)
		{
			mModel->SetX(AREA_BOUNDS_LEFT);
		}

		if (mRotation >= -50.0f)
		{
			float rotAmount = rotateSpeed * dt;
			mModel->RotateZ(rotAmount);
			mRotation -= rotAmount;
		}
	}
	if (gEngine->KeyHeld(KEY_RIGHT))
	{
		mModel->MoveX(mSpeed * dt);
		if (mModel->GetX() > AREA_BOUNDS_RIGHT)
		{
			mModel->SetX(AREA_BOUNDS_RIGHT);
		}

		if (mRotation <= 50.0f)
		{
			float rotAmount = rotateSpeed * dt;
			mModel->RotateZ(-rotAmount);
			mRotation += rotAmount;
		}
	}

	//Shield Regen

	if (mShield < mMaxShield)
	{
		mRegenTimer += dt;
		
		while (mRegenTimer > mShieldRegenRate && mShield < mMaxShield)
		{
			if (mShield == 0) //Reattach shield if hidden
			{
				mShieldModel->SetPosition(0.0f, 0.0f, 0.0f);
				mShieldModel->AttachToParent(mModel);
			}
			mShield++;

			mRegenTimer -= mShieldRegenRate;
		}
	}

	DrawText();

	//Health Bars
	AnimateShield(dt);
	AnimateHealth(dt);
}

void CPlayer::CheckCollision()
{
	//No collision check atm
}

void CPlayer::TakeDamage(int damage)
{
	mRegenTimer = -5.0f; //5 second delay before shield regen starts

	if (mShield > 0)
	{
		if (damage >= mShield) //Shield is destroyed
		{
			//Apply left over damage to health
			mHealth -= mShield - damage;

			//Remove shield model
			mShieldModel->DetachFromParent();
			mShieldModel->SetPosition(OFF_SCREEN_X, OFF_SCREEN_Y, OFF_SCREEN_Z);
		}
		mShield -= min(damage, mShield);
		mShieldMove += damage * 4.0f; // for shield bar animation
	}
	else
	{
		mHealth -= damage;
		mHealthMove += damage * 2.0f; // for health bar animation
	}
}

void CPlayer::DrawText()
{
	stringstream textOut;
	//textOut.precision(2);
	textOut << mScore;
	mFont->Draw(textOut.str(), 1005, 940, kYellow);
}

void CPlayer::AnimateHealth(float delta)
{
	if (mHealthMove > 0)
	{
		mpHealthBar->MoveX(-100.0f * delta);
		mHealthMove -= 100.0f * delta;
	}
}

void CPlayer::AnimateShield(float delta)
{
	if (mShieldMove > 0)
	{
		mpShieldBar->MoveX(-100.0f * delta);
		mShieldMove -= 100.0f * delta;
	}
}

void CPlayer::IncreaseScore(int value)
{
	mScore += value;
	cout << "Player's Score:  " << mScore << endl;
}

//Sets

void CPlayer::SetScore(int score)
{
	mScore = score;
}

void CPlayer::SetHealth(int health)
{
	if (mMaxHealth < health)
	{
		mHealth = mMaxHealth;
	}
	else
	{
		mHealth = health;
	}
}

void CPlayer::SetMaxHealth(int health)
{
	mMaxHealth = health;
}

void CPlayer::SetShield(int shield)
{
	if (mMaxShield < shield)
	{
		mShield = mMaxShield;
	}
	else
	{
		mShield = shield;
	}
}

void CPlayer::SetMaxShield(int shield)
{
	mMaxShield = shield;
}

void CPlayer::SetShieldRegen(float regen)
{
	mShieldRegenRate = regen;
}

//Gets

int CPlayer::GetScore()
{
	return mScore;
}

int CPlayer::GetHealth()
{
	return mHealth;
}

int CPlayer::GetMaxHealth()
{
	return mMaxHealth;
}

int CPlayer::GetShield()
{
	return mShield;
}

int CPlayer::GetMaxShield()
{
	return mMaxShield;
}

CWeapon* CPlayer::GetWeapon()
{
	return mWeapon.get();
}

//Inherited from IEntity
void CPlayer::Reset()
{
	mHealth = 100;
	mMaxHealth = 100;
	mShield = 50;
	mMaxShield = 50;
	mRegenTimer = 0.0f;

	mpHealthBar->SetPosition(mStartBarPosX, mStartBarPosY);
	mpShieldBar->SetPosition(mStartBarPosX, mStartBarPosY + 37.0f);
}

CPlayer::~CPlayer()
{
}
