/*******************************************************************************
 * Way Studios Library
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

    EventElement& operator =(const EventElement&);

    BOOLEAN operator ==(const EventElement&) const;
    BOOLEAN operator !=(const EventElement&) const;

    Event* event;
    Object* receiver;
    Object* sender;
};

END_WS_NAMESPACE

END_HEADER

#endif
