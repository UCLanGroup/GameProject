#include "KeyBinds.h"

tle::EKeyCode KeyBinds::Up = tle::EKeyCode::Key_Up;
tle::EKeyCode KeyBinds::Down = tle::EKeyCode::Key_Down;
tle::EKeyCode KeyBinds::Left = tle::EKeyCode::Key_Left;
tle::EKeyCode KeyBinds::Right = tle::EKeyCode::Key_Right;
tle::EKeyCode KeyBinds::Fire = tle::EKeyCode::Key_Space;

//Returns true if the key is used by any of the keybinds
bool KeyBinds::IsKeyBinded(tle::EKeyCode key)
{
	if (key == Up) return true;
	if (key == Down) return true;
	if (key == Left) return true;
	if (key == Right) return true;
	if (key == Fire) return true;
	return false;
}

//Returns true if the key is allowed to be binded
bool KeyBinds::IsKeyBindable(tle::EKeyCode key)
{
	int keyCode = static_cast<int>(key);
	//Mouse keys
	if (0x01 <= keyCode && keyCode <= 0x06) return true;
	//Space bar
	else if (0x20 == keyCode) return true;
	//Arrow keys
	else if (0x25 <= keyCode && keyCode <= 0x28) return true;
	//Number keys
	else if (0x30 <= keyCode && keyCode <= 0x39) return true;
	//Letters
	else if (0x41 <= keyCode && keyCode <= 0x5A) return true;
	//Numpad
	else if (0x60 <= keyCode && keyCode <= 0x6F) return true;

	//Unknow invalid key
	return false;
}

std::string KeyBinds::ToString(tle::EKeyCode key)
{
	int code = static_cast<int>(key);

	switch (code)
	{
	case 0x01: return "Left Mouse Button";
	case 0x02: return "Right Mouse Button";
	case 0x04: return "Middle Mouse Button";
	case 0x20: return "Space";
	case 0x25: return "Left Arrow";
	case 0x26: return "Up Arrow";
	case 0x27: return "Right Arrow";
	case 0x28: return "Down Arrow";
	case 0x30: return "0";
	case 0x31: return "1";
	case 0x32: return "2";
	case 0x33: return "3";
	case 0x34: return "4";
	case 0x35: return "5";
	case 0x36: return "6";
	case 0x37: return "7";
	case 0x38: return "8";
	case 0x39: return "9";
	case 0x41: return "A";
	case 0x42: return "B";
	case 0x43: return "C";
	case 0x44: return "D";
	case 0x45: return "E";
	case 0x46: return "F";
	case 0x47: return "G";
	case 0x48: return "H";
	case 0x49: return "I";
	case 0x4A: return "J";
	case 0x4B: return "K";
	case 0x4C: return "L";
	case 0x4D: return "M";
	case 0x4E: return "N";
	case 0x4F: return "O";
	case 0x50: return "P";
	case 0x51: return "Q";
	case 0x52: return "R";
	case 0x53: return "S";
	case 0x54: return "T";
	case 0x55: return "U";
	case 0x56: return "V";
	case 0x57: return "W";
	case 0x58: return "X";
	case 0x59: return "Y";
	case 0x5A: return "Z";
	case 0x60: return "Num 0";  
	case 0x61: return "Num 1";  
	case 0x62: return "Num 2";  
	case 0x63: return "Num 3";  
	case 0x64: return "Num 4";  
	case 0x65: return "Num 5";  
	case 0x66: return "Num 6";  
	case 0x67: return "Num 7";  
	case 0x68: return "Num 8";  
	case 0x69: return "Num 9";  
	case 0x6A: return "Num *";
	case 0x6B: return "Num +";
	case 0x6C: return "Num Enter";
	case 0x6D: return "Num -";  
	case 0x6E: return "Num .";
	case 0x6F: return "Num /";
	default: return "";
	}
}