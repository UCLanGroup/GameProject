#include "CContainer.h"

namespace tle_ui
{
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

	//Adds a component as a child
	//Warning: If the component has already been added somewhere within the component hierarchy then expect serious errors
	void CContainer::Add(CComponent* component)
	{
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
}
