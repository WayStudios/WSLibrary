/*******************************************************************************
 * WayStudio GUI Library
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
	ResizeEvent(integer, integer);
	ResizeEvent(const Rectangle&);
	~ResizeEvent();

	const Rectangle Size;

	UNCOPYABLE(ResizeEvent)
};

END_WS_NAMESPACE

END_HEADER

#endif
