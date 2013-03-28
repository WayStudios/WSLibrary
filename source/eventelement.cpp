/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <eventelement.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

EventElement::EventElement(Event* E, Object* R, Object* S) : event(E), receiver(R), sender(S) {
}

EventElement::EventElement(const EventElement& REF) : event(REF.event), receiver(REF.receiver), sender(REF.sender) {
}

EventElement::~EventElement() {
}

EventElement& EventElement::operator =(const EventElement& REF) {
	event = REF.event;
    receiver = REF.receiver;
    sender = REF.sender;
    return *this;
}

BOOLEAN EventElement::operator ==(const EventElement& REF) const {
	return event == REF.event && receiver == REF.receiver && sender == REF.sender;
}

BOOLEAN EventElement::operator !=(const EventElement& REF) const {
	return event != REF.event || receiver != REF.receiver || sender != REF.sender;
}

END_SOURCECODE
