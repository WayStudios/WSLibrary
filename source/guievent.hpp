/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef GUIEVENT_HEADER
#define GUIEVENT_HEADER

#include <event.hpp>

BEGIN_HEADER

#ifndef WS_GUIEVENT
#define WS_GUIEVENT 0x13
#endif

BEGIN_WS_NAMESPACE

struct EXPORT GUIEvent:public Event
{
	enum GUIEventType
	{
		Unknow,
		RenderEvent,
		MoveEvent,
		ResizeEvent,
		InputEvent
	};

	explicit GUIEvent(GUIEventType T=GUIEvent::Unknow);
	virtual ~GUIEvent();

	const GUIEventType EventType;

	UNCOPYABLE(GUIEvent)
};

END_WS_NAMESPACE

END_HEADER

#endif
