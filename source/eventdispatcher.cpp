/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <eventdispatcher.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

EventDispatcher::EventDispatcher(Object* OBJ) : Object(OBJ) {
}

EventDispatcher::~EventDispatcher() {
}

BOOLEAN EventDispatcher::dispatch(Event* E, Object* R, Object* S) {
	if(R)
		return R->notifyEvent(E, R, S);
	return false;
}

BOOLEAN EventDispatcher::dispatch(const EventElement& REF) {
	return dispatch(REF.event, REF.receiver, REF.sender);
}

END_SOURCECODE
