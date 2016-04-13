#pragma once
#include "CContainer.h"

namespace tle_ui
{
	//Panel container organises the child components either veritcally or horizontally
	class CPanel : public CContainer
	{
	public:
		//Creates a panel with vertical orientation
		CPanel();

		//Creates a panel with the given orientation
		CPanel(Orientation orientation);

		//Resizes the component based on child components
		virtual void Resize();
	};
}