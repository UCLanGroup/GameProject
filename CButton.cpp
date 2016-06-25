#include "CButton.h"

namespace tle_ui
{

	CButton::CButton(tle::IFont* font, const string& text, unsigned int color, unsigned int mouseOverColor)
	{
		mpFont = font;
		mText = text;
		mTextColor = color;
		mTextColorOver = mouseOverColor;
		mIsFocusable = true;
		Resize();
	}

	//Resizes the component to fit the text
	void CButton::Resize()
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
	void CButton::Update(float delta)
	{
		//Nothing to update
	}

	//Called before draw call to the engine
	//Called by parent component's Draw function
	void CButton::Draw()
	{
		//Skip draw if there is no font
		if (!mpFont) return;

		mpFont->Draw(mText, mTextX - 3, mTextY - 3, tle::kBlack);

		if (mHasFocus)
		{
			mpFont->Draw(mText, mTextX, mTextY, mTextColorOver);
		}
		else
		{
			mpFont->Draw(mText, mTextX, mTextY, mTextColor);
		}
	}

	//Key event handler
	void CButton::KeyEvent(tle::EKeyCode keyCode)
	{
		if (mpParent)
		{
			if (keyCode == tle::EKeyCode::Key_Up)
			{
				mpParent->PassFocusUp();
			}
			else if (keyCode == tle::EKeyCode::Key_Down)
			{
				mpParent->PassFocusDown();
			}
			else if (keyCode == tle::EKeyCode::Key_Left)
			{
				mpParent->PassFocusLeft();
			}
			else if (keyCode == tle::EKeyCode::Key_Right)
			{
				mpParent->PassFocusRight();
			}
			else if (keyCode == tle::EKeyCode::Key_Space)
			{
				if (eventHandler)
				{
					if (mpMouseClickSound) mpMouseClickSound->Play();
					eventHandler->MouseClickedEvent(CMouseEvent(this, CMouseEvent::Mouse_Clicked, -1, -1));
				}
			}
		}
	}

	//Sets the font used for the label's text
	void CButton::SetFont(tle::IFont* font)
	{
		mpFont = font;
		Resize();
	}

	//Sets the text that is displayed
	void CButton::SetText(const string& text)
	{
		mText = text;
		Resize();
	}

	//Sets the color of the text
	void CButton::SetColor(unsigned int color)
	{
		mTextColor = color;
	}

	//Sets the color of the text when the mouse is over the button
	void CButton::SetMouseOverColor(unsigned int color)
	{
		mTextColorOver = color;
	}

	//Sets the x position of the UI object
	void CButton::SetX(int x)
	{
		int xDif = x - mX;

		mTextX += xDif;

		mX = x;
	}

	//Sets the y position of the UI object
	void CButton::SetY(int y)
	{
		int yDif = y - mY;

		mTextY += yDif;

		mY = y;
	}

	//Sets the x and y position of the UI object
	void CButton::SetPosition(int x, int y)
	{
		int xDif = x - mX;
		int yDif = y - mY;

		mTextX += xDif;
		mTextY += yDif;

		mX = x;
		mY = y;
	}

	//Returns the font used to create the text
	tle::IFont* CButton::GetFont()
	{
		return mpFont;
	}

	//Returns the text
	string CButton::GetText()
	{
		return mText;
	}

	//Returns the color of the text
	unsigned int CButton::GetColor()
	{
		return mTextColor;
	}

	//Returns the color of the text when the mouse is over
	unsigned int CButton::GetMouseOvercolor()
	{
		return mTextColorOver;
	}
}