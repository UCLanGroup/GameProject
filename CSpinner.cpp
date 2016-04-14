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
		if (mouseEvent.GetSource() == mRightLabel)
		{
			mRightLabel->SetColor(mButtonOverColor);
		}
		else if (mouseEvent.GetSource() == mLeftLabel)
		{
			mLeftLabel->SetColor(mButtonOverColor);
		}
	}

	//Handles events from the mouse being moved off of a component
	void CSpinner::MouseExittedEvent(const CMouseEvent& mouseEvent)
	{
		if (mouseEvent.GetSource() == mRightLabel)
		{
			mRightLabel->SetColor(mButtonColor);
		}
		else if (mouseEvent.GetSource() == mLeftLabel)
		{
			mLeftLabel->SetColor(mButtonColor);
		}
	}

	//Handles events from the a component being clicked on
	void CSpinner::MouseClickedEvent(const CMouseEvent& mouseEvent)
	{
		if (mouseEvent.GetSource() == mRightLabel)
		{
			SetValue(mValue + mIncrement);

			if (eventHandler != nullptr)
			{
				eventHandler->MouseClickedEvent(CMouseEvent(this, CMouseEvent::Mouse_Clicked, mouseEvent.GetX(), mouseEvent.GetY()));
			}
		}
		else if (mouseEvent.GetSource() == mLeftLabel)
		{
			SetValue(mValue - mIncrement);

			if (eventHandler != nullptr)
			{
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
		mpFont = font;
		mLeftLabel = new CLabel(font, "<", mButtonColor);
		mRightLabel = new CLabel(font, ">", mButtonColor);
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
		mLeftLabel->Resize();
		mRightLabel->Resize();

		//Calc width
		if (mWidth == kAutoScale)
		{
			mCalcedWidth = mMargin * 2;
			mCalcedWidth += mValueLabel->GetWidth();
			mCalcedWidth += mLeftLabel->GetWidth();
			mCalcedWidth += mRightLabel->GetWidth();
		}
		else
			mCalcedWidth = mWidth;

		//Calc height
		if (mHeight == kAutoScale)
			mCalcedHeight = mMargin * 2 + mLeftLabel->GetHeight();
		else
			mCalcedHeight = mHeight;

		mLeftLabel->SetPosition(mX + mMargin, mY + mMargin);
		mValueLabel->SetPosition(mLeftLabel->GetX() + mLeftLabel->GetWidth(), mY + mMargin);
		mValueLabel->SetPosition(mValueLabel->GetX() + mValueLabel->GetWidth(), mY + mMargin);
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
		mLeftLabel->Draw();
		mRightLabel->Draw();
	}

	//Checks if the mouse event location is within the component
	//If so triggers the event call to the event handler
	void CSpinner::CheckEvent(CMouseEvent& mouseEvent)
	{
		mLeftLabel->CheckEvent(mouseEvent);
		mRightLabel->CheckEvent(mouseEvent);
	}

	//Sets the font used for the label's text
	void CSpinner::SetFont(tle::IFont* font)
	{
		mpFont = font;
		mValueLabel->SetFont(font);
		mLeftLabel->SetFont(font);
		mRightLabel->SetFont(font);
		Resize();
	}

	//Sets the color of the text
	void CSpinner::SetTextColor(unsigned int color)
	{
		mTextColor = color;
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

		mValueLabel->SetText(std::to_string(value));
	}

	//Sets the x position of the UI object
	void CSpinner::SetX(int x)
	{
		int xDif = x - mX;

		mValueLabel->SetX(mValueLabel->GetX() + xDif);
		mLeftLabel->SetX(mLeftLabel->GetX() + xDif);
		mRightLabel->SetX(mRightLabel->GetX() + xDif);

		mX = x;
	}

	//Sets the y position of the UI object
	void CSpinner::SetY(int y)
	{
		int yDif = y - mY;

		mValueLabel->SetY(mValueLabel->GetY() + yDif);
		mLeftLabel->SetY(mLeftLabel->GetY() + yDif);
		mRightLabel->SetY(mRightLabel->GetY() + yDif);

		mY = y;
	}

	//Sets the x and y position of the UI object
	void CSpinner::SetPosition(int x, int y)
	{
		int xDif = x - mX;
		int yDif = y - mY;

		mValueLabel->SetPosition(mValueLabel->GetX() + xDif, mValueLabel->GetY() + yDif);
		mLeftLabel->SetPosition(mLeftLabel->GetX() + xDif, mLeftLabel->GetY() + yDif);
		mRightLabel->SetPosition(mRightLabel->GetX() + xDif, mRightLabel->GetY() + yDif);

		mX = x;
		mY = y;
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
		delete mLeftLabel;
		delete mRightLabel;
		delete mValueLabel;
	}
}