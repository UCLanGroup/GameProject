#include "CImage.h"

namespace tle_ui
{

	CImage::CImage(tle::ISprite* sprite, int width, int height)
	{
		mpSprite = sprite;
		mImageWidth = width;
		mImageHeight = height;
		Resize();
	}

	//Resizes the component to fit the text
	void CImage::Resize()
	{
		//Calc width
		if (mWidth == kAutoScale)
			mCalcedWidth = mMargin * 2 + mImageWidth;
		else
			mCalcedWidth = mWidth;

		//Calc height
		if (mHeight == kAutoScale)
			mCalcedHeight = mMargin * 2 + mImageHeight;
		else
			mCalcedHeight = mHeight;

		//Horizontal alignment
		switch (mHorizontal)
		{
		case Right:
			mImageX = mX + mCalcedWidth - mImageWidth - mMargin;
			break;

		case Left:
			mImageX = mX + mMargin;
			break;

		case Center:
			mImageX = mX + ((mCalcedWidth - mImageWidth) / 2);
			break;

		default:
			//Unsupported alignment type
			break;
		}

		//Vertical alignment
		switch (mVertical)
		{
		case Top:
			mImageY = mY + mMargin;
			break;

		case Bottom:
			mImageY = mY + mCalcedHeight - mImageHeight - mMargin;
			break;

		case Center:
			mImageY = mY + ((mCalcedHeight - mImageHeight) / 2);
			break;

		default:
			//Unsupported alignment type
			break;
		}
	}

	//Update function for manual updating of content
	void CImage::Update(float delta)
	{
		//Nothing to update
	}

	//Called before draw call to the engine
	//Called by parent component's Draw function
	void CImage::Draw()
	{
		//Nothing to draw
	}

	//Sets the font used for the label's text
	void CImage::SetSprite(tle::ISprite* sprite)
	{
		mpSprite = sprite;
		Resize();
	}

	//Sets the x position of the UI object
	void CImage::SetX(int x)
	{
		int xDif = x - mX;

		if (mpSprite) mpSprite->MoveX(static_cast<float>(xDif));

		mX = x;
	}

	//Sets the y position of the UI object
	void CImage::SetY(int y)
	{
		int yDif = y - mY;

		if (mpSprite) mpSprite->MoveY(static_cast<float>(yDif));

		mY = y;
	}

	//Sets the x and y position of the UI object
	void CImage::SetPosition(int x, int y)
	{
		int xDif = x - mX;
		int yDif = y - mY;

		if (mpSprite)
		{
			mpSprite->Move(static_cast<float>(xDif), static_cast<float>(yDif));
		}

		mX = x;
		mY = y;
	}

	//Returns the font used to create the text
	tle::ISprite* CImage::GetSprite()
	{
		return mpSprite;
	}
}