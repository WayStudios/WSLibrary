/*******************************************************************************
 * WayStudio Library
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
    signal :
    DECLARE_SIGNAL(Object*, Object, Constructed)
    DECLARE_SIGNAL(Object*, Object, Destroyed)
public:
    explicit Object(Object* OBJ = 0);
    explicit Object(const String&, Object* OBJ = 0);
    virtual ~Object();

    Object* GetMaster() const;
    void SetMaster(Object*);

    const String& GetName() const;
    void SetName(const String&);

    virtual boolean NotifyEvent(Event*, Object* R = 0, Object* S = 0);
    virtual boolean SendEvent(Event*, Object* R = 0, Object* S = 0);
    virtual boolean PostEvent(Event*, Object* R = 0, Object* S = 0);

    static boolean Exist(Object*);
protected:
    virtual void ProcessEvent(Event*);
#if !defined(WITHOUT_SIGNALSLOT)
    virtual void ProcessSignalSlotEvent(SignalSlotEvent*);
#endif
};

END_WS_NAMESPACE

END_HEADER

#endif
