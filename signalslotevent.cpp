/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <signalslotevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

SignalSlotEvent::SignalSlotEvent(const String& STR_SIGN, const String& STR_SLOT, const SharedPointer<SignalSlotArgument>& REF_SP) : Event(WS_SIGNALSLOTEVENT), STR_Signal(STR_SIGN), STR_Slot(STR_SLOT), SP_Argument(REF_SP) {
}

SignalSlotEvent::~SignalSlotEvent() {
}

boolean SignalSlotEvent::operator ==(const SignalSlotEvent& REF) const {
    return STR_Signal == REF.STR_Signal && STR_Slot == REF.STR_Slot && SP_Argument == REF.SP_Argument;
}

boolean SignalSlotEvent::operator !=(const SignalSlotEvent& REF) const {
    return STR_Signal != REF.STR_Signal || STR_Slot != REF.STR_Slot || SP_Argument != REF.SP_Argument;
}

END_SOURCECODE
