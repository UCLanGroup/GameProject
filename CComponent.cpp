#include "CComponent.h"

namespace tle_ui
{
	/*******************************
			 Public methods
	********************************/

	//Checks if the mouse event location is within the component
	//If so triggers the event call to the event handler
	void CComponent::CheckEvent(CMouseEvent& mouseEvent)
	{
		if (eventHandler != nullptr)
		{
			if ((mX < mouseEvent.GetX()) && ((mX + mCalcedWidth) > mouseEvent.GetX()) &&
				(mY < mouseEvent.GetY()) && ((mY + mCalcedHeight) > mouseEvent.GetY()))
			{
				if (mMouseOver)
				{
					if (mouseEvent.GetType() == CMouseEvent::Mouse_Clicked)
					{
						eventHandler->MouseClickedEvent(CMouseEvent(this, CMouseEvent::Mouse_Clicked, mouseEvent.GetX(), mouseEvent.GetY()));
					}
					else
					{
						eventHandler->MouseMovedEvent(CMouseEvent(this, CMouseEvent::Mouse_Moved, mouseEvent.GetX(), mouseEvent.GetY()));
					}
				}
				else
				{
					mMouseOver = true;
					eventHandler->MouseEnteredEvent(CMouseEvent(this, CMouseEvent::Mouse_Entered, mouseEvent.GetX(), mouseEvent.GetY()));
				}
			}
			else if(mMouseOver)
			{
				mMouseOver = false;
				eventHandler->MouseExittedEvent(CMouseEvent(this, CMouseEvent::Mouse_Exitted, mouseEvent.GetX(), mouseEvent.GetY()));
			}
		}
	}

	//Sets the width of the component
	//Set to -1 for auto scale
	void CComponent::SetWidth(int width)
	{
		mWidth = width;
		Resize();
	}

	//Sets the height of the component
	//Set to -1 for auto scale
	void CComponent::SetHeight(int height)
	{
		mHeight = height;
		Resize();
	}

	//Sets the width and height of the component
	//Set to -1 for auto scale
	void CComponent::SetSize(int width, int height)
	{
		mWidth = width;
		mHeight = height;
		Resize();
	}

	//Sets the x position of the UI object
	void CComponent::SetX(int x)
	{
		mX = x;
	}

	//Sets the y position of the UI object
	void CComponent::SetY(int y)
	{
		mY = y;
	}

	//Sets the x and y position of the UI object
	void CComponent::SetPosition(int x, int y)
	{
		mX = x;
		mY = y;
	}

	//Sets the width of empty space around the component
	void CComponent::SetMargin(int margin)
	{
		mMargin = margin;
		Resize();
	}

	//Sets the component's max width
	void CComponent::SetMaxWidth(int maxWidth)
	{
		mMaxWidth = maxWidth;
		Resize();
	}

	//Sets the component's max height
	void CComponent::SetMaxHeight(int maxHeight)
	{
		mMaxHeight = maxHeight;
		Resize();
	}

	//Sets the component's maximum width and height, only used for auto scaling
	void CComponent::SetMaxSize(int maxWidth, int maxHeight)
	{
		mMaxWidth = maxWidth;
		mMaxHeight = maxHeight;
		Resize();
	}

	//Sets the way the contents are displayed within the component
	void CComponent::SetOrientation(Orientation orientation)
	{
		mOrientation = orientation;
	}

	//Sets the way the contents are aligned vertically within the component
	void CComponent::SetVertAlignment(Alignment alignment)
	{
		mVertical = alignment;
	}

	//Sets the way the contents are aligned horizontally within the component
	void CComponent::SetHorAlignment(Alignment alignment)
	{
		mHorizontal = alignment;
	}

	//Sets the way the contents are aligned horizontally and vertically within the component
	void CComponent::SetAlignments(Alignment horizontal, Alignment vertical)
	{
		mHorizontal = horizontal;
		mVertical = vertical;
	}

	//Adds an event handler to the component that will recieve events from the component
	void CComponent::SetEventHandler(IMouseEventHandler* handler)
	{
		eventHandler = handler;
	}

	//Returns the component's width
	int CComponent::GetWidth()
	{
		return mCalcedWidth;
	}

	//Returns the component's height
	int CComponent::GetHeight()
	{
		return mCalcedHeight;
	}

	//Returns the component's x position
	int CComponent::GetX()
	{
		return mX;
	}

	//Returns the component's y position
	int CComponent::GetY()
	{
		return mY;
	}

	//Returns the component's margin
	int CComponent::GetMargin()
	{
		return mMargin;
	}

	//Returns the component's maximum width
	int CComponent::GetMaxWidth()
	{
		return mMaxWidth;
	}

	//Returns the component's maximum height
	int CComponent::GetMaxHeight()
	{
		return mMaxHeight;
	}

	//Returns the orientation of the contents within the component
	Orientation CComponent::GetOrientation()
	{
		return mOrientation;
	}

	//Returns the way the contents are aligned vertically within the component
	Alignment CComponent::GetVertAlignment()
	{
		return mVertical;
	}

	//returns the way the contents are aligned horizontally within the component
	Alignment CComponent::GetHorAlignment()
	{
		return mHorizontal;
	}
}