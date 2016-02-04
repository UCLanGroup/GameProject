#include "CAnimation.h"
#include "Globals.h"

CAnimation::CAnimation(SpriteVector& sprites, float x, float y, float z, float rate, bool looped)
{
	mSprites = sprites;
	mX = x;
	mY = y;
	mZ = z;
	mAnimationRate = rate;
	mTimePassed = 0.0f;
	mLooped = looped;
	mHasEnded = false;

	//Set the first sprite on screen
	mActiveSprite = mSprites.begin();
	if (mActiveSprite != mSprites.end()) //Check if there is sprites within the vector
	{
		(*mActiveSprite)->SetPosition(mX, mY);
		mActiveSprite++;
	}

	//Move all other sprites off screen
	for (; mActiveSprite != mSprites.end(); mActiveSprite++)
	{
		(*mActiveSprite)->SetPosition(gEngine->GetWidth(), gEngine->GetHeight());
	}
	mActiveSprite = mSprites.begin();
}

//Move the animation frames along by the set amount of time
void CAnimation::Animate(float delta)
{
	//Don't Animate if it is not looped and has already reached the end
	if (!mLooped && mActiveSprite == mSprites.end()) return;
	//Don't Animate if there is not sprites in the vector, so I can assume for the rest of the code that there is at least one sprite
	//It's also a small optimization due to less checks needed to make it robust
	if (!mSprites.size()) return;

	//Increment timer
	mTimePassed += delta;
	//For each tick of the animation that has passed since the last call
	while (mTimePassed > mAnimationRate)
	{
		//Remove the previous sprite
		(*mActiveSprite)->SetPosition(gEngine->GetWidth(), gEngine->GetHeight());

		//Increment sprite pointer
		mActiveSprite++;
		if (mActiveSprite == mSprites.end())
		{
			if (mLooped) //Loop back to the start
			{
				mActiveSprite = mSprites.begin();
			}
			else //Revert back to the last available sprite
			{
				mActiveSprite--;
				mHasEnded = true;
			}
		}

		//Place next sprite on screen
		(*mActiveSprite)->SetPosition(mX, mY);

		//Decrement timer
		mTimePassed -= mAnimationRate;
	}
}

//Reset the animation to the start
void CAnimation::Reset()
{
	mTimePassed = 0.0f;
	mHasEnded = false;

	//Check if there are sprites
	if (mSprites.size())
	{
		//Move the previous sprite off screen
		(*mActiveSprite)->SetPosition(gEngine->GetWidth(), gEngine->GetHeight());

		//Move back to the start
		mActiveSprite = mSprites.begin();

		//Place the current sprite on screen
		(*mActiveSprite)->SetPosition(mX, mY);
	}
}

//Returns whether the animation has reached the end if the animation is not looped
bool CAnimation::HasEnded()
{
	return mHasEnded;
}

//Return whether the animation is looped or not
bool CAnimation::IsLooped()
{
	return mLooped;
}

//Set the x position of the animation
void CAnimation::SetX(float x)
{
	mX = x;
	//Update the current sprite if one exist
	if (mActiveSprite != mSprites.end())
	{
		(*mActiveSprite)->SetX(mX);
	}
}

//Set the y position of the animation
void CAnimation::SetY(float y)
{
	mY = y;
	//Update the current sprite if one exist
	if (mActiveSprite != mSprites.end())
	{
		(*mActiveSprite)->SetY(mY);
	}
}

//Set the z position of the animation
void CAnimation::SetZ(float z)
{
	mZ = z;
	//Update all sprites in the vector
	for (auto it = mSprites.begin(); it != mSprites.end(); it++)
	{
		(*it)->SetZ(mZ);
	}
}

//Set the x and y position of the animation
void CAnimation::SetPosition(float x, float y)
{
	mX = x;
	mY = y;
	//Update the current sprite if one exist
	if (mActiveSprite != mSprites.end())
	{
		(*mActiveSprite)->SetPosition(mX, mY);
	}
}

//Set the x, y and z position of the animation
void CAnimation::SetPosition(float x, float y, float z)
{
	mX = x;
	mY = y;

	//Update the current sprite if one exist
	if (mActiveSprite != mSprites.end())
	{
		(*mActiveSprite)->SetPosition(mX, mY);
	}

	mZ = z;

	//Update all sprites in the vector
	for (auto it = mSprites.begin(); it != mSprites.end(); it++)
	{
		(*it)->SetZ(mZ);
	}
}

//Return the x position of the animation
float CAnimation::GetX()
{
	return mX;
}

//Return the y position of the animation
float CAnimation::GetY()
{
	return mY;
}

//Return the z position of the animation
float CAnimation::GetZ()
{
	return mZ;
}

void CAnimation::MoveX(float xMovement)
{
	mX += xMovement;
	//Update the current sprite if one exist
	if (mActiveSprite != mSprites.end())
	{
		(*mActiveSprite)->SetX(mX);
	}
}

void CAnimation::MoveY(float yMovement)
{
	mY += yMovement;
	//Update the current sprite if one exist
	if (mActiveSprite != mSprites.end())
	{
		(*mActiveSprite)->SetY(mY);
	}
}

void CAnimation::MoveZ(float zMovement)
{
	mZ += zMovement;
	//Update all sprites in the vector
	for (auto it = mSprites.begin(); it != mSprites.end(); it++)
	{
		(*it)->SetZ(mZ);
	}
}

CAnimation::~CAnimation()
{
	//Remove all sprites from the scene
	for (auto it = mSprites.begin(); it != mSprites.end(); it++)
	{
		gEngine->RemoveSprite(*it);
	}
}