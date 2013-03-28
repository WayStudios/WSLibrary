/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <signalslotevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

SignalSlotEvent::SignalSlotEvent(const String& STR_SIGN, const String& STR_SLOT, const SharedPointer<SignalSlotArgument>& REF_SP) : Event(WS_SIGNALSLOTEVENT), signalIdentity(STR_SIGN), slotIdentity(STR_SLOT), argument(REF_SP) {
}

SignalSlotEvent::~SignalSlotEvent() {
}

BOOLEAN SignalSlotEvent::operator ==(const SignalSlotEvent& REF) const {
    return signalIdentity == REF.signalIdentity && slotIdentity == REF.slotIdentity && argument == REF.argument;
}

BOOLEAN SignalSlotEvent::operator !=(const SignalSlotEvent& REF) const {
    return signalIdentity != REF.signalIdentity || slotIdentity != REF.slotIdentity || argument != REF.argument;
}

END_SOURCECODE
