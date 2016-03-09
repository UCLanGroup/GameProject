#pragma once
#include "IUsings.h"

namespace tle
{
	class IAnimation
	{
	public:
		virtual void Run() = 0;
		virtual void Pause() = 0;
		virtual void Reset() = 0;

		virtual void SetX(float x) = 0;
		virtual void SetY(float y) = 0;
		virtual void SetZ(float z) = 0;

		virtual void SetPosition(const tlx::CVector3& pos) = 0;

		virtual float GetX() = 0;
		virtual float GetY() = 0;
		virtual float GetZ() = 0;

		virtual tlx::CVector3 GetPosition() = 0;

		virtual bool IsPaused() = 0;
		virtual bool IsLooped() = 0;
		virtual bool HasEnded() = 0;

		virtual void MoveX(float xMovement) = 0;
		virtual void MoveY(float yMovement) = 0;
		virtual void MoveZ(float zMovement) = 0;
		virtual void Move(const tlx::CVector3& movement) = 0;

		virtual ~IAnimation() {}
	};
}