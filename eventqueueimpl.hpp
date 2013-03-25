/*******************************************************************************
 * WayStudio Library
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

class LOCAL EventQueue::EventQueueImplementation : public Allocator< QueueNode<EventQueue::VALUE> > {
    UNCOPYABLE(EventQueueImplementation)
public:
    EventQueueImplementation();
    ~EventQueueImplementation();

    size Total() const;
    boolean Empty() const;
    void Clear();
    void Destroy();
    EventQueueImplementation* Duplicate();

    void Append(const EventQueue::VALUE&);
    void Pop();

    AtomicInteger Ref;
    Mutex MLock;
    QueueNode<EventQueue::VALUE>* QueB;
    QueueNode<EventQueue::VALUE>* QueE;
};

END_WS_NAMESPACE

END_HEADER

#endif
