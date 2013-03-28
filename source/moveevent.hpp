/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef MOVEEVENT_HEADER
#define MOVEEVENT_HEADER

#include <guievent.hpp>
#include <vector2.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXPORT MoveEvent:public GUIEvent
{
	MoveEvent(INTEGER, INTEGER);
	MoveEvent(const Vector2&);
	~MoveEvent();

	const Vector2 coordinate;

	UNCOPYABLE(MoveEvent)
};

END_WS_NAMESPACE

END_HEADER

#endif
