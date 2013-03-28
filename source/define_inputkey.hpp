/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef DEFINE_INPUTKEY_HEADER
#define DEFINE_INPUTKEY_HEADER

namespace WS
{
	enum InputKey
	{
		Unknow,
//mouse buttons
		ButtonLeft,
		ButtonRight,
		ButtonMiddle,
//numeric keypad keys
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
//keyboard keys
		KeyHome,
		KeyEnd,
		KeyEnter,
		KeyDelete,
		KeyInsert,
		KeyBackspace,
		KeySpacebar,
		KeyCancel,
		KeyControl,
		KeyCommand,
		KeyWindows,
		KeyFunction,
		KeyAlt,
		KeyOption,
		KeyShift,
		KeyTable,
		KeyEscape,
	//page keys
		KeyPageUp,
		KeyPageDown,
	//arrows
		ArrowUp,
		ArrowDown,
		ArrowLeft,
		ArrowRight,
	//numbers
		Key1 = 0x30,
		Key2 = 0x31,
		Key3 = 0x32,
		Key4 = 0x33,
		Key5 = 0x34,
		Key6 = 0x35,
		Key7 = 0x36,
		Key8 = 0x37,
		Key9 = 0x38,
		Key0 = 0x39,
	//letters
		KeyA = 0x41,
		KeyB = 0x42,
		KeyC = 0x43,
		KeyD = 0x44,
		KeyE = 0x45,
		KeyF = 0x46,
		KeyG = 0x47,
		KeyH = 0x48,
		KeyI = 0x49,
		KeyJ = 0x4A,
		KeyK = 0x4B,
		KeyL = 0x4C,
		KeyM = 0x4D,
		KeyN = 0x4E,
		KeyO = 0x4F,
		KeyP = 0x50,
		KeyQ = 0x51,
		KeyR = 0x52,
		KeyS = 0x53,
		KeyT = 0x54,
		KeyU = 0x55,
		KeyV = 0x56,
		KeyW = 0x57,
		KeyX = 0x58,
		KeyY = 0x59,
		KeyZ = 0x5A,
//function keys
		Function1,
		Function2,
		Function3,
		Function4,
		Function5,
		Function6,
		Function7,
		Function8,
		Function9,
		Function10,
		Function11,
		Function12,
//custom
		Custom
	};
};

#endif
