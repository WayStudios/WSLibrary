/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <eventqueue.hpp>
#include <eventqueueimpl.hpp>
#include <scopedlock.hpp>
#include <event.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

EventQueue::EventQueueImplementation::EventQueueImplementation() : QueB(0), QueE(0) {
}

EventQueue::EventQueueImplementation::~EventQueueImplementation() {
}

size EventQueue::EventQueueImplementation::Total() const {
    size RET = 0;
    if (!Empty()) {
        ScopedLock<Mutex> SL_Mutex(const_cast<Mutex*> (&MLock));
        QueueNode<EventQueue::VALUE>* P_N = QueB;
        while (P_N) {
            ++RET;
            P_N = P_N->Next;
        }
    }
    return RET;
}

boolean EventQueue::EventQueueImplementation::Empty() const {
    return !QueB;
}

void EventQueue::EventQueueImplementation::Clear() {
    if (!Empty()) {
        ScopedLock<Mutex> SL_Mutex(&MLock);
        while (!Empty()) {
            QueueNode<EventQueue::VALUE>* P_N = QueB->Next;
            Destruct(QueB);
            Deallocate(QueB);
            QueB = P_N;
            if (Empty())
                QueE = QueB = 0;
        }
    }
}

void EventQueue::EventQueueImplementation::Destroy() {
    //destroy all appended events or aka delete Event*;
    if (!Empty()) {
        ScopedLock<Mutex> SL_Mutex(&MLock);
        while (!Empty()) {
            QueueNode<EventQueue::VALUE>* P_N = QueB->Next;
            delete (QueB->Object.Content);
            Destruct(QueB);
            Deallocate(QueB);
            QueB = P_N;
            if (Empty())
                QueE = QueB = 0;
        }
    }
}

EventQueue::EventQueueImplementation* EventQueue::EventQueueImplementation::Duplicate() {
    ScopedLock<Mutex> SL_Mutex(&MLock);
    EventQueueImplementation* N_IMPL = new EventQueueImplementation;
    if (N_IMPL) {
        if (!Empty()) {
            QueueNode<EventQueue::VALUE>* P_ITER = QueB;
            while (P_ITER) {
                QueueNode<EventQueue::VALUE>* P_N = Allocate(1);
                new(P_N) QueueNode<EventQueue::VALUE > (P_ITER->Object, 0);
                if (N_IMPL->Empty())
                    N_IMPL->QueE = N_IMPL->QueB = P_N;
                else {
                    N_IMPL->QueE->Next = P_N;
                    N_IMPL->QueE = P_N;
                }
                P_ITER = P_ITER->Next;
            }
        }
        return N_IMPL;
    }
    return 0;
}

void EventQueue::EventQueueImplementation::Append(const EventQueue::VALUE& REF) {
    ScopedLock<Mutex> SL_Mutex(&MLock);
    QueueNode<EventQueue::VALUE>* P_N = Allocate(1);
    new(P_N) QueueNode<EventQueue::VALUE > (REF, 0);
    if (Empty())
        QueE = QueB = P_N;
    else {
        QueE->Next = P_N;
        QueE = P_N;
    }
}

void EventQueue::EventQueueImplementation::Pop() {
    if (!Empty()) {
        ScopedLock<Mutex> SL_Mutex(&MLock);
        QueueNode<EventQueue::VALUE>* P_N = QueB->Next;
        Destruct(QueB);
        Deallocate(QueB);
        QueB = P_N;
        if (Empty())
            QueE = QueB = 0;
    }
}

EventQueue::EventQueue() : Implementation(0) {
    Implementation = new EventQueueImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

EventQueue::EventQueue(const EventQueue& REF) : Implementation(REF.Implementation) {
    if (Implementation)
        ++(Implementation->Ref);
}

EventQueue::~EventQueue() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->Clear();
            delete Implementation;
        }
}

size EventQueue::Total() const {
    if (Implementation)
        return Implementation->Total();
    return 0;
}

boolean EventQueue::Empty() const {
    if (Implementation)
        return Implementation->Empty();
    return true;
}

void EventQueue::Clear() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->Clear();
            delete Implementation;
        }
    Implementation = new EventQueueImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

void EventQueue::Destroy() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->Destroy();
            delete Implementation;
        }
    Implementation = new EventQueueImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

void EventQueue::Append(Event* E, Object* R, Object* S) {
    Append(EventElement(E, R, S));
}

void EventQueue::Append(const EventElement& REF) {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            EventQueueImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->Append(REF);
    }
}

void EventQueue::Pop() {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            EventQueueImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->Pop();
    }
}

const EventElement& EventQueue::Top() const {
    return Implementation->QueB->Object;
}

EventQueue& EventQueue::operator =(const EventQueue& REF) {
    if (Implementation && REF.Implementation) {
        ++(REF.Implementation->Ref);
        if (--(Implementation->Ref) == 0) {
            EventQueueImplementation* OLD = Implementation;
            Implementation = REF.Implementation;
            OLD->Clear();
            delete OLD;
        } else
            Implementation = REF.Implementation;
    }
    return *this;
}

END_SOURCECODE
