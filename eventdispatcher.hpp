/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef EVENTDISPATCHER_HEADER
#define	EVENTDISPATCHER_HEADER

#include <object.hpp>
#include <eventelement.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT EventDispatcher : public Object {
    UNCOPYABLE(EventDispatcher)
public:
    explicit EventDispatcher(Object* OBJ = 0);
    virtual ~EventDispatcher();
    //to do: host event and release mem after event finished
    virtual boolean Dispatch(Event*, Object*, Object*);
    virtual boolean Dispatch(const EventElement&);
};

END_WS_NAMESPACE

END_HEADER

#endif
