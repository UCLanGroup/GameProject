#pragma once
#include "CVector3.h"
#include <memory>
#include <vector>
#include <list>

namespace tle
{
	using tlx::CVector3;

	template<class T>
	using vector_ptr = std::vector<std::unique_ptr<T>>;

	template<class T>
	using list_ptr = std::list<std::unique_ptr<T>>;
}