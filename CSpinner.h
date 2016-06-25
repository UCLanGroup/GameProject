#pragma once
#include "ExtendedEngine.h"
#include "CComponent.h"
#include "CLabel.h"
#include "CButton.h"
#include "IMouseEventHandler.h"

namespace tle_ui
{
	class CSpinner : public CComponent, public IMouseEventHandler
	{
	private:
		CButton* mRightButton;
		CButton* mLeftButton;
		CLabel* mValueLabel;

		unsigned int mTextColor = tle::kWhite;
		unsigned int mButtonColor = tle::kWhite;
		unsigned int mButtonOverColor = tle::kRed;

		int mValue;
		int mMinValue;
		int mMaxValue;
		int mIncrement;

		tle::IFont* mpFont;

		//Handles events from the mouse being moved over a component
		virtual void MouseEnteredEvent(const CMouseEvent& mouseEvent);

		//Handles events from the mouse being moved off of a component
		virtual void MouseExittedEvent(const CMouseEvent& mouseEvent);

		//Handles events from the a component being clicked on
		virtual void MouseClickedEvent(const CMouseEvent& mouseEvent);

		//Handles events from the mouse being moved while over a component
		virtual void MouseMovedEvent(const CMouseEvent& mouseEvent);

	public:
		//Creates a spinner with the given font and colors
		CSpinner(tle::IFont* font, int value);

		//Resizes the component to fit the text
		virtual void Resize();

		//Update function for manual updating of content
		virtual void Update(float delta);

		//Called before draw call to the engine
		//Called by parent component's Draw function
		virtual void Draw();

		//Checks if the mouse event location is within the component
		//If so triggers the event call to the event handler
		virtual void CheckEvent(CMouseEvent& mouseEvent);

		//Key event handler
		virtual void KeyEvent(tle::EKeyCode keyCode);

		//Sets whether the component is now in focus
		void SetFocus(bool hasFocus);

		//Sets the font used for the label's text
		void SetFont(tle::IFont* font);

		//Sets the color of the text
		void SetTextColor(unsigned int color);

		//Sets the minimum value of the spinner
		void SetMinValue(int minValue);

		//Sets the maximum value of the spinner
		void SetMaxValue(int maxValue);

		//Sets the amount the spinner will increment in
		void SetIncrement(int increment);

		//Sets the spinner's value
		void SetValue(int value);

		//Sets the x position of the UI object
		virtual void SetX(int x) final;

		//Sets the y position of the UI object
		virtual void SetY(int y) final;

		//Sets the x and y position of the UI object
		virtual void SetPosition(int x, int y) final;

		//Sets the sound that is played when the mouse is moved over the component
		//If the sound is a null pointer then no sound is played
		virtual void SetMouseOverSound(tle::ISound* pSound);

		//Sets the sound that is played when the component is clicked on
		//If the sound is a null pointer then no sound is played
		virtual void SetMouseClickSound(tle::ISound* pSound);

		//Sets the sound that is played when the mouse is moved over the component
		//Sets the sound that is played when the component is clicked on
		//If a sound is a null pointer then no sound is played
		virtual void SetSounds(tle::ISound* pMouseOver, tle::ISound* pMouseClick);

		//Returns the font used to create the text
		tle::IFont* GetFont();

		//Returns the color of the text
		unsigned int GetTextColor();

		//Gets the minimum value of the spinner
		int GetMinValue();

		//Gets the maximum value of the spinner
		int GetMaxValue();

		//Gets the amount the spinner will increment in
		int GetIncrement();

		//Gets the spinner's value
		int GetValue();

		//Destroys the spinner
		~CSpinner();
	};
}