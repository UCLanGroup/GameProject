#include "CSpinner.h"

//CLabel* mRightLabel;
//CLabel* mLeftLabel;
//CLabel* mValueLabel;
//
//unsigned int mTextColor = tle::kWhite;
//unsigned int mButtonColor = tle::kWhite;
//unsigned int mButtonOverColor = tle::kRed;
//
//data mMinValue;
//data mMaxValue;
//data mIncrement;
namespace tle_ui
{
	//Handles events from the mouse being moved over a component
	void CSpinner::MouseEnteredEvent(const CMouseEvent& mouseEvent)
	{
		if (mouseEvent.GetSource() == mRightButton)
		{
			mLeftButton->SetFocus(false);
		}
		else if (mouseEvent.GetSource() == mLeftButton)
		{
			mRightButton->SetFocus(false);
		}
	}

	//Handles events from the mouse being moved off of a component
	void CSpinner::MouseExittedEvent(const CMouseEvent& mouseEvent)
	{
		if (mouseEvent.GetSource() == mRightButton)
		{
			mLeftButton->SetFocus(mHasFocus);
		}
		else if (mouseEvent.GetSource() == mLeftButton)
		{
			mRightButton->SetFocus(mHasFocus);
		}
	}

	//Handles events from the a component being clicked on
	void CSpinner::MouseClickedEvent(const CMouseEvent& mouseEvent)
	{
		if (mouseEvent.GetSource() == mRightButton)
		{
			SetValue(mValue + mIncrement);

			if (eventHandler != nullptr)
			{
				if (mpMouseClickSound) mpMouseClickSound->Play();
				eventHandler->MouseClickedEvent(CMouseEvent(this, CMouseEvent::Mouse_Clicked, mouseEvent.GetX(), mouseEvent.GetY()));
			}
		}
		else if (mouseEvent.GetSource() == mLeftButton)
		{
			SetValue(mValue - mIncrement);

			if (eventHandler != nullptr)
			{
				if (mpMouseClickSound) mpMouseClickSound->Play();
				eventHandler->MouseClickedEvent(CMouseEvent(this, CMouseEvent::Mouse_Clicked, mouseEvent.GetX(), mouseEvent.GetY()));
			}
		}
	}

	//Handles events from the mouse being moved while over a component
	void CSpinner::MouseMovedEvent(const CMouseEvent& mouseEvent)
	{
		//None
	}

	//Creates a spinner with the given font and colors
	CSpinner::CSpinner(tle::IFont* font, int value)
	{
		mIsFocusable = true;
		mpFont = font;
		mLeftButton = new CButton(font, "<", mButtonColor, mButtonOverColor);
		mLeftButton->SetEventHandler(this);
		mLeftButton->SetParent(this);
		mRightButton = new CButton(font, ">", mButtonColor, mButtonOverColor);
		mRightButton->SetEventHandler(this);
		mRightButton->SetParent(this);
		mValueLabel = new CLabel(font, std::to_string(value), mTextColor);

		mValue = value;
		mMinValue = value;
		mMaxValue = value;
		mIncrement = 1;

		Resize();
	}

	//Resizes the component to fit the text
	void CSpinner::Resize()
	{
		int textWidth = mpFont->MeasureTextWidth(std::to_string(mMaxValue) + "1");
		mValueLabel->SetWidth(textWidth);
		mLeftButton->Resize();
		mRightButton->Resize();

		//Calc width
		if (mWidth == kAutoScale)
		{
			mCalcedWidth = mMargin * 2;
			mCalcedWidth += mValueLabel->GetWidth();
			mCalcedWidth += mLeftButton->GetWidth();
			mCalcedWidth += mRightButton->GetWidth();
		}
		else
			mCalcedWidth = mWidth;

		//Calc height
		if (mHeight == kAutoScale)
			mCalcedHeight = mMargin * 2 + mLeftButton->GetHeight();
		else
			mCalcedHeight = mHeight;

		mLeftButton->SetPosition(mX + mMargin, mY + mMargin);
		mValueLabel->SetPosition(mLeftButton->GetX() + mLeftButton->GetWidth(), mY + mMargin);
		mRightButton->SetPosition(mValueLabel->GetX() + mValueLabel->GetWidth(), mY + mMargin);
	}

	//Update function for manual updating of content
	void CSpinner::Update(float delta)
	{
		//None
	}

	//Called before draw call to the engine
	//Called by parent component's Draw function
	void CSpinner::Draw()
	{
		mValueLabel->Draw();
		mLeftButton->Draw();
		mRightButton->Draw();
	}

	//Checks if the mouse event location is within the component
	//If so triggers the event call to the event handler
	void CSpinner::CheckEvent(CMouseEvent& mouseEvent)
	{
		mLeftButton->CheckEvent(mouseEvent);
		mRightButton->CheckEvent(mouseEvent);
	}

	//Key event handler
	void CSpinner::KeyEvent(tle::EKeyCode keyCode)
	{
		if (mpParent)
		{
			if (keyCode == tle::EKeyCode::Key_Up)
			{
				mpParent->PassFocusUp();
			}
			if (keyCode == tle::EKeyCode::Key_Down)
			{
				mpParent->PassFocusDown();
			}
			if (keyCode == tle::EKeyCode::Key_Left)
			{
				MouseClickedEvent(CMouseEvent(mLeftButton, CMouseEvent::Mouse_Clicked, -1, -1));
			}
			if (keyCode == tle::EKeyCode::Key_Right)
			{
				MouseClickedEvent(CMouseEvent(mRightButton, CMouseEvent::Mouse_Clicked, -1, -1));
			}
		}
	}

	//Sets whether the component is now in focus
	void CSpinner::SetFocus(bool hasFocus)
	{
		mHasFocus = hasFocus;
		mRightButton->SetFocus(hasFocus);
		mLeftButton->SetFocus(hasFocus);
	}

	//Sets the font used for the label's text
	void CSpinner::SetFont(tle::IFont* font)
	{
		mpFont = font;
		mValueLabel->SetFont(font);
		mLeftButton->SetFont(font);
		mRightButton->SetFont(font);
		Resize();
	}

	//Sets the color of the text
	void CSpinner::SetTextColor(unsigned int color)
	{
		mTextColor = color;
		mLeftButton->SetColor(color);
		mRightButton->SetColor(color);
		mValueLabel->SetColor(color);
	}

	//Sets the minimum value of the spinner
	void CSpinner::SetMinValue(int minValue)
	{
		mMinValue = minValue;
	}

	//Sets the maximum value of the spinner
	void CSpinner::SetMaxValue(int maxValue)
	{
		mMaxValue = maxValue;
	}

	//Sets the amount the spinner will increment in
	void CSpinner::SetIncrement(int increment)
	{
		mIncrement = increment;
	}

	//Sets the spinner's value
	void CSpinner::SetValue(int value)
	{
		if (value > mMaxValue) mValue = mMaxValue;
		else if (value < mMinValue) mValue = mMinValue;
		else mValue = value;

		mValueLabel->SetText(std::to_string(mValue));
	}

	//Sets the x position of the UI object
	void CSpinner::SetX(int x)
	{
		int xDif = x - mX;

		mValueLabel->SetX(mValueLabel->GetX() + xDif);
		mLeftButton->SetX(mLeftButton->GetX() + xDif);
		mRightButton->SetX(mRightButton->GetX() + xDif);

		mX = x;
	}

	//Sets the y position of the UI object
	void CSpinner::SetY(int y)
	{
		int yDif = y - mY;

		mValueLabel->SetY(mValueLabel->GetY() + yDif);
		mLeftButton->SetY(mLeftButton->GetY() + yDif);
		mRightButton->SetY(mRightButton->GetY() + yDif);

		mY = y;
	}

	//Sets the x and y position of the UI object
	void CSpinner::SetPosition(int x, int y)
	{
		int xDif = x - mX;
		int yDif = y - mY;

		mValueLabel->SetPosition(mValueLabel->GetX() + xDif, mValueLabel->GetY() + yDif);
		mLeftButton->SetPosition(mLeftButton->GetX() + xDif, mLeftButton->GetY() + yDif);
		mRightButton->SetPosition(mRightButton->GetX() + xDif, mRightButton->GetY() + yDif);

		mX = x;
		mY = y;
	}

	//Sets the sound that is played when the mouse is moved over the component
	//If the sound is a null pointer then no sound is played
	void CSpinner::SetMouseOverSound(tle::ISound* pSound)
	{
		CComponent::SetMouseOverSound(pSound);
		mLeftButton->SetMouseOverSound(pSound);
		mRightButton->SetMouseOverSound(pSound);
	}

	//Sets the sound that is played when the component is clicked on
	//If the sound is a null pointer then no sound is played
	void CSpinner::SetMouseClickSound(tle::ISound* pSound)
	{
		CComponent::SetMouseClickSound(pSound);
		mLeftButton->SetMouseClickSound(pSound);
		mRightButton->SetMouseClickSound(pSound);
	}

	//Sets the sound that is played when the mouse is moved over the component
	//Sets the sound that is played when the component is clicked on
	//If a sound is a null pointer then no sound is played
	void CSpinner::SetSounds(tle::ISound* pMouseOver, tle::ISound* pMouseClick)
	{
		CComponent::SetMouseOverSound(pMouseOver);
		mLeftButton->SetMouseOverSound(pMouseOver);
		mRightButton->SetMouseOverSound(pMouseOver);

		CComponent::SetMouseClickSound(pMouseClick);
		mLeftButton->SetMouseClickSound(pMouseClick);
		mRightButton->SetMouseClickSound(pMouseClick);
	}

	//Returns the font used to create the text
	tle::IFont* CSpinner::GetFont()
	{
		return mpFont;
	}

	//Returns the color of the text
	unsigned int CSpinner::GetTextColor()
	{
		return mTextColor;
	}

	//Gets the minimum value of the spinner
	int CSpinner::GetMinValue()
	{
		return mMinValue;
	}

	//Gets the maximum value of the spinner
	int CSpinner::GetMaxValue()
	{
		return mMaxValue;
	}

	//Gets the amount the spinner will increment in
	int CSpinner::GetIncrement()
	{
		return mIncrement;
	}

	//Gets the spinner's value
	int CSpinner::GetValue()
	{
		return mValue;
	}

	//Destroys the spinner
	CSpinner::~CSpinner()
	{
		delete mLeftButton;
		delete mRightButton;
		delete mValueLabel;
	}
}