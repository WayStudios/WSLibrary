/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <eventqueue.hpp>
#include <eventqueueimpl.hpp>
#include <scopedlock.hpp>
#include <event.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

EventQueue::EventQueueImplementation::EventQueueImplementation() : head(0), tail(0) {
}

EventQueue::EventQueueImplementation::~EventQueueImplementation() {
}

SIZE EventQueue::EventQueueImplementation::total() const {
    SIZE RET = 0;
    if (!empty()) {
        ScopedLock<Mutex> SL_MUTEX(const_cast<Mutex*> (&mutex));
        QueueNode<EventQueue::TYPE>* P_N = head;
        while (P_N) {
            ++RET;
            P_N = P_N->next;
        }
    }
    return RET;
}

BOOLEAN EventQueue::EventQueueImplementation::empty() const {
    return !head;
}

void EventQueue::EventQueueImplementation::clear() {
    if (!empty()) {
        ScopedLock<Mutex> SL_MUTEX(&mutex);
        while (!empty()) {
            QueueNode<EventQueue::TYPE>* P_N = head->next;
            destruct(head);
            deallocate(head);
            head = P_N;
            if (empty())
                tail = head = 0;
        }
    }
}

void EventQueue::EventQueueImplementation::destroy() {
    //destroy all appended events or aka delete Event*;
    if (!empty()) {
        ScopedLock<Mutex> SL_MUTEX(&mutex);
        while (!empty()) {
            QueueNode<EventQueue::TYPE>* P_N = head->next;
            delete (head->object.event);
            destruct(head);
            deallocate(head);
            head = P_N;
            if (empty())
                tail = head = 0;
        }
    }
}

EventQueue::EventQueueImplementation* EventQueue::EventQueueImplementation::duplicate() {
    ScopedLock<Mutex> SL_MUTEX(&mutex);
    EventQueueImplementation* N_IMPL = new EventQueueImplementation;
    if (N_IMPL) {
        if (!empty()) {
            QueueNode<EventQueue::TYPE>* P_ITER = head;
            while (P_ITER) {
                QueueNode<EventQueue::TYPE>* P_N = allocate(1);
                new(P_N) QueueNode<EventQueue::TYPE> (P_ITER->object, 0);
                if (N_IMPL->empty())
                    N_IMPL->tail = N_IMPL->head = P_N;
                else {
                    N_IMPL->tail->next = P_N;
                    N_IMPL->tail = P_N;
                }
                P_ITER = P_ITER->next;
            }
        }
        return N_IMPL;
    }
    return 0;
}

void EventQueue::EventQueueImplementation::append(const EventQueue::TYPE& REF) {
    ScopedLock<Mutex> SL_MUTEX(&mutex);
    QueueNode<EventQueue::TYPE>* P_N = allocate(1);
    new(P_N) QueueNode<EventQueue::TYPE>(REF, 0);
    if (empty())
        tail = head = P_N;
    else {
        tail->next = P_N;
        tail = P_N;
    }
}

void EventQueue::EventQueueImplementation::pop() {
    if (!empty()) {
        ScopedLock<Mutex> SL_MUTEX(&mutex);
        QueueNode<EventQueue::TYPE>* P_N = head->next;
        destruct(head);
        deallocate(head);
        head = P_N;
        if (empty())
            tail = head = 0;
    }
}

EventQueue::EventQueue() : implementation(0) {
    implementation = new EventQueueImplementation;
    if (implementation)
        ++(implementation->reference);
}

EventQueue::EventQueue(const EventQueue& REF) : implementation(REF.implementation) {
    if (implementation)
        ++(implementation->reference);
}

EventQueue::~EventQueue() {
    if (implementation)
        if (--(implementation->reference) == 0) {
            implementation->clear();
            delete implementation;
        }
}

SIZE EventQueue::total() const {
    if (implementation)
        return implementation->total();
    return 0;
}

BOOLEAN EventQueue::empty() const {
    if (implementation)
        return implementation->empty();
    return true;
}

void EventQueue::clear() {
    if (implementation)
        if (--(implementation->reference) == 0) {
            implementation->clear();
            delete implementation;
        }
    implementation = new EventQueueImplementation;
    if (implementation)
        ++(implementation->reference);
}

void EventQueue::destroy() {
    if (implementation)
        if (--(implementation->reference) == 0) {
            implementation->destroy();
            delete implementation;
        }
    implementation = new EventQueueImplementation;
    if (implementation)
        ++(implementation->reference);
}

void EventQueue::append(Event* E, Object* R, Object* S) {
    append(EventElement(E, R, S));
}

void EventQueue::append(const EventElement& REF) {
    if (implementation) {
        if (implementation->reference != 1) {
            EventQueueImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->append(REF);
    }
}

void EventQueue::pop() {
    if (implementation) {
        if (implementation->reference != 1) {
            EventQueueImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->pop();
    }
}

const EventElement& EventQueue::top() const {
    return implementation->head->object;
}

EventQueue& EventQueue::operator =(const EventQueue& REF) {
    if (implementation && REF.implementation) {
        ++(REF.implementation->reference);
        if (--(implementation->reference) == 0) {
            EventQueueImplementation* OLD = implementation;
            implementation = REF.implementation;
            OLD->clear();
            delete OLD;
        } else
            implementation = REF.implementation;
    }
    return *this;
}

END_SOURCECODE
