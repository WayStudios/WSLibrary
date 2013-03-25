/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SLOT_HEADER
#define	SLOT_HEADER

#include <global.hpp>
#include <string.hpp>
#include <vector.hpp>
#include <signalslotargument.hpp>
#include <sharedpointer.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class Object;
class Signal;

class EXPORT Slot {
    UNCOPYABLE(Slot)

    Object* Master;
    String SlotName;
    Vector<Signal*> SignVector;
public:
    explicit Slot(const String&, Object*);
    virtual ~Slot() = 0;

    Object* Host() const;
    const String& Name() const;
    Vector<Signal*>& Connections();

    virtual void Call(const SharedPointer<SignalSlotArgument>&) = 0;
};

END_WS_NAMESPACE

END_HEADER

#include <slotimpl.hpp>

#endif
