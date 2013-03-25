/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <slot.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

Slot::Slot(const String& STR, Object* OBJ) : Master(OBJ), SlotName(STR) {
}

Slot::~Slot() {
}

Object* Slot::Host() const {
    return Master;
}

const String& Slot::Name() const {
    return SlotName;
}

Vector<Signal*>& Slot::Connections() {
    return SignVector;
}

void Slot::Call(const SharedPointer<SignalSlotArgument>&) {
}

END_SOURCECODE
