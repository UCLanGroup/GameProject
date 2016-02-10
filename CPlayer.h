#pragma once

#include <TL-Engine.h>
#include "globals.h"

using namespace tle;

class CPlayer
{
private:
	IMesh* mesh;
	float mSpeed = 20.0f; // speed to move plane
	

public:
	IModel* model;

	void Init();

	void Move(float);

	~CPlayer();

protected:

};