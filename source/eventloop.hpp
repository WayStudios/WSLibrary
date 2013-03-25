/*******************************************************************************
 * WayStudio Library
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

    boolean PostEvent(Event*, Object*, Object*);

    boolean IsActive() const;

    void Enter();
    void Exit();
protected:
    EventQueue* GetEventQueue() const;
    void SetEventQueue(EventQueue*);

    EventDispatcher* GetEventDispatcher() const;
    void SetEventDispatcher(EventDispatcher*);

    virtual void Iteration();
};

END_WS_NAMESPACE

END_HEADER

#endif
