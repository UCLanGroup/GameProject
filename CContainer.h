#pragma once
#include "CComponent.h"

namespace tle_ui
{
	//Base container component, does not manage the memory of child components
	class CContainer : public CComponent
	{
	protected:
		//All the child components
		std::vector<CComponent*> mComponents;

	public:
		//Resizes the component based on child components
		virtual void Resize() = 0;

		//Update function for manual updating of content
		void Update(float delta) final;

		//Called before draw call to the engine
		//Called by parent component's Draw function
		void Draw() final;

		//Checks if the mouse event location is within the container
		//If so triggers the event call to the child components
		virtual void CheckEvent(CMouseEvent& mouseEvent) final;

		//Adds a component as a child
		void Add(CComponent* component);

		//Removes the child component
		void Remove(CComponent* component);

		//Sets the x position of the UI object
		virtual void SetX(int x) final;

		//Sets the y position of the UI object
		virtual void SetY(int y) final;

		//Sets the x and y position of the UI object
		virtual void SetPosition(int x, int y) final;
	};
}