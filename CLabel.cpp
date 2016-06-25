#include "CLabel.h"

namespace tle_ui
{

	CLabel::CLabel(tle::IFont* font, const string& text, unsigned int color)
	{
		mpFont = font;
		mText = text;
		mTextColor = color;
		mIsFocusable = false;
		Resize();
	}

	//Resizes the component to fit the text
	void CLabel::Resize()
	{
		int textWidth = 0;
		int textHeight = 0;

		if (mpFont)
		{
			textWidth = mpFont->MeasureTextWidth(mText);
			textHeight = mpFont->MeasureTextHeight(mText);
		}

		//Calc width
		if (mWidth == kAutoScale)
			mCalcedWidth = mMargin * 2 + textWidth;
		else
			mCalcedWidth = mWidth;

		//Calc height
		if (mHeight == kAutoScale)
			mCalcedHeight = mMargin * 2 + textHeight;
		else
			mCalcedHeight = mHeight;

		//Horizontal alignment
		switch (mHorizontal)
		{
		case Right:
			mTextX = mX + mCalcedWidth - textWidth - mMargin;
			break;

		case Left:
			mTextX = mX + mMargin;
			break;

		case Center:
			mTextX = mX + ((mCalcedWidth - textWidth) / 2);
			break;

		default:
			//Unsupported alignment type
			break;
		}

		//Vertical alignment
		switch (mVertical)
		{
		case Top:
			mTextY = mY + mMargin;
			break;

		case Bottom:
			mTextY = mY + mCalcedHeight - textHeight - mMargin;
			break;

		case Center:
			mTextY = mY + ((mCalcedHeight - textHeight) / 2);
			break;

		default:
			//Unsupported alignment type
			break;
		}
	}

	//Update function for manual updating of content
	void CLabel::Update(float delta)
	{
		//Nothing to update
	}

	//Called before draw call to the engine
	//Called by parent component's Draw function
	void CLabel::Draw()
	{
		//Skip draw if there is no font
		if (!mpFont) return;

		mpFont->Draw(mText, mTextX - 3, mTextY - 3, tle::kBlack);
		mpFont->Draw(mText, mTextX, mTextY, mTextColor);
	}

	//Sets the font used for the label's text
	void CLabel::SetFont(tle::IFont* font)
	{
		mpFont = font;
		Resize();
	}

	//Sets the text that is displayed
	void CLabel::SetText(const string& text)
	{
		mText = text;
		Resize();
	}

	//Sets the color of the text
	void CLabel::SetColor(unsigned int color)
	{
		mTextColor = color;
	}

	//Sets the x position of the UI object
	void CLabel::SetX(int x)
	{
		int xDif = x - mX;

		mTextX += xDif;

		mX = x;
	}

	//Sets the y position of the UI object
	void CLabel::SetY(int y)
	{
		int yDif = y - mY;

		mTextY += yDif;

		mY = y;
	}

	//Sets the x and y position of the UI object
	void CLabel::SetPosition(int x, int y)
	{
		int xDif = x - mX;
		int yDif = y - mY;

		mTextX += xDif;
		mTextY += yDif;

		mX = x;
		mY = y;
	}

	//Returns the font used to create the text
	tle::IFont* CLabel::GetFont()
	{
		return mpFont;
	}

	//Returns the text
	string CLabel::GetText()
	{
		return mText;
	}

	//Returns the color of the text
	unsigned int CLabel::GetColor()
	{
		return mTextColor;
	}
}