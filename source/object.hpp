/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef OBJECT_HEADER
#define	OBJECT_HEADER

#include <global.hpp>
#include <string.hpp>
#if !defined(WITHOUT_SIGNALSLOT)
#include <signalslot.hpp>
#endif

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct Event;
#if !defined(WITHOUT_SIGNALSLOT)
struct SignalSlotEvent;
#endif

class EXPORT Object {
    DECLARE_IMPLEMENTATION(Object)
    UNCOPYABLE(Object)
signal:
	DECLARE_SIGNAL(Object*, Object, masterChanged)
public:
    explicit Object(Object* OBJ = 0);
    explicit Object(const String&, Object* OBJ = 0);
    virtual ~Object();

    Object* getMaster() const;
    void setMaster(Object*);

    const String& getIdentity() const;
    void setIdentity(const String&);

    virtual BOOLEAN notifyEvent(Event*, Object* R = 0, Object* S = 0);
    virtual BOOLEAN sendEvent(Event*, Object* R = 0, Object* S = 0);
    virtual BOOLEAN postEvent(Event*, Object* R = 0, Object* S = 0);

    static BOOLEAN exist(Object*);
protected:
    virtual void processEvent(Event*);
#if !defined(WITHOUT_SIGNALSLOT)
    virtual void processSignalSlotEvent(SignalSlotEvent*);
#endif
};

END_WS_NAMESPACE

END_HEADER

#endif
