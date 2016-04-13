#pragma once

namespace tle_ui
{
	class CComponent;

	//For forming mouse events to be passed to and from components
	class CMouseEvent
	{
	public:
		//Types of events
		enum Type : int {Mouse_Entered, Mouse_Exitted, Mouse_Clicked, Mouse_Moved};

		//Creates a mouse event from the position of the event and the type of event
		CMouseEvent(CComponent* source, Type t, int x, int y);

		//Returns the source of the event
		CComponent* GetSource() const;

		//Returns the type of the event
		Type GetType() const;

		//Returns the x position of where the event occured
		int GetX() const;

		//Returns the y position of where the event occured
		int GetY() const;
	
	private:
		CComponent* mSource;
		Type mType;
		int mX;
		int mY;
	};
}