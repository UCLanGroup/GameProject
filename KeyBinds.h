#pragma once
#include <Input.h>
#include <string>

class KeyBinds
{
public:
	static tle::EKeyCode Up;
	static tle::EKeyCode Down;
	static tle::EKeyCode Left;
	static tle::EKeyCode Right;
	static tle::EKeyCode Fire;

	//Returns true if the key is used by any of the keybinds
	static bool IsKeyBinded(tle::EKeyCode key);

	//Returns true if the key is allowed to be binded
	static bool IsKeyBindable(tle::EKeyCode key);

	//Converts the keycode enum to a string
	static std::string ToString(tle::EKeyCode key);
};