/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <signal.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

Signal::Signal(const String& STR, Object* OBJ) : Master(OBJ), SignName(STR) {
}

Signal::~Signal() {
}

Object* Signal::Host() const {
    return Master;
}

const String& Signal::Name() const {
    return SignName;
}

Vector<Slot*>& Signal::Connections() {
    return SlotVector;
}

void Signal::Emit(const SharedPointer<SignalSlotArgument>&) {
}

END_SOURCECODE
