/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <cursorevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

CursorEvent::CursorEvent(integer X, integer Y):InputEvent(InputEvent::Cursor), Coordinate(X, Y){}

CursorEvent::CursorEvent(const Vector2& VEC2):InputEvent(InputEvent::Cursor), Coordinate(VEC2){}

CursorEvent::~CursorEvent(){}

END_SOURCECODE
