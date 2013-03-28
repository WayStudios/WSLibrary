/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <slot.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

Slot::Slot(const String& STR, Object* OBJ) : master(OBJ), slotIdentity(STR) {
}

Slot::~Slot() {
}

Object* Slot::host() const {
    return master;
}

const String& Slot::identity() const {
    return slotIdentity;
}

Vector<Signal*>& Slot::connections() {
    return signVector;
}

void Slot::call(const SharedPointer<SignalSlotArgument>&) {
}

END_SOURCECODE
