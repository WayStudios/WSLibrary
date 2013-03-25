/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <moveevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

MoveEvent::MoveEvent(integer X, integer Y):GUIEvent(GUIEvent::MoveEvent), Coordinate(X, Y){}

MoveEvent::MoveEvent(const Vector2& VEC2):GUIEvent(GUIEvent::MoveEvent), Coordinate(VEC2){}

MoveEvent::~MoveEvent(){}

END_SOURCECODE
