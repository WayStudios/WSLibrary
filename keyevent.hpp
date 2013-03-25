/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef KEYEVENT_HEADER
#define KEYEVENT_HEADER

#include <inputevent.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXPORT KeyEvent:public InputEvent
{
	explicit KeyEvent(InputKey, boolean);
	~KeyEvent();

	boolean IsPressed() const;
	boolean IsReleased() const;

	const InputKey Key;
	const boolean Status;

	UNCOPYABLE(KeyEvent)
};

END_WS_NAMESPACE

END_HEADER

#endif
