/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef INPUTEVENT_HEADER
#define INPUTEVENT_HEADER

#include <guievent.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXPORT InputEvent:public GUIEvent
{
	enum InputDevice
	{
		Unknow,
		Key,
		Cursor
	};

	InputEvent(InputDevice T=InputEvent::Unknow);
	virtual ~InputEvent();

	const InputDevice device;

	UNCOPYABLE(InputEvent)
};

END_WS_NAMESPACE

END_HEADER

#endif
