/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef EVENTLOOP_HEADER
#define	EVENTLOOP_HEADER

#include <object.hpp>
#include <eventqueue.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EventDispatcher;

class EXPORT EventLoop : public Object {
    DECLARE_IMPLEMENTATION(EventLoop)
    UNCOPYABLE(EventLoop)
public:
    explicit EventLoop(EventQueue*, EventDispatcher*, Object* OBJ = 0);
    virtual ~EventLoop();

    BOOLEAN postEvent(Event*, Object* R, Object* S);
	BOOLEAN sendEvent(Event*, Object* R, Object* S);

    BOOLEAN isActive() const;

    void enter();
    void exit();

	void process(); //it will process events in the queue then return.
protected:
    EventQueue* getEventQueue() const;
    void setEventQueue(EventQueue*);

    EventDispatcher* getEventDispatcher() const;
    void setEventDispatcher(EventDispatcher*);

    virtual void iteration();
};

END_WS_NAMESPACE

END_HEADER

#endif
