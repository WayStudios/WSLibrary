/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <guievent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

GUIEvent::GUIEvent(GUIEvent::GUIEventType T) : Event(WS_GUIEVENT), EventType(T){}

GUIEvent::~GUIEvent(){}

END_SOURCECODE
