/*******************************************************************************
 * Way Studios Library
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

BOOLEAN Object::exist(Object* P) {
	Meta* P_META=Meta::Pool.find(P);
	if(P_META)
		return true;
    return false;
}

Object::ObjectImplementation::ObjectImplementation(Object* OBJ):meta(OBJ) {}

Object::ObjectImplementation::~ObjectImplementation() {}

void Object::ObjectImplementation::initialize(const String& STR, Object* MASTER) {
	meta.thread = Thread::current();
	meta.master = MASTER;
	meta.identity = STR;
	if(meta.master)
	{
		Meta* P = Meta::Pool.find(meta.master);
		if(P)
		{
			P->children.append(meta.handle);
		}
	}
}

void Object::ObjectImplementation::destroy() {
#if !defined(WITHOUT_SIGNALSLOT)
	SignalSlot::close(meta.handle);
	for (Map<String, Signal*>::Iterator ITER_SIGNMAP = meta.signalMap.begin(); ITER_SIGNMAP != meta.signalMap.end(); ++ITER_SIGNMAP)
		delete (*ITER_SIGNMAP).second;
	meta.signalMap.clear();
	for (Map<String, Slot*>::Iterator ITER_SLOTMAP = meta.slotMap.begin(); ITER_SLOTMAP != meta.slotMap.end(); ++ITER_SLOTMAP)
		delete (*ITER_SLOTMAP).second;
	meta.slotMap.clear();
#endif
	if(meta.master)
	{
		Meta* P = Meta::Pool.find(meta.master);
		if(P)
		{
			P->children.remove(meta.handle);
		}
	}
	if(!meta.children.empty())
	{
		for(List<Object*>::Iterator ITER = meta.children.begin(); ITER != meta.children.end(); ++ITER)
		{
			Meta* P=Meta::Pool.find(*ITER);
			if(P)
				P->master = 0;
		}
	}
}

Object* Object::ObjectImplementation::getMaster() const {
	return meta.master;
}

void Object::ObjectImplementation::setMaster(Object* MASTER) {
	if(meta.master)
	{
		Meta* P = Meta::Pool.find(meta.master);
		if(P)
		{
			P->children.remove(meta.handle);
		}
	}
	meta.master = MASTER;
	if(meta.master)
	{
		Meta* P = Meta::Pool.find(meta.master);
		if(P)
		{
			P->children.append(meta.handle);
		}
	}
}

Object::Object(Object* OBJ) : implementation(0) {
	implementation = new ObjectImplementation(this);
	if(implementation)
		implementation->initialize(String(), OBJ);
}

Object::Object(const String& STR, Object* OBJ) : implementation(0) {
	implementation = new ObjectImplementation(this);
	if(implementation)
		implementation->initialize(STR, OBJ);
}

Object::~Object() {
    if (implementation) {
		implementation->destroy();
        delete implementation;
    }
}

Object* Object::getMaster() const {
    if (implementation)
		return implementation->getMaster();
    return 0;
}

void Object::setMaster(Object* P_OBJ) {
    if (implementation)
		implementation->setMaster(P_OBJ);
}

const String& Object::getIdentity() const {
    return implementation->meta.identity;
}

void Object::setIdentity(const String& STR) {
    implementation->meta.identity = STR;
}

BOOLEAN Object::notifyEvent(Event* E, Object* R, Object* S) {
    if (E) {
        processEvent(E);
        return true;
    }
    return false;
}

BOOLEAN Object::sendEvent(Event* E, Object* R, Object* S) {
    if (Thread::current())
        return Thread::current()->sendEvent(E, R, S);
	else
		if(R)
			return R->notifyEvent(E, R, S);
    return false;
}

BOOLEAN Object::postEvent(Event* E, Object* R, Object* S) {
    if (Thread::current())
        return Thread::current()->postEvent(E, R, S);
    return false;
}

void Object::processEvent(Event* E) {
    if (E) {
#if !defined(WITHOUT_SIGNALSLOT)
        if (E->type == WS_SIGNALSLOTEVENT)
            processSignalSlotEvent(static_cast<SignalSlotEvent*> (E));
#endif
    }
}

#if !defined(WITHOUT_SIGNALSLOT)

void Object::processSignalSlotEvent(SignalSlotEvent* E) {
    if (E)
        SignalSlot::call(this, E->slotIdentity, E->argument);
}
#endif

END_SOURCECODE
