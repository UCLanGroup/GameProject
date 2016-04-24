#pragma once
#include <functional>
#include <vector>
#include "Globals.h"

class CCheatManager
{
public:
	using CheatFunction_t = std::function<void()>;
	using KeyStream = std::vector<tle::EKeyCode>;
	void Register(std::string keystream, CheatFunction_t fn);
	void Update();

private:

	struct SCheat
	{
		size_t currentIndex;
		KeyStream bytes;
		CheatFunction_t fn;
	};

	using Cheat_ptr = std::unique_ptr<SCheat>;

	std::vector<Cheat_ptr> mCheats;
};
