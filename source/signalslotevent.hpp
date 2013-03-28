/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SIGNALSLOTEVENT_HEADER
#define	SIGNALSLOTEVENT_HEADER

#include <event.hpp>
#include <string.hpp>
#include <sharedpointer.hpp>
#include <signalslotargument.hpp>

BEGIN_HEADER

#ifndef WS_SIGNALSLOTEVENT
#define WS_SIGNALSLOTEVENT 0x11
#endif

BEGIN_WS_NAMESPACE

struct EXPORT SignalSlotEvent : public Event {
    explicit SignalSlotEvent(const String&, const String&, const SharedPointer<SignalSlotArgument>&);
    ~SignalSlotEvent();

    BOOLEAN operator ==(const SignalSlotEvent&) const;
    BOOLEAN operator !=(const SignalSlotEvent&) const;

    String signalIdentity;
    String slotIdentity;
    SharedPointer<SignalSlotArgument> argument;

    UNCOPYABLE(SignalSlotEvent)
};

END_WS_NAMESPACE

END_HEADER

#endif
