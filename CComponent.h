#pragma once
#include "IMouseEventHandler.h"
#include "CMouseEvent.h"
#include <ISound.h>
#include <list>

namespace tle_ui
{
	const int kAutoScale = -1;

	enum Orientation : int { Vertical, Horizontal };
	enum Alignment : int {Left, Right, Center, Top, Bottom};
	
	//Base UI component
	class CComponent
	{
	private:

		tle::ISound* mpMouseOverSound = 0; //If not null (zero), the sound is played when the mouse is moved over the component
		tle::ISound* mpMouseClickSound = 0; //If not null (zero), the sound is played when the component is clicked on

	public:

		//Resizes the component based on child components
		virtual void Resize() = 0;

		//Update function for manual updating of content
		virtual void Update(float delta) = 0;

		//Called before draw call to the engine
		//Called by parent component's Draw function
		virtual void Draw() = 0;

		//Checks if the mouse event location is within the component
		//If so triggers the event call to the event handler
		virtual void CheckEvent(CMouseEvent& mouseEvent);

		//Sets the width of the component
		//Set to -1 for auto scale
		void SetWidth(int width);

		//Sets the height of the component
		//Set to -1 for auto scale
		void SetHeight(int height);

		//Sets the width and height of the component
		//Set to -1 for auto scale
		void SetSize(int width, int height);

		//Sets the x position of the UI object
		virtual void SetX(int x);

		//Sets the y position of the UI object
		virtual void SetY(int y);

		//Sets the x and y position of the UI object
		virtual void SetPosition(int x, int y);

		//Sets the width of empty space around the component
		void SetMargin(int margin);

		//Sets the component's max width, only used for auto scaling
		void SetMaxWidth(int maxWidth);

		//Sets the component's max height, only used for auto scaling
		void SetMaxHeight(int maxHeight);

		//Sets the component's maximum width and height, only used for auto scaling
		void SetMaxSize(int maxWidth, int maxHeight);

		//Sets the way the contents are displayed within the component
		void SetOrientation(Orientation orientation);
		
		//Sets the way the contents are aligned vertically within the component
		void SetVertAlignment(Alignment alignment);

		//Sets the way the contents are aligned horizontally within the component
		void SetHorAlignment(Alignment alignment);

		//Sets the way the contents are aligned horizontally and vertically within the component
		void SetAlignments(Alignment horizontal, Alignment vertical);

		//Adds an event handler to the component that will recieve events from the component
		void SetEventHandler(IMouseEventHandler* handler);

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

		//Returns the component's width
		int GetWidth();

		//Returns the component's height
		int GetHeight();

		//Returns the component's x position
		int GetX();

		//Returns the component's y position
		int GetY();

		//Returns the component's margin
		int GetMargin();

		//Returns the component's maximum width
		int GetMaxWidth();

		//Returns the component's maximum height
		int GetMaxHeight();

		//Returns the orientation of the contents within the component
		Orientation GetOrientation();

		//Returns the way the contents are aligned vertically within the component
		Alignment GetVertAlignment();

		//returns the way the contents are aligned horizontally within the component
		Alignment GetHorAlignment();

		//Gets the sound that is played when the mouse is moved over the component
		//If no sound then zero is returned
		tle::ISound* GetMouseOverSound();

		//Sets the sound that is played when the component is clicked on
		//If no sound then zero is returned
		tle::ISound* SetMouseClickSound();

	protected:
		bool mMouseOver = false; //Is the mouse currently over this component

		int mX = 0;
		int mY = 0;
		int mWidth = kAutoScale;
		int mHeight = kAutoScale;
		int mMaxWidth = kAutoScale;
		int mMaxHeight = kAutoScale;
		int mMargin = 1;

		int mCalcedWidth = 2;
		int mCalcedHeight = 2;

		Orientation mOrientation = Orientation::Vertical;
		Alignment mVertical = Alignment::Center; //The vertical alignment
		Alignment mHorizontal = Alignment::Center; //The horizontal alignment
		
		IMouseEventHandler* eventHandler = nullptr;
	};
}