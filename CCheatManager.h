#pragma once
#include <functional>
#include <vector>
#include "Globals.h"

class CCheatManager
{
public:

	using CheatFunction_t = std::function<void()>;
	using KeyStream = std::vector<tle::EKeyCode>;

	struct SCheat
	{
		std::size_t      currentIndex;
		KeyStream        bytes;
		std::string      description;
		CheatFunction_t  fn;
	};

	// Registers a new cheat. Keystream should be in capital letters A-Z. 
	void Register(std::string keystream, std::string description, CheatFunction_t fn);
	
	// Processes key presses.
	void Update();

	SCheat* GetRecentlyActivated();

private:

	using Cheat_ptr = std::unique_ptr<SCheat>;
	std::vector<Cheat_ptr> mCheats;

	SCheat* mRecent = nullptr;
};

inline CCheatManager::SCheat* CCheatManager::GetRecentlyActivated()
{
	SCheat* result;
	result = mRecent;
	mRecent = nullptr;

	return result;
}