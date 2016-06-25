#include "CPanel.h"
#include <algorithm>

namespace tle_ui
{
	//Creates a panel with vertical orientation
	CPanel::CPanel()
	{
		mHasFocus = true;
		mOrientation = Orientation::Vertical;
	}

	//Creates a panel with the given orientation
	CPanel::CPanel(Orientation orientation)
	{
		mHasFocus = true;
		mOrientation = orientation;
	}

	//Resizes the component based on chield components
	void CPanel::Resize()
	{
		int usedSpace = mMargin;
		int totalWidth = 0;
		int totalHeight = 0;

		//Calc total area of components
		for (CComponent* component : mComponents)
		{
			component->Resize();
			if (mOrientation == Orientation::Vertical)
			{
				totalWidth = std::max(totalWidth, component->GetWidth());
				totalHeight += component->GetHeight();
			}
			else //Horizontal
			{
				totalWidth += component->GetWidth();
				totalHeight = std::max(totalHeight, component->GetHeight());
			}
		}

		//Recalc the width
		if (mWidth == kAutoScale)
		{
			mCalcedWidth = mMargin * 2 + totalWidth;
		}
		else
		{
			mCalcedWidth = mWidth;
		}

		//Recalc the height
		if (mHeight == kAutoScale)
		{
			mCalcedHeight = mMargin * 2 + totalHeight;
		}
		else
		{
			mCalcedHeight = mHeight;
		}

		//Place things vertically
		if (mOrientation == Orientation::Vertical)
		{
			for (CComponent* component : mComponents)
			{
				//x positions
				switch (mHorizontal)
				{
				case Right:
					component->SetX(mX + mCalcedWidth - mMargin - component->GetWidth());
					break;

				case Left:
					component->SetX(mX + mMargin);
					break;

				case Center:
					component->SetX(mX + (mCalcedWidth - component->GetWidth()) / 2);
					break;

				default:
					//Unsupported alignment type
					break;

				}

				//y positions
				switch (mVertical)
				{
				case Top:
					component->SetY(mY + usedSpace);
					usedSpace += component->GetHeight();
					break;

				case Bottom:
					usedSpace += component->GetHeight();
					component->SetY(mY + mCalcedHeight - usedSpace);
					break;

				case Center:
					component->SetY(mY + usedSpace + ((mCalcedHeight - totalHeight) / 2));
					usedSpace += component->GetHeight();
					break;

				default:
					//Unsupported alignment type
					break;

				}
			}
		}
		else //Horizontal
		{
			for (CComponent* component : mComponents)
			{
				//x positions
				switch (mHorizontal)
				{
				case Right:
					usedSpace += component->GetWidth();
					component->SetX(mX + mCalcedWidth - usedSpace);
					break;

				case Left:
					component->SetX(mX + usedSpace);
					usedSpace += component->GetWidth();
					break;

				case Center:
					component->SetX(mX + usedSpace + ((mCalcedWidth - totalWidth) / 2));
					usedSpace += component->GetWidth();
					break;

				default:
					//Unsupported alignment type
					break;

				}

				//y positions
				switch (mVertical)
				{
				case Top:
					component->SetY(mY + mCalcedHeight - mMargin - component->GetHeight());
					break;

				case Bottom:
					component->SetY(mY + mMargin);
					break;

				case Center:
					component->SetY(mY + (mCalcedHeight - component->GetHeight()) / 2);
					break;

				default:
					//Unsupported alignment type
					break;

				}
			}
		}
	}

	//Returns an iterator to the next focusable component
	//Returns the end iterator if there is no next component
	std::list<CComponent*>::iterator CPanel::FindNextFocusableComponent()
	{
		//Find first component in focus
		auto it = mComponents.begin();
		while ((it != mComponents.end()) && !(*it)->HasFocus())
		{
			++it;
		}

		//Check if component found
		if (it == mComponents.end())
		{
			//If no focused component found then select the first focusable target
			for (it = mComponents.begin(); it != mComponents.end(); ++it)
			{
				if ((*it)->IsFocusable())
				{
					(*it)->SetFocus(true);
					return it;
				}
			}
		}
		else
		{
			//Remove focus from previous
			(*it)->SetFocus(false);
			++it;

			//Find next focusable target
			for (; it != mComponents.end(); ++it)
			{
				if ((*it)->IsFocusable())
				{
					(*it)->SetFocus(true);
					return it;
				}
			}

			//Reached end of list without finding new target
			//If no parent then loop back to the start and select first focusable component
			if (!mpParent)
			{
				for (it = mComponents.begin(); it != mComponents.end(); ++it)
				{
					if ((*it)->IsFocusable())
					{
						(*it)->SetFocus(true);
						return it;
					}
				}
			}
		}

		//No new focusable target was found
		return it;
	}

	//Returns an iterator to the next focusable component
	//Returns the end iterator if there is no next component
	std::list<CComponent*>::reverse_iterator CPanel::FindPreviousFocusableComponent()
	{
		//Find first component in focus
		auto it = mComponents.rbegin();
		while ((it != mComponents.rend()) && !(*it)->HasFocus())
		{
			++it;
		}

		//Check if component found
		if (it == mComponents.rend())
		{
			//If no focused component found then select the first focusable target
			for (it = mComponents.rbegin(); it != mComponents.rend(); ++it)
			{
				if ((*it)->IsFocusable())
				{
					(*it)->SetFocus(true);
					return it;
				}
			}
		}
		else
		{
			//Remove focus from previous
			(*it)->SetFocus(false);
			++it;

			//Find next focusable target
			for (; it != mComponents.rend(); ++it)
			{
				if ((*it)->IsFocusable())
				{
					(*it)->SetFocus(true);
					return it;
				}
			}

			//Reached end of list without finding new target
			//If no parent then loop back to the start and select first focusable component
			if (!mpParent)
			{
				for (it = mComponents.rbegin(); it != mComponents.rend(); ++it)
				{
					if ((*it)->IsFocusable())
					{
						(*it)->SetFocus(true);
						return it;
					}
				}
			}
		}

		//No new focusable target was found
		return it;
	}

	//Passes focus to the next component to the right
	void CPanel::PassFocusRight()
	{
		//Attempt to select new component
		if (mOrientation == Orientation::Horizontal || !HasFocusedComponent())
		{
			auto it = FindNextFocusableComponent();
			if (it != mComponents.end())
			{
				(*it)->PassFocusRight();
				return;
			}
		}

		//No new component was found
		if (mpParent)
		{
			mpParent->PassFocusRight();
		}
	}

	//Passes focus to the next component to the left
	void CPanel::PassFocusLeft()
	{
		//Attempt to select new component
		if (mOrientation == Orientation::Horizontal || !HasFocusedComponent())
		{
			auto it = FindPreviousFocusableComponent();
			if (it != mComponents.rend())
			{
				(*it)->PassFocusLeft();
				return;
			}
		}

		//No new component was found
		if (mpParent)
		{
			mpParent->PassFocusLeft();
		}
	}

	//Passes focus to the next component to the up
	void CPanel::PassFocusUp()
	{
		//Attempt to select new component
		if (mOrientation == Orientation::Vertical || !HasFocusedComponent())
		{
			auto it = FindPreviousFocusableComponent();
			if (it != mComponents.rend())
			{
				(*it)->PassFocusUp();
				return;
			}
		}

		//No new component was found
		if (mpParent)
		{
			mpParent->PassFocusUp();
		}
	}

	//Passes focus to the next component to the down
	void CPanel::PassFocusDown()
	{
		//Attempt to select new component
		if (mOrientation == Orientation::Vertical || !HasFocusedComponent())
		{
			auto it = FindNextFocusableComponent();
			if (it != mComponents.end())
			{
				(*it)->PassFocusDown();
				return;
			}
		}
		
		//No new component was found
		if (mpParent)
		{
			mpParent->PassFocusDown();
		}
	}
}