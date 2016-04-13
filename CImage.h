#pragma once
#include "ExtendedEngine.h"
#include "CComponent.h"

namespace tle_ui
{
	//Contains a sprite
	class CImage final : public CComponent
	{
	private:
		tle::ISprite* mpSprite = 0;

		int mImageX = 0;
		int mImageY = 0;

		int mImageWidth = 0;
		int mImageHeight = 0;

	public:
		CImage(tle::ISprite* sprite, int width, int height);

		//Resizes the component to fit the text
		virtual void Resize();

		//Update function for manual updating of content
		virtual void Update(float delta);

		//Called before draw call to the engine
		//Called by parent component's Draw function
		virtual void Draw();

		//Sets the internal sprite
		void SetSprite(tle::ISprite* sprite);

		//Sets the x position of the UI object
		virtual void SetX(int x) final;

		//Sets the y position of the UI object
		virtual void SetY(int y) final;

		//Sets the x and y position of the UI object
		virtual void SetPosition(int x, int y) final;

		//Returns the internal sprite
		tle::ISprite* GetSprite();
	};
}