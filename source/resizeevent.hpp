/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef RESIZEEVENT_HEADER
#define RESIZEEVENT_HEADER

#include <guievent.hpp>
#include <rectangle.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXPORT ResizeEvent:public GUIEvent
{
	explicit ResizeEvent(INTEGER W = 0, INTEGER H = 0);
	~ResizeEvent();

	const UINTEGER width;
	const UINTEGER height;

	UNCOPYABLE(ResizeEvent)
};

END_WS_NAMESPACE

END_HEADER

#endif
