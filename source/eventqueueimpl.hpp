/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef EVENTQUEUEIMPLEMENTATION_HEADER
#define	EVENTQUEUEIMPLEMENTATION_HEADER

#include <eventqueue.hpp>
#include <allocator.hpp>
#include <queuenode.hpp>
#include <atomicinteger.hpp>
#include <mutex.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL EventQueue::EventQueueImplementation : public Allocator< QueueNode<EventQueue::TYPE> > {
    UNCOPYABLE(EventQueueImplementation)
public:
    EventQueueImplementation();
    ~EventQueueImplementation();

    SIZE total() const;
    BOOLEAN empty() const;
    void clear();
    void destroy();
    EventQueueImplementation* duplicate();

    void append(const EventQueue::TYPE&);
    void pop();

    AtomicInteger reference;
    Mutex mutex;
    QueueNode<EventQueue::TYPE>* head;
    QueueNode<EventQueue::TYPE>* tail;
};

END_WS_NAMESPACE

END_HEADER

#endif
