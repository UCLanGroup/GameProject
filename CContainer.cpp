#include "CContainer.h"

namespace tle_ui
{
	//Returns true if a sub component has focus
	bool CContainer::HasFocusedComponent()
	{
		for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
		{
			if ((*it)->HasFocus())
			{
				return true;
			}
		}
		return false;
	}

	//Update function for manual updating of content
	void CContainer::Update(float delta)
	{
		for (CComponent* component : mComponents)
		{
			component->Update(delta);
		}
	}

	//Called before draw call to the engine
	//Called by parent component's Draw function
	void CContainer::Draw()
	{
		for (CComponent* component : mComponents)
		{
			component->Draw();
		}
	}

	//Checks if the mouse event location is within the container
	//If so triggers the event call to the child components
	void CContainer::CheckEvent(CMouseEvent& mouseEvent)
	{
		for (CComponent* component : mComponents)
		{
			component->CheckEvent(mouseEvent);
		}
	}

	//Key event handler
	void CContainer::KeyEvent(tle::EKeyCode keyCode)
	{
		//Pass down the key event
		for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
		{
			if ((*it)->HasFocus())
			{
				(*it)->KeyEvent(keyCode);
				return;
			}
		}

		//Give the next component focus if none have focus
		if (keyCode == tle::EKeyCode::Key_Up)
		{
			PassFocusUp();
		}
		else if (keyCode == tle::EKeyCode::Key_Left)
		{
			PassFocusLeft();
		}
		else if (keyCode == tle::EKeyCode::Key_Down)
		{
			PassFocusDown();
		}
		else if (keyCode == tle::EKeyCode::Key_Right)
		{
			PassFocusRight();
		}
	}

	//Adds a component as a child
	//Warning: If the component has already been added somewhere within the component hierarchy then expect serious errors
	void CContainer::Add(CComponent* component)
	{
		component->SetParent(this);
		mComponents.push_back(component);
		Resize();
	}

	//Removes the child component
	void CContainer::Remove(CComponent* component)
	{
		for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
		{
			if ((*it) == component)
			{
				(*it)->SetParent(0); //Set the component's parent to null
				mComponents.erase(it);
				Resize();
				return;
			}
		}
	}

	//Sets the x position of the UI object
	void CContainer::SetX(int x)
	{
		int xDif = x - mX;

		for (CComponent* component : mComponents)
		{
			component->SetX(component->GetX() + xDif);
		}

		mX = x;
	}

	//Sets the y position of the UI object
	void CContainer::SetY(int y)
	{
		int yDif = y - mY;

		for (CComponent* component : mComponents)
		{
			component->SetY(component->GetY() + yDif);
		}

		mY = y;
	}

	//Sets the x and y position of the UI object
	void CContainer::SetPosition(int x, int y)
	{
		int xDif = x - mX;
		int yDif = y - mY;

		for (CComponent* component : mComponents)
		{
			component->SetX(component->GetX() + xDif);
			component->SetY(component->GetY() + yDif);
		}

		mX = x;
		mY = y;
	}

	/*******************************
		  Focus event handling
	********************************/

	//Return whether the component can be focused
	bool CContainer::IsFocusable()
	{
		for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
		{
			if ((*it)->IsFocusable())
			{
				return true;
			}
		}

		return false;
	}

	//Sets whether the component is now in focus
	void CContainer::SetFocus(bool hasFocus)
	{
		mHasFocus = hasFocus;

		//If focus is being removed, remove it from any sub components
		if (!hasFocus)
		{
			for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
			{
				if ((*it)->HasFocus())
				{
					(*it)->SetFocus(false);
				}
			}
		}
	}

	//Passes focus to the specific sub component
	void CContainer::PassFocusTo(CComponent* component)
	{
		for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
		{
			if ((*it) == component)
			{
				(*it)->SetFocus(true);
			}
			else
			{
				(*it)->SetFocus(false);
			}
		}

		if (mpParent)
		{
			mpParent->PassFocusTo(this);
		}
		else
		{
			SetFocus(true);
		}
	}

	//Passes focus to the next component to the right
	void CContainer::PassFocusRight()
	{

	}

	//Passes focus to the next component to the left
	void CContainer::PassFocusLeft()
	{

	}

	//Passes focus to the next component to the up
	void CContainer::PassFocusUp()
	{

	}

	//Passes focus to the next component to the down
	void CContainer::PassFocusDown()
	{

	}
}
