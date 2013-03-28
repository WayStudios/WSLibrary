/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <moveevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

MoveEvent::MoveEvent(INTEGER X, INTEGER Y):GUIEvent(GUIEvent::MoveEvent), coordinate(X, Y){}

MoveEvent::MoveEvent(const Vector2& VEC2):GUIEvent(GUIEvent::MoveEvent), coordinate(VEC2){}

MoveEvent::~MoveEvent(){}

END_SOURCECODE
