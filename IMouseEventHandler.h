#pragma once
#include "CMouseEvent.h"

namespace tle_ui
{
	class IMouseEventHandler
	{
	public:
		//Handles events from the mouse being moved over a component
		virtual void MouseEnteredEvent(const CMouseEvent& mouseEvent) = 0;

		//Handles events from the mouse being moved off of a component
		virtual void MouseExittedEvent(const CMouseEvent& mouseEvent) = 0;

		//Handles events from the a component being clicked on
		virtual void MouseClickedEvent(const CMouseEvent& mouseEvent) = 0;

		//Handles events from the mouse being moved while over a component
		virtual void MouseMovedEvent(const CMouseEvent& mouseEvent) = 0;
	};
}