/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <object.hpp>
#include <objectimpl.hpp>
#include <thread.hpp>
#include <vector.hpp>
#if !defined(WITHOUT_SIGNALSLOT)
#include <signal.hpp>
#include <slot.hpp>
#include <signalslot.hpp>
#include <signalslotevent.hpp>
#endif

BEGIN_SOURCECODE

USING_WS_NAMESPACE

boolean Object::Exist(Object*) {
    return false;
}

Object::ObjectImplementation::ObjectImplementation(const String& STR, Object* OBJ) : OBJMeta(STR, OBJ) {
}

Object::ObjectImplementation::~ObjectImplementation() {
}

Object::Object(Object* OBJ) : Implementation(0) {
    Implementation = new ObjectImplementation(String("WS::Object"), this);
    if (Implementation)
        Implementation->OBJMeta.Master = OBJ;
    EmitSignal(Constructed, this);
}

Object::Object(const String& STR, Object* OBJ) : Implementation(0) {
    Implementation = new ObjectImplementation(STR, this);
    if (Implementation)
        Implementation->OBJMeta.Master = OBJ;
    EmitSignal(Constructed, this);
}

Object::~Object() {
    if (Implementation) {
#if !defined(WITHOUT_SIGNALSLOT)
        EmitSignal(Destroyed, this);
        SignalSlot::Close(this);
        for (Map<String, Signal*>::Iterator ITER_SIGNMAP = Implementation->OBJMeta.SignalMap.Begin(); ITER_SIGNMAP != Implementation->OBJMeta.SignalMap.End(); ++ITER_SIGNMAP)
            delete (*ITER_SIGNMAP).Second;
        Implementation->OBJMeta.SignalMap.Clear();
        for (Map<String, Slot*>::Iterator ITER_SLOTMAP = Implementation->OBJMeta.SlotMap.Begin(); ITER_SLOTMAP != Implementation->OBJMeta.SlotMap.End(); ++ITER_SLOTMAP)
            delete (*ITER_SLOTMAP).Second;
        Implementation->OBJMeta.SlotMap.Clear();
#endif
        delete Implementation;
    }
}

Object* Object::GetMaster() const {
    if (Implementation)
        return Implementation->OBJMeta.Master;
    return 0;
}

void Object::SetMaster(Object* P_OBJ) {
    if (Implementation)
        Implementation->OBJMeta.Master = P_OBJ;
}

const String& Object::GetName() const {
    return Implementation->OBJMeta.Name;
}

void Object::SetName(const String& STR) {
    Implementation->OBJMeta.Name = STR;
}

boolean Object::NotifyEvent(Event* E, Object* R, Object* S) {
    if (E) {
        ProcessEvent(E);
        return true;
    }
    return false;
}

boolean Object::SendEvent(Event* E, Object* R, Object* S) {
    if (R)
        return R->NotifyEvent(E, R, S);
    return false;
}

boolean Object::PostEvent(Event* E, Object* R, Object* S) {
    if (Thread::Current())
        return Thread::Current()->PostEvent(E, R, S);
    return false;
}

void Object::ProcessEvent(Event* E) {
    if (E) {
#if !defined(WITHOUT_SIGNALSLOT)
        if (E->Type == WS_SIGNALSLOTEVENT)
            ProcessSignalSlotEvent(static_cast<SignalSlotEvent*> (E));
#endif
    }
}

#if !defined(WITHOUT_SIGNALSLOT)

void Object::ProcessSignalSlotEvent(SignalSlotEvent* E) {
    if (E)
        SignalSlot::Call(this, E->STR_Slot, E->SP_Argument);
}
#endif

END_SOURCECODE
