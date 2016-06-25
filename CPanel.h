#pragma once
#include "CContainer.h"

namespace tle_ui
{
	//Panel container organises the child components either veritcally or horizontally
	class CPanel : public CContainer
	{
	private:
		//Returns an interator to the next focusable component
		std::list<CComponent*>::iterator FindNextFocusableComponent();

		//Returns an interator to the previous focusable component
		std::list<CComponent*>::reverse_iterator FindPreviousFocusableComponent();

	public:
		//Creates a panel with vertical orientation
		CPanel();

		//Creates a panel with the given orientation
		CPanel(Orientation orientation);

		//Resizes the component based on child components
		virtual void Resize();

		//Passes focus to the next component to the right
		virtual void PassFocusRight();

		//Passes focus to the next component to the left
		virtual void PassFocusLeft();

		//Passes focus to the next component to the up
		virtual void PassFocusUp();

		//Passes focus to the next component to the down
		virtual void PassFocusDown();
	};
}