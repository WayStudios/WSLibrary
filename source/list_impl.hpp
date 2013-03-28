/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef LIST_implementation_HEADER
#define	LIST_implementation_HEADER

#include <list.hpp>
#include <allocator.hpp>
#include <listnode.hpp>
#include <atomicinteger.hpp>
#include <mutex.hpp>
#include <scopedlock.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
class LOCAL List<T>::ListImplementation : public Allocator< ListNode<typename List<T>::TYPE> > {
    UNCOPYABLE(ListImplementation)
public:
    ListImplementation();
    ~ListImplementation();

    SIZE total() const;
    BOOLEAN empty() const;
    ListImplementation* duplicate();
    void clear();

    void pushFront(const T&);
    void popFront();

    void pushBack(const T&);
    void popBack();

    void remove(ListNode<T>*);
    void remove(const T&);

#if !defined(WITHOUT_THREAD)
    mutable AtomicInteger reference;
    mutable Mutex mutex;
#endif
    ListNode<T>* begin;
    ListNode<T>* end;
};

template <typename T>
class EXPORT List<T>::Iterator {
    ListNode<T>* current; //the pointer of current address of node
public:
    explicit Iterator(ListNode<T>*);
    Iterator(const Iterator&);
    ~Iterator();

    Iterator& operator =(const Iterator&);
    Iterator& operator ++();
    Iterator& operator --();

    T& operator*();

    const T& operator*() const;

    BOOLEAN operator ==(const Iterator&) const;
    BOOLEAN operator !=(const Iterator&) const;
};

template <typename T>
List<T>::ListImplementation::ListImplementation() : begin(0), end(0) {
}

template <typename T>
List<T>::ListImplementation::~ListImplementation() {
}

template <typename T>
SIZE List<T>::ListImplementation::total() const {
    SIZE RET = 0;
    if (!empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        for (ListNode<T>* P_ITER = begin; P_ITER != 0; P_ITER = P_ITER->next)
            ++RET;
    }
    return RET;
}

template <typename T>
BOOLEAN List<T>::ListImplementation::empty() const {
    return !begin;
}

template <typename T>
typename List<T>::ListImplementation* List<T>::ListImplementation::duplicate() {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
    ListImplementation* N_IMPL = new ListImplementation;
    if (N_IMPL) {
        if (!empty()) {
            for (ListNode<T>* P_ITER = begin; P_ITER != 0; P_ITER = P_ITER->next) {
                ListNode<T>* P_N = Allocator< ListNode<T> >::allocate(1);
                new(P_N) ListNode<T> (P_ITER->object, 0, 0);
                if (N_IMPL->empty())
                    N_IMPL->end = N_IMPL->begin = P_N;
                else {
                    P_N->prev = N_IMPL->end;
                    N_IMPL->end->next = P_N;
                    N_IMPL->end = P_N;
                }
            }
        }
        return N_IMPL;
    }
    return 0;
}

template <typename T>
void List<T>::ListImplementation::clear() {
    if (!empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        while (!empty()) {
            ListNode<T>* P_N = begin->next;
            destruct(begin);
            deallocate(begin);
            begin = P_N;
            if (empty())
                end = begin = 0;
        }
    }
}

template <typename T>
void List<T>::ListImplementation::pushFront(const typename List<T>::TYPE& REF) {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
    ListNode<T>* P_N = allocate(1);
    new(P_N) ListNode<T> (REF, 0, 0);
    if (empty())
        end = begin = P_N;
    else {
        P_N->next = begin;
        begin->prev = P_N;
        begin = P_N;
    }
}

template <typename T>
void List<T>::ListImplementation::popFront() {
    if (!empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        ListNode<T>* P_N = begin->next;
        if (P_N)
            P_N->prev = 0;
        destruct(begin);
        deallocate(begin);
        begin = P_N;
        if (empty())
            end = begin = 0;
    }
}

template <typename T>
void List<T>::ListImplementation::pushBack(const typename List<T>::TYPE& REF) {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
    ListNode<T>* P_N = allocate(1);
    new(P_N) ListNode<T> (REF, 0, 0);
    if (empty())
        end = begin = P_N;
    else {
        P_N->prev = end;
        end->next = P_N;
        end = P_N;
    }
}

template <typename T>
void List<T>::ListImplementation::popBack() {
    if (!empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        ListNode<T>* P_N = end->prev;
        if (P_N)
            P_N->next = 0;
        destruct(end);
        deallocate(end);
        end = P_N;
        if (empty())
            end = begin = 0;
    }
}

template <typename T>
void List<T>::ListImplementation::remove(ListNode<T>* P_N) {
    if (!empty() && P_N) {
        if (P_N == begin)
            return popFront();
        if (P_N == end)
            return popBack();
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        P_N->prev->next = P_N->next;
        P_N->next->prev = P_N->prev;
        destruct(P_N);
        deallocate(P_N);
    }
}

template <typename T>
void List<T>::ListImplementation::remove(const typename List<T>::TYPE& REF) {
    if (!empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        for (ListNode<T>* P_ITER = begin; P_ITER != 0; P_ITER = P_ITER->next)
            if (P_ITER->object == REF) {
                if (P_ITER == begin)
                    begin = begin->next;
                if (P_ITER == end)
                    end = end->prev;
                if (P_ITER->prev)
                    P_ITER->prev->next = P_ITER->next;
                if (P_ITER->next)
                    P_ITER->next->prev = P_ITER->prev;
                destruct(P_ITER);
                deallocate(P_ITER);
                return;
            }
    }
}

template <typename T>
List<T>::Iterator::Iterator(ListNode<T>* P_ITER) : current(P_ITER) {
}

template <typename T>
List<T>::Iterator::Iterator(const Iterator& REF) : current(REF.current) {
}

template <typename T>
List<T>::Iterator::~Iterator() {
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator =(const Iterator& REF) {
    current = REF.current;
    return *this;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator ++() {
    current = current->next;
    return *this;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator --() {
    current = current->prev;
    return *this;
}

template <typename T>
typename List<T>::TYPE& List<T>::Iterator::operator *() {
    return current->object;
}

template <typename T>
const typename  List<T>::TYPE& List<T>::Iterator::operator *() const {
    return current->object;
}

template <typename T>
BOOLEAN List<T>::Iterator::operator ==(const Iterator& REF) const {
    return current == REF.current;
}

template <typename T>
BOOLEAN List<T>::Iterator::operator !=(const Iterator& REF) const {
    return current != REF.current;
}

template <typename T>
List<T>::List() : implementation(0) {
    implementation = new ListImplementation;
    if (implementation)
        ++(implementation->reference);
}

template <typename T>
List<T>::List(const List<T>& REF) : implementation(REF.implementation) {
    if (implementation)
        ++(implementation->reference);
}

template <typename T>
List<T>::~List() {
    if (implementation)
        if (--(implementation->reference) == 0) {
            implementation->clear();
            delete implementation;
        }
}

template <typename T>
SIZE List<T>::total() const {
    if (implementation)
        return implementation->total();
    return 0;
}

template <typename T>
BOOLEAN List<T>::empty() const {
    if (implementation)
        return implementation->empty();
    return true;
}

template <typename T>
void List<T>::clear() {
    if (implementation)
        if (--(implementation->Ref) == 0) {
            implementation->clear();
            delete implementation;
        }
    implementation = new ListImplementation;
    if (implementation)
        ++(implementation->Ref);
}

template <typename T>
BOOLEAN List<T>::exist(const typename List<T>::TYPE& REF) const {
    if (implementation) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&(implementation->mutex));
#endif
        for (Iterator P_ITER = begin(); P_ITER != end(); ++P_ITER)
            if (*P_ITER == REF)
                return true;
    }
    return false;
}

template <typename T>
typename List<T>::TYPE& List<T>::first() {
    if (implementation->ref != 1) {
        ListImplementation* N_IMPL = implementation->duplicate();
        --(implementation->ref);
        implementation = N_IMPL;
        ++(implementation->ref);
    }
    return implementation->begin->object;
}

template <typename T>
typename List<T>::TYPE& List<T>::last() {
    if (implementation->ref != 1) {
        ListImplementation* N_IMPL = implementation->duplicate();
        --(implementation->ref);
        implementation = N_IMPL;
        ++(implementation->ref);
    }
    return implementation->end->object;
}

template <typename T>
typename List<T>::TYPE& List<T>::at(SIZE IDX) {
    if (implementation->ref != 1) {
        ListImplementation* N_IMPL = implementation->duplicate();
        --(implementation->ref);
        implementation = N_IMPL;
        ++(implementation->ref);
    }
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_MUTEX(&(implementation->mutex));
#endif
    Iterator ITER = implementation->begin;
    for (SIZE i = 0; i <= IDX; ++i)
        ++ITER;
    return *ITER;
}

template <typename T>
const typename List<T>::TYPE& List<T>::first() const {
    return implementation->begin->object;
}

template <typename T>
const typename List<T>::TYPE& List<T>::last() const {
    return implementation->end->object;
}

template <typename T>
const typename List<T>::TYPE& List<T>::at(SIZE IDX) const {
    Iterator ITER = implementation->begin;
    for (SIZE i = 0; i <= IDX; ++i)
        ++ITER;
    return *ITER;
}

template <typename T>
void List<T>::pushFront(const typename List<T>::TYPE& REF) {
    if (implementation) {
        if (implementation->ref != 1) {
            ListImplementation* N_IMPL = implementation->duplicate();
            --(implementation->ref);
            implementation = N_IMPL;
            ++(implementation->ref);
        }
        implementation->pushFront(REF);
    }
}

template <typename T>
void List<T>::popFront() {
    if (implementation) {
        if (implementation->ref != 1) {
            ListImplementation* N_IMPL = implementation->duplicate();
            --(implementation->ref);
            implementation = N_IMPL;
            ++(implementation->ref);
        }
        implementation->popFront();
    }
}

template <typename T>
void List<T>::pushBack(const T& REF) {
    if (implementation) {
        if (implementation->reference != 1) {
            ListImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->pushBack(REF);
    }
}

template <typename T>
void List<T>::popBack() {
    if (implementation) {
        if (implementation->ref != 1) {
            ListImplementation* N_IMPL = implementation->duplicate();
            --(implementation->ref);
            implementation = N_IMPL;
            ++(implementation->ref);
        }
        implementation->popBack();
    }
}

template <typename T>
void List<T>::append(const typename List<T>::TYPE& REF) {
    pushBack(REF);
}

template <typename T>
void List<T>::remove(const typename List<T>::TYPE& REF) {
    if (implementation) {
        if (implementation->reference != 1) {
            ListImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->remove(REF);
    }
}

template <typename T>
typename List<T>::Iterator List<T>::begin() {
    if (implementation)
        return Iterator(implementation->begin);
    return Iterator(0);
}

template <typename T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(0);
}

template <typename T>
const typename List<T>::Iterator List<T>::begin() const {
    if (implementation)
        return Iterator(implementation->begin);
    return Iterator(0);
}

template <typename T>
const typename List<T>::Iterator List<T>::end() const {
    return Iterator(0);
}

template <typename T>
List<T>& List<T>::operator =(const List<T>& REF) {
    if (implementation && REF.implementation) {
        ++(REF.implementation->ref);
        if (--(implementation->ref) == 0) {
            ListImplementation* OLD = implementation;
            implementation = REF.implementation;
            OLD->clear();
            delete OLD;
        } else
            implementation = REF.implementation;
    }
    return *this;
}

template <typename T>
BOOLEAN List<T>::operator ==(const List<T>& REF) const {
    if (implementation && REF.implementation) {
        if (implementation != REF.implementation) {
#if !defined(WITHOUT_THREAD)
            ScopedLock<Mutex> SL_MUTEX_F(&(REF.implementation->mutex));
            ScopedLock<Mutex> SL_MUTEX_S(&(implementation->mutex));
#endif
            ListNode<TYPE>* P_ITER_F = REF.implementation->begin;
            ListNode<TYPE>* P_ITER_S = implementation->begin;
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
BOOLEAN List<T>::operator !=(const List<T>& REF) const {
    if (implementation && REF.implementation) {
        if (implementation != REF.implementation) {
#if !defined(WITHOUT_THREAD)
            ScopedLock<Mutex> SL_MUTEX_F(&(REF.implementation->mutex));
            ScopedLock<Mutex> SL_MUTEX_S(&(implementation->mutex));
#endif
            ListNode<TYPE>* P_ITER_F = REF.implementation->begin;
            ListNode<TYPE>* P_ITER_S = implementation->begin;
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

template <typename T>
typename List<T>::TYPE& List<T>::operator [](SIZE IDX) {
    return at(IDX);
}

template <typename T>
const typename List<T>::TYPE& List<T>::operator [](SIZE IDX) const {
    return at(IDX);
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
