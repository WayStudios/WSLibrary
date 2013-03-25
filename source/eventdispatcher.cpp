/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <eventdispatcher.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

EventDispatcher::EventDispatcher(Object* OBJ) : Object(OBJ) {
}

EventDispatcher::~EventDispatcher() {
}

boolean EventDispatcher::Dispatch(Event* E, Object* R, Object* S) {
    return SendEvent(E, R, S);
}

boolean EventDispatcher::Dispatch(const EventElement& REF) {
    return SendEvent(REF.Content, REF.Receiver, REF.Sender);
}

END_SOURCECODE
