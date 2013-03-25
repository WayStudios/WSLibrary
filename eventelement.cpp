/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <eventelement.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

EventElement::EventElement(Event* E, Object* R, Object* S) : Content(E), Receiver(R), Sender(S) {
}

EventElement::EventElement(const EventElement& REF) : Content(REF.Content), Receiver(REF.Receiver), Sender(REF.Sender) {
}

EventElement::~EventElement() {
}

EventElement& EventElement::operator =(const EventElement& REF) {
    Content = REF.Content;
    Receiver = REF.Receiver;
    Sender = REF.Sender;
    return *this;
}

boolean EventElement::operator ==(const EventElement& REF) const {
    return Content == REF.Content && Receiver == REF.Receiver && Sender == REF.Sender;
}

boolean EventElement::operator !=(const EventElement& REF) const {
    return Content != REF.Content || Receiver != REF.Receiver || Sender != REF.Sender;
}

END_SOURCECODE
