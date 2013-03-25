/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef EVENTELEMENT_HEADER
#define	EVENTELEMENT_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct Event;
class Object;

struct EXPORT EventElement {
    explicit EventElement(Event*, Object*, Object*);
    EventElement(const EventElement&);
    ~EventElement();

    EventElement& operator=(const EventElement&);

    boolean operator==(const EventElement&) const;
    boolean operator!=(const EventElement&) const;

    Event* Content;
    Object* Receiver;
    Object* Sender;
};

END_WS_NAMESPACE

END_HEADER

#endif
