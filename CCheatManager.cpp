#include "CCheatManager.h"

void CCheatManager::Register(std::string keystream, CheatFunction_t fn)
{
	KeyStream stream;

	// Static cast stream into TL-keys.
	for (size_t i = 0; i < keystream.size(); ++i)
		stream.emplace_back(static_cast<tle::EKeyCode>(keystream[i]));

	// Create a cheat entry.
	mCheats.push_back(Cheat_ptr(new SCheat{ 0, stream, fn }));
}

void CCheatManager::Update()
{
	for (auto& cheat : mCheats)
	{
		// Get the next character needed to increase the cheat.
		tle::EKeyCode key = cheat->bytes[cheat->currentIndex];
		bool keyStatus = gEngine->KeyHit(key);

		if (keyStatus)
		{
			// Increase the cheat index.
			cheat->currentIndex++;

			// If the entire cheat has been entered, reset it and call its callback.
			if (cheat->currentIndex >= cheat->bytes.size())
			{
				cheat->currentIndex = 0;
				cheat->fn();
			}

		}
		else if (gEngine->AnyKeyHit())
		{
			// If this cheat's key wasn't pressed in this loop,
			// cancel its index.
			cheat->currentIndex = 0;
		}
	}
}