/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef KEYEVENT_HEADER
#define KEYEVENT_HEADER

#include <inputevent.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXPORT KeyEvent:public InputEvent
{
	explicit KeyEvent(InputKey, BOOLEAN);
	~KeyEvent();

	BOOLEAN isPressed() const;
	BOOLEAN isReleased() const;

	const InputKey key;
	const BOOLEAN status;

	UNCOPYABLE(KeyEvent)
};

END_WS_NAMESPACE

END_HEADER

#endif
