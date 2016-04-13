#include "CPanel.h"
#include <algorithm>

namespace tle_ui
{
	//Creates a panel with vertical orientation
	CPanel::CPanel()
	{
		mOrientation = Orientation::Vertical;
	}

	//Creates a panel with the given orientation
	CPanel::CPanel(Orientation orientation)
	{
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
}