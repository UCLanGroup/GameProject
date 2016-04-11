#pragma once
#include "CMouseEvent.h"
#include <vector>

namespace tle_ui
{
	const int kAutoScale = -1;

	typedef void(*EventHandler)(const CMouseEvent& mouseEvent);

	enum Orientation : int { Vertical, Horizontal };
	enum Alignment : int {Left, Right, Center, Top, Bottom};
	
	//Base UI component
	class CComponent
	{
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
		void SetEventHandler(EventHandler handler);

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

	protected:
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
		
		EventHandler eventHandler = nullptr;
	};
}