/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <cursorevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

CursorEvent::CursorEvent(INTEGER V_X, INTEGER V_Y) : InputEvent(InputEvent::Cursor), x(V_X), y(V_Y) {}

CursorEvent::~CursorEvent(){}

END_SOURCECODE
