/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <signal.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

Signal::Signal(const String& STR, Object* OBJ) : master(OBJ), signIdentity(STR) {
}

Signal::~Signal() {
}

Object* Signal::host() const {
    return master;
}

const String& Signal::identity() const {
    return signIdentity;
}

Vector<Slot*>& Signal::connections() {
    return slotVector;
}

void Signal::emit(const SharedPointer<SignalSlotArgument>&) {
}

END_SOURCECODE
