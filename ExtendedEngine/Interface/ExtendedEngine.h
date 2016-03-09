#pragma once

#define WIN32_LEAN_AND_MEAN // Minimise windows includes

#include "IEngine.h"

namespace tle
{
	IEngine* NewEngine();
}