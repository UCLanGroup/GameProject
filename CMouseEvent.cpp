#include "CMouseEvent.h"
#include "CComponent.h"

namespace tle_ui
{
	//Creates a mouse event from the position of the event and the type of event
	CMouseEvent::CMouseEvent(CComponent* source, Type t, int x, int y)
	{
		mSource = source;
		mType = t;
		mX = x;
		mY = y;
	}

	//Returns the source of the event
	CComponent* CMouseEvent::GetSource() const
	{
		return mSource;
	}

	//Returns the type of the event
	CMouseEvent::Type CMouseEvent::GetType() const
	{
		return mType;
	}

	//Returns the x position of where the event occured
	int CMouseEvent::GetX() const
	{
		return mX;
	}

	//Returns the y position of where the event occured
	int CMouseEvent::GetY() const
	{
		return mY;
	}
}
