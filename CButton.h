#pragma once
#include "ExtendedEngine.h"
#include "CComponent.h"

namespace tle_ui
{
	class CButton final : public CComponent
	{
	private:
		tle::IFont* mpFont = 0;

		string mText;

		unsigned int mTextColor = tle::kWhite;
		unsigned int mTextColorOver = tle::kRed;

		int mTextX = 0;
		int mTextY = 0;

	public:
		CButton(tle::IFont* font, const string& text, unsigned int color = tle::kWhite, unsigned int mouseOverColor = tle::kRed);

		//Resizes the component to fit the text
		virtual void Resize();

		//Update function for manual updating of content
		virtual void Update(float delta);

		//Called before draw call to the engine
		//Called by parent component's Draw function
		virtual void Draw();

		//Key event handler
		virtual void KeyEvent(tle::EKeyCode keyCode);

		//Sets the font used for the label's text
		void SetFont(tle::IFont* font);

		//Sets the text that is displayed
		void SetText(const string& text);

		//Sets the color of the text
		void SetColor(unsigned int color);

		//Sets the color of the text when the mouse is over the button
		void SetMouseOverColor(unsigned int color);

		//Sets the x position of the UI object
		virtual void SetX(int x) final;

		//Sets the y position of the UI object
		virtual void SetY(int y) final;

		//Sets the x and y position of the UI object
		virtual void SetPosition(int x, int y) final;

		//Returns the font used to create the text
		tle::IFont* GetFont();

		//Returns the text
		string GetText();

		//Returns the color of the text
		unsigned int GetColor();

		//Returns the color of the text when the mouse is over
		unsigned int GetMouseOvercolor();
	};
}