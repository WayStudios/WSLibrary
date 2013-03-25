/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef QUEUE_IMPLEMENTATION_HEADER
#define	QUEUE_IMPLEMENTATION_HEADER

#include <queue.hpp>
#include <allocator.hpp>
#include <queuenode.hpp>
#include <atomicinteger.hpp>
#include <mutex.hpp>
#include <scopedlock.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class LOCAL Queue<TYPE>::QueueImplementation : public Allocator< QueueNode<TYPE> > {
    UNCOPYABLE(QueueImplementation)
public:
    QueueImplementation();
    ~QueueImplementation();

    size Total() const;
    boolean Empty() const;
    QueueImplementation* Duplicate();
    void Clear();

    void Push(const TYPE&);
    void Pop();

    AtomicInteger Ref;
    Mutex MLock;
    QueueNode<TYPE>* QueB;
    QueueNode<TYPE>* QueE;
};

template <typename TYPE>
class EXPORT Queue<TYPE>::Iterator {
    QueueNode<TYPE>* Current;
public:
    explicit Iterator(QueueNode<TYPE>*);
    Iterator(const Iterator&);
    ~Iterator();

    Iterator& operator=(const Iterator&);
    Iterator& operator++();

    TYPE& operator*();

    const TYPE& operator*() const;

    boolean operator==(const Iterator&) const;
    boolean operator!=(const Iterator&) const;
};

template <typename TYPE>
Queue<TYPE>::QueueImplementation::QueueImplementation() : QueB(0), QueE(0) {
}

template <typename TYPE>
Queue<TYPE>::QueueImplementation::~QueueImplementation() {
}

template <typename TYPE>
size Queue<TYPE>::QueueImplementation::Total() const {
    size RET = 0;
    if (!Empty()) {
        ScopedLock<Mutex> SL_Mutex(&MLock);
        for (QueueNode<TYPE>* P_ITER = QueB; P_ITER != 0; P_ITER = P_ITER->Next)
            ++RET;
    }
    return 0;
}

template <typename TYPE>
boolean Queue<TYPE>::QueueImplementation::Empty() const {
    return !QueB;
}

template <typename TYPE>
class Queue<TYPE>::QueueImplementation* Queue<TYPE>::QueueImplementation::Duplicate() {
    ScopedLock<Mutex> SL_Mutex(&MLock);
    QueueImplementation* N_IMPL = new QueueImplementation;
    if (N_IMPL) {
        if (!Empty()) {
            for (QueueNode<TYPE>* P_ITER = QueB; P_ITER != 0; P_ITER = P_ITER->Next) {
                QueueNode<TYPE>* P_N = Allocate(1);
                new(P_N) QueueNode<TYPE > (P_ITER->Object, 0);
                if (N_IMPL->Empty())
                    N_IMPL->QueE = N_IMPL->QueB = P_N;
                else {
                    N_IMPL->QueE->Next = P_N;
                    N_IMPL->QueE = P_N;
                }
            }
        }
        return N_IMPL;
    }
    return 0;
}

template <typename TYPE>
void Queue<TYPE>::QueueImplementation::Clear() {
    if (!Empty()) {
        ScopedLock<Mutex> SL_Mutex(&MLock);
        while (!Empty()) {
            QueueNode<TYPE>* P_N = QueB->Next;
            Destruct(QueB);
            Deallocate(QueB);
            QueB = P_N;
            if (Empty())
                QueE = QueB = 0;
        }
    }
}

template <typename TYPE>
void Queue<TYPE>::QueueImplementation::Push(const TYPE& REF) {
    ScopedLock<Mutex> SL_Mutex(&MLock);
    QueueNode<TYPE>* P_N = Allocator<TYPE>::Allocate(1);
    new(P_N) QueueNode<TYPE > (REF, 0);
    if (Empty())
        QueE = QueB = P_N;
    else {
        QueE->Next = P_N;
        QueE = P_N;
    }
}

template <typename TYPE>
void Queue<TYPE>::QueueImplementation::Pop() {
    if (!Empty()) {
        ScopedLock<Mutex> SL_Mutex(&MLock);
        QueueNode<TYPE>* P_N = QueB->Next;
        Destruct(QueB);
        Deallocate(QueB);
        QueB = P_N;
        if (Empty())
            QueE = QueB = 0;
    }
}

template <typename TYPE>
Queue<TYPE>::Iterator::Iterator(QueueNode<TYPE>* P_ITER) : Current(P_ITER) {
}

template <typename TYPE>
Queue<TYPE>::Iterator::Iterator(const Iterator& REF) : Current(REF.Current) {
}

template <typename TYPE>
Queue<TYPE>::Iterator::~Iterator() {
}

template <typename TYPE>
class Queue<TYPE>::Iterator& Queue<TYPE>::Iterator::operator =(const Iterator& REF) {
    Current = REF.Current;
    return *this;
}

template <typename TYPE>
class Queue<TYPE>::Iterator& Queue<TYPE>::Iterator::operator ++() {
    Current = Current->Next;
    return *this;
}

template <typename TYPE>
TYPE& Queue<TYPE>::Iterator::operator *() {
    return Current->Object;
}

template <typename TYPE>
const TYPE& Queue<TYPE>::Iterator::operator *() const {
    return Current->Object;
}

template <typename TYPE>
boolean Queue<TYPE>::Iterator::operator ==(const Iterator& REF) const {
    return Current == REF.Current;
}

template <typename TYPE>
boolean Queue<TYPE>::Iterator::operator !=(const Iterator& REF) const {
    return Current != REF.Current;
}

template <typename TYPE>
Queue<TYPE>::Queue() : Implementation(0) {
    Implementation = new QueueImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

template <typename TYPE>
Queue<TYPE>::Queue(const Queue<TYPE>& REF) : Implementation(REF.Implementation) {
    if (Implementation)
        ++(Implementation->Ref);
}

template <typename TYPE>
Queue<TYPE>::~Queue() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->Clear();
            delete Implementation;
        }
}

template <typename TYPE>
size Queue<TYPE>::Total() const {
    if (Implementation)
        return Implementation->Total();
    return 0;
}

template <typename TYPE>
boolean Queue<TYPE>::Empty() const {
    if (Implementation)
        return Implementation->Empty();
    return true;
}

template <typename TYPE>
void Queue<TYPE>::Clear() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->Clear();
            delete Implementation;
        }
    Implementation = new QueueImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

template <typename TYPE>
boolean Queue<TYPE>::Exist(const TYPE& REF) const {
    if (Implementation) {
        ScopedLock<Mutex> SL_Mutex(&(Implementation->MLock));
        for (Iterator iter = Begin(); iter != End(); ++iter)
            if (*iter == REF)
                return true;
    }
    return false;
}

template <typename TYPE>
TYPE& Queue<TYPE>::Top() {
    if (Implementation->Ref != 1) {
        QueueImplementation* N_IMPL = Implementation->Duplicate();
        --(Implementation->Ref);
        Implementation = N_IMPL;
        ++(Implementation->Ref);
    }
    return Implementation->QueB->Object;
}

template <typename TYPE>
const TYPE& Queue<TYPE>::Top() const {
    return Implementation->QueB->Object;
}

template <typename TYPE>
void Queue<TYPE>::Push(const TYPE& REF) {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            QueueImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->Push(REF);
    }
}

template <typename TYPE>
void Queue<TYPE>::Pop() {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            QueueImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->Pop();
    }
}

template <typename TYPE>
void Queue<TYPE>::Append(const TYPE& REF) {
    Push(REF);
}

template <typename TYPE>
class Queue<TYPE>::Iterator Queue<TYPE>::Begin() {
    if (Implementation)
        return Iterator(Implementation->QueB);
    return Iterator(0);
}

template <typename TYPE>
class Queue<TYPE>::Iterator Queue<TYPE>::End() {
    return Iterator(0);
}

template <typename TYPE>
const class Queue<TYPE>::Iterator Queue<TYPE>::Begin() const {
    if (Implementation)
        return Iterator(Implementation->QueB);
    return Iterator(0);
}

template <typename TYPE>
const class Queue<TYPE>::Iterator Queue<TYPE>::End() const {
    return Iterator(0);
}

template <typename TYPE>
        Queue<TYPE>& Queue<TYPE>::operator =(const Queue<TYPE>& REF) {
    if (Implementation && REF.Implementation) {
        ++(REF.Implementation->Ref);
        if (--(Implementation->Ref) == 0) {
            QueueImplementation* OLD = Implementation;
            Implementation = REF.Implementation;
            OLD->Clear();
            delete OLD;
        } else
            Implementation = REF.Implementation;
    }
    return *this;
}

template <typename TYPE>
boolean Queue<TYPE>::operator ==(const Queue<TYPE>& REF) const {
    if (Implementation && REF.Implementation) {
        if (Implementation != REF.Implementation) {
            ScopedLock<Mutex> SL_Mutex_F(&(REF.Implementation->MLock));
            ScopedLock<Mutex> SL_Mutex_S(&(Implementation->MLock));
            QueueNode<TYPE>* P_ITER_F = REF.Implementation->QueB;
            QueueNode<TYPE>* P_ITER_S = Implementation->QueB;
            while (P_ITER_F && P_ITER_S) {
                if (P_ITER_F->Object != P_ITER_S->Object)
                    return false;
                P_ITER_F = P_ITER_F->Next;
                P_ITER_S = P_ITER_S->Next;
            }
        }
        return true;
    }
    return false;
}

template <typename TYPE>
boolean Queue<TYPE>::operator !=(const Queue<TYPE>& REF) const {
    if (Implementation && REF.Implementation) {
        if (Implementation != REF.Implementation) {
            ScopedLock<Mutex> SL_Mutex_F(&(REF.Implementation->MLock));
            ScopedLock<Mutex> SL_Mutex_S(&(Implementation->MLock));
            QueueNode<TYPE>* P_ITER_F = REF.Implementation->QueB;
            QueueNode<TYPE>* P_ITER_S = Implementation->QueB;
            while (P_ITER_F && P_ITER_S) {
                if (P_ITER_F->Object != P_ITER_S->Object)
                    return true;
                P_ITER_F = P_ITER_F->Next;
                P_ITER_S = P_ITER_S->Next;
            }
        }
        return false;
    }
    return true;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
