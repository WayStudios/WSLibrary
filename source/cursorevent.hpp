/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef CURSOREVENT_HEADER
#define CURSOREVENT_HEADER

#include <inputevent.hpp>
#include <vector2.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXPORT CursorEvent:public InputEvent
{
	CursorEvent(integer, integer);
	CursorEvent(const Vector2&);
	~CursorEvent();

	Vector2 Coordinate;

	UNCOPYABLE(CursorEvent)
};

END_WS_NAMESPACE

END_HEADER

#endif
