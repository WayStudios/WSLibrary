/*******************************************************************************
 * Way Studios Library
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

template <typename T>
class LOCAL Queue<T>::QueueImplementation : public Allocator< QueueNode<Queue<T>::TYPE> > {
    UNCOPYABLE(QueueImplementation)
public:
    QueueImplementation();
    ~QueueImplementation();

    SIZE total() const;
    BOOLEAN empty() const;
    QueueImplementation* duplicate();
    void clear();

    void push(const TYPE&);
    void pop();

    AtomicInteger reference;
    Mutex mutex;
    QueueNode<TYPE>* head;
    QueueNode<TYPE>* tail;
};

template <typename T>
class EXPORT Queue<T>::Iterator {
    QueueNode<Queue<T>::TYPE>* current;
public:
    explicit Iterator(QueueNode<Queue<T>::TYPE>*);
    Iterator(const Iterator&);
    ~Iterator();

    Iterator& operator =(const Iterator&);
    Iterator& operator ++();

    Queue<T>::TYPE& operator *();

    const Queue<T>::TYPE& operator *() const;

    BOOLEAN operator==(const Queue<T>::Iterator&) const;
    BOOLEAN operator!=(const Queue<T>::Iterator&) const;
};

template <typename T>
Queue<T>::QueueImplementation::QueueImplementation() : head(0), tail(0) {
}

template <typename T>
Queue<T>::QueueImplementation::~QueueImplementation() {
}

template <typename T>
SIZE Queue<T>::QueueImplementation::total() const {
    SIZE RET = 0;
    if (!empty()) {
        ScopedLock<Mutex> SL_MUTEX(&mutex);
        for (QueueNode<Queue<T>::TYPE>* P_ITER = head; P_ITER != 0; P_ITER = P_ITER->next)
            ++RET;
    }
    return 0;
}

template <typename T>
BOOLEAN Queue<T>::QueueImplementation::empty() const {
    return !head;
}

template <typename T>
class Queue<T>::QueueImplementation* Queue<T>::QueueImplementation::duplicate() {
    ScopedLock<Mutex> SL_MUTEX(&mutex);
    QueueImplementation* N_IMPL = new QueueImplementation;
    if (N_IMPL) {
        if (!empty()) {
            for (QueueNode<Queue<T>::TYPE>* P_ITER = head; P_ITER != 0; P_ITER = P_ITER->next) {
                QueueNode<Queue<T>::TYPE>* P_N = allocate(1);
                new(P_N) QueueNode<Queue<T>::TYPE> (P_ITER->object, 0);
                if (N_IMPL->empty())
                    N_IMPL->tail = N_IMPL->head = P_N;
                else {
                    N_IMPL->tail->next = P_N;
                    N_IMPL->tail = P_N;
                }
            }
        }
        return N_IMPL;
    }
    return 0;
}

template <typename T>
void Queue<T>::QueueImplementation::clear() {
    if (!empty()) {
        ScopedLock<Mutex> SL_MUTEX(&mutex);
        while (!empty()) {
            QueueNode<Queue<T>::TYPE>* P_N = head->next;
            destruct(head);
            deallocate(head);
            head = P_N;
            if (empty())
                tail = head = 0;
        }
    }
}

template <typename T>
void Queue<T>::QueueImplementation::push(const Queue<T>::TYPE& REF) {
    ScopedLock<Mutex> SL_MUTEX(&mutex);
    QueueNode<Queue<T>::TYPE>* P_N = allocate(1);
    new(P_N) QueueNode<Queue<T>::TYPE>(REF, 0);
    if (empty())
        tail = head = P_N;
    else {
        tail->next = P_N;
        tail = P_N;
    }
}

template <typename T>
void Queue<T>::QueueImplementation::pop() {
    if (!empty()) {
        ScopedLock<Mutex> SL_MUTEX(&mutex);
        QueueNode<Queue<T>::TYPE>* P_N = head->next;
        destruct(head);
        deallocate(head);
        head = P_N;
        if (empty())
            tail = head = 0;
    }
}

template <typename T>
Queue<T>::Iterator::Iterator(QueueNode<Queue<T>::TYPE>* P_ITER) : current(P_ITER) {
}

template <typename T>
Queue<T>::Iterator::Iterator(const Queue<T>::Iterator& REF) : current(REF.current) {
}

template <typename T>
Queue<T>::Iterator::~Iterator() {
}

template <typename T>
class Queue<T>::Iterator& Queue<T>::Iterator::operator =(const Queue<T>::Iterator& REF) {
    current = REF.current;
    return *this;
}

template <typename T>
class Queue<T>::Iterator& Queue<T>::Iterator::operator ++() {
    current = current->next;
    return *this;
}

template <typename T>
Queue<T>::TYPE& Queue<TYPE>::Iterator::operator *() {
    return current->object;
}

template <typename T>
const Queue<T>::TYPE& Queue<T>::Iterator::operator *() const {
    return current->object;
}

template <typename T>
BOOLEAN Queue<T>::Iterator::operator ==(const Iterator& REF) const {
    return current == REF.current;
}

template <typename T>
BOOLEAN Queue<T>::Iterator::operator !=(const Iterator& REF) const {
    return current != REF.current;
}

template <typename T>
Queue<T>::Queue() : implementation(0) {
    implementation = new QueueImplementation;
    if (implementation)
        ++(implementation->reference);
}

template <typename T>
Queue<T>::Queue(const Queue<T>& REF) : implementation(REF.implementation) {
    if (implementation)
        ++(implementation->reference);
}

template <typename T>
Queue<T>::~Queue() {
    if (implementation)
        if (--(implementation->reference) == 0) {
            implementation->clear();
            delete implementation;
        }
}

template <typename T>
SIZE Queue<T>::total() const {
    if (implementation)
        return implementation->total();
    return 0;
}

template <typename T>
BOOLEAN Queue<T>::empty() const {
    if (implementation)
        return implementation->empty();
    return true;
}

template <typename T>
void Queue<T>::clear() {
    if (implementation)
        if (--(implementation->reference) == 0) {
            implementation->clear();
            delete implementation;
        }
    implementation = new QueueImplementation;
    if (implementation)
        ++(implementation->reference);
}

template <typename T>
BOOLEAN Queue<T>::exist(const Queue<T>::TYPE& REF) const {
    if (implementation) {
        ScopedLock<Mutex> SL_MUTEX(&(implementation->mutex));
        for (Iterator iter = begin(); iter != end(); ++iter)
            if (*iter == REF)
                return true;
    }
    return false;
}

template <typename T>
Queue<T>::TYPE& Queue<T>::top() {
    if (implementation->reference != 1) {
        QueueImplementation* N_IMPL = implementation->duplicate();
        --(implementation->reference);
        implementation = N_IMPL;
        ++(implementation->reference);
    }
    return implementation->head->object;
}

template <typename T>
const Queue<T>::TYPE& Queue<T>::top() const {
    return implementation->head->object;
}

template <typename T>
void Queue<T>::push(const Queue<T>::TYPE& REF) {
    if (implementation) {
        if (implementation->reference != 1) {
            QueueImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->push(REF);
    }
}

template <typename T>
void Queue<T>::pop() {
    if (implementation) {
        if (implementation->reference != 1) {
            QueueImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->pop();
    }
}

template <typename T>
void Queue<T>::append(const Queue<T>::TYPE& REF) {
    push(REF);
}

template <typename T>
class Queue<T>::Iterator Queue<T>::begin() {
    if (implementation)
        return Iterator(implementation->head);
    return Iterator(0);
}

template <typename T>
class Queue<T>::Iterator Queue<T>::end() {
    return Iterator(0);
}

template <typename T>
const class Queue<T>::Iterator Queue<T>::begin() const {
    if (implementation)
        return Iterator(implementation->head);
    return Iterator(0);
}

template <typename T>
const class Queue<T>::Iterator Queue<T>::end() const {
    return Iterator(0);
}

template <typename T>
Queue<T>& Queue<T>::operator =(const Queue<T>& REF) {
    if (implementation && REF.implementation) {
        ++(REF.implementation->reference);
        if (--(implementation->reference) == 0) {
            QueueImplementation* OLD = implementation;
            implementation = REF.implementation;
            OLD->clear();
            delete OLD;
        } else
            implementation = REF.implementation;
    }
    return *this;
}

template <typename T>
BOOLEAN Queue<T>::operator ==(const Queue<T>& REF) const {
    if (implementation && REF.implementation) {
        if (implementation != REF.implementation) {
            ScopedLock<Mutex> SL_MUTEX_F(&(REF.implementation->mutex));
            ScopedLock<Mutex> SL_MUTEX_S(&(implementation->mutex));
            QueueNode<Queue<T>::TYPE>* P_ITER_F = REF.implementation->head;
            QueueNode<Queue<T>::TYPE>* P_ITER_S = implementation->head;
            while (P_ITER_F && P_ITER_S) {
                if (P_ITER_F->object != P_ITER_S->object)
                    return false;
                P_ITER_F = P_ITER_F->next;
                P_ITER_S = P_ITER_S->next;
            }
        }
        return true;
    }
    return false;
}

template <typename T>
BOOLEAN Queue<T>::operator !=(const Queue<T>& REF) const {
    if (implementation && REF.implementation) {
        if (implementation != REF.implementation) {
            ScopedLock<Mutex> SL_MUTEX_F(&(REF.implementation->mutex));
            ScopedLock<Mutex> SL_MUTEX_S(&(implementation->mutex));
            QueueNode<Queue<T>::TYPE>* P_ITER_F = REF.implementation->head;
            QueueNode<Queue<T>::TYPE>* P_ITER_S = implementation->head;
            while (P_ITER_F && P_ITER_S) {
                if (P_ITER_F->object != P_ITER_S->object)
                    return true;
                P_ITER_F = P_ITER_F->next;
                P_ITER_S = P_ITER_S->next;
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
