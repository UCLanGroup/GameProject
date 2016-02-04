#pragma once
#include <vector>
#include <TL-Engine.h>

using SpriteVector = std::vector<tle::ISprite*>;

class CAnimation
{
private:
	float mX;
	float mY;
	float mZ;
	bool mLooped;
	bool mHasEnded;
	float mAnimationRate;
	float mTimePassed;
	SpriteVector::iterator mActiveSprite;
	SpriteVector mSprites;

public:
	CAnimation(SpriteVector& sprites, float x, float y, float z, float rate, bool looped);
	void Animate(float delta);
	void Reset();
	bool HasEnded();
	bool IsLooped();

	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

	void SetPosition(float x, float y);
	void SetPosition(float x, float y, float z);

	float GetX();
	float GetY();
	float GetZ();

	void MoveX(float xMovement);
	void MoveY(float yMovement);
	void MoveZ(float zMovement);

	~CAnimation();
};