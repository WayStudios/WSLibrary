/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SIGNAL_HEADER
#define	SIGNAL_HEADER

#include <global.hpp>
#include <string.hpp>
#include <vector.hpp>
#include <signalslotargument.hpp>
#include <sharedpointer.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class Object;
class Slot;

class EXPORT Signal {
    UNCOPYABLE(Signal)

    Object* Master;
    String SignName;
    Vector<Slot*> SlotVector;
public:
    explicit Signal(const String&, Object*);
    virtual ~Signal() = 0;

    Object* Host() const;
    const String& Name() const;
    Vector<Slot*>& Connections();

    virtual void Emit(const SharedPointer<SignalSlotArgument>&) = 0;
};

END_WS_NAMESPACE

END_HEADER

#include <signalimpl.hpp>

#endif
