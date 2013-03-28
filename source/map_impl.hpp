/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef MAP_IMPLEMENTATION_HEADER
#define	MAP_IMPLEMENTATION_HEADER

#include <map.hpp>
#include <allocator.hpp>
#include <listnode.hpp>
#include <atomicinteger.hpp>
#include <mutex.hpp>
#include <scopedlock.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T_KEY, typename T>
class LOCAL Map<T_KEY, T>::MapImplementation : public Allocator< ListNode<typename Map<T_KEY, T>::PAIR> > {
    UNCOPYABLE(MapImplementation)
public:
    MapImplementation();
    ~MapImplementation();

    SIZE total() const;
    BOOLEAN empty() const;
    MapImplementation* duplicate();
    void clear();

    BOOLEAN exist(const typename Map<T_KEY, T>::KEY&);

    void append(const typename Map<T_KEY, T>::KEY&, const typename Map<T_KEY, T>::TYPE&);

    void remove(ListNode<typename Map<T_KEY, T>::PAIR>*);
    void remove(const typename Map<T_KEY, T>::KEY&);

#if !defined(WITHOUT_THREAD)
    mutable AtomicInteger reference;
    mutable Mutex mutex;
#endif
    ListNode<typename Map<T_KEY, T>::PAIR>* begin;
    ListNode<typename Map<T_KEY, T>::PAIR>* end;
    ListNode<typename Map<T_KEY, T>::PAIR>* current;
};

template <typename T_KEY, typename T>
class EXPORT Map<T_KEY, T>::Iterator {
    ListNode<typename Map<T_KEY, T>::PAIR>* current;
public:
    explicit Iterator(ListNode<typename Map<T_KEY, T>::PAIR>*);
    Iterator(const Iterator&);
    ~Iterator();

    Iterator& operator=(const Iterator&);
    Iterator& operator++();
    Iterator& operator--();

    typename Map<T_KEY, T>::PAIR& operator*();

    const typename Map<T_KEY, T>::PAIR& operator*() const;

    BOOLEAN operator==(const Iterator&) const;
    BOOLEAN operator!=(const Iterator&) const;
};

template <typename T_KEY, typename T>
Map<T_KEY, T>::MapImplementation::MapImplementation() : begin(0), end(0), current(0) {
}

template <typename T_KEY, typename T>
Map<T_KEY, T>::MapImplementation::~MapImplementation() {
}

template <typename T_KEY, typename T>
SIZE Map<T_KEY, T>::MapImplementation::total() const {
    SIZE RET = 0;
    if (!empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        for (ListNode<Map<T_KEY, T>::PAIR>* P_ITER = begin; P_ITER != 0; P_ITER = P_ITER->next)
            ++RET;
    }
    return RET;
}

template <typename T_KEY, typename T>
BOOLEAN Map<T_KEY, T>::MapImplementation::empty() const {
    return !begin;
}

template <typename T_KEY, typename T>
typename Map<T_KEY, T>::MapImplementation* Map<T_KEY, T>::MapImplementation::duplicate() {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
    MapImplementation* N_IMPL = new MapImplementation;
    if (N_IMPL) {
        if (!empty()) {
            for (ListNode<Map<T_KEY, T>::PAIR>* P_ITER = begin; P_ITER != 0; P_ITER = P_ITER->next) {
                ListNode<Map<T_KEY, T>::PAIR>* P_N = allocate(1);
                new(P_N) ListNode<Map<T_KEY, T>::PAIR>(P_ITER->object, 0, 0);
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

template <typename T_KEY, typename T>
void Map<T_KEY, T>::MapImplementation::clear() {
    if (!empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        while (!empty()) {
            ListNode<Map<T_KEY, T>::PAIR>* P_N = begin->next;
            destruct(begin);
            deallocate(begin);
            begin = P_N;
            if (empty())
                current = end = begin = 0;
        }
    }
}

template <typename T_KEY, typename T>
BOOLEAN Map<T_KEY, T>::MapImplementation::exist(const typename Map<T_KEY, T>::KEY& REF_KEY) {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
    for (ListNode<Map<T_KEY, T>::PAIR>* P_ITER = begin; P_ITER != 0; P_ITER = P_ITER->next)
        if (P_ITER->object.first == REF_KEY) {
            current = P_ITER;
            return true;
        }
    return false;
}

template <typename T_KEY, typename T>
void Map<T_KEY, T>::MapImplementation::append(const typename Map<T_KEY, T>::KEY& REF_KEY, const typename Map<T_KEY, T>::TYPE& REF_VALUE) {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
    ListNode<Map<T_KEY, T>::PAIR>* P_N = allocate(1);
    new(P_N) ListNode<Map<T_KEY, T>::PAIR>(Map<T_KEY, T>::PAIR(REF_KEY, REF_VALUE), 0, 0);
    if (empty())
        end = begin = P_N;
    else {
        P_N->prev = end;
        end->next = P_N;
        end = P_N;
    }
}

template <typename T_KEY, typename T>
void Map<T_KEY, T>::MapImplementation::remove(ListNode<typename Map<T_KEY, T>::PAIR>* P_N) {
    if (!empty() && P_N) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        if (P_N == begin)
            begin = begin->next;
        if (P_N == end)
            end = end->prev;
        if (P_N->prev)
            P_N->prev->next = P_N->next;
        if (P_N->next)
            P_N->next->prev = P_N->prev;
        current = 0;
        destruct(P_N);
        deallocate(P_N);
    }
}

template <typename T_KEY, typename T>
void Map<T_KEY, T>::MapImplementation::remove(const typename Map<T_KEY, T>::KEY& REF_KEY) {
    if (!empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        for (ListNode<Map<T_KEY, T>::PAIR>* P_ITER = begin; P_ITER != 0; P_ITER = P_ITER->next)
            if (P_ITER->object.first == REF_KEY) {
                if (P_ITER == begin)
                    begin = begin->next;
                if (P_ITER == end)
                    end = end->prev;
                if (P_ITER->prev)
                    P_ITER->prev->next = P_ITER->next;
                if (P_ITER->next)
                    P_ITER->next->prev = P_ITER->prev;
                current = 0;
                destruct(P_ITER);
                deallocate(P_ITER);
                return;
            }
    }
}

template <typename T_KEY, typename T>
Map<T_KEY, T>::Iterator::Iterator(ListNode<typename Map<T_KEY, T>::PAIR>* P_ITER) : current(P_ITER) {
}

template <typename T_KEY, typename T>
Map<T_KEY, T>::Iterator::Iterator(const typename Map<T_KEY, T>::Iterator& REF) : current(REF.current) {
}

template <typename T_KEY, typename T>
Map<T_KEY, T>::Iterator::~Iterator() {
}

template <typename T_KEY, typename T>
typename Map<T_KEY, T>::Iterator& Map<T_KEY, T>::Iterator::operator =(const typename Map<T_KEY, T>::Iterator& REF) {
    current = REF.current;
    return *this;
}

template <typename T_KEY, typename T>
typename Map<T_KEY, T>::Iterator& Map<T_KEY, T>::Iterator::operator ++() {
    current = current->next;
    return *this;
}

template <typename T_KEY, typename T>
typename Map<T_KEY, T>::Iterator& Map<T_KEY, T>::Iterator::operator --() {
    current = current->prev;
    return *this;
}

template <typename T_KEY, typename T>
typename Map<T_KEY, T>::PAIR& Map<T_KEY, T>::Iterator::operator *() {
    return current->object;
}

template <typename T_KEY, typename T>
const typename Map<T_KEY, T>::PAIR& Map<T_KEY, T>::Iterator::operator *() const {
    return current->object;
}

template <typename T_KEY, typename T>
BOOLEAN Map<T_KEY, T>::Iterator::operator ==(const typename Map<T_KEY, T>::Iterator& REF) const {
    return current == REF.current;
}

template <typename T_KEY, typename T>
BOOLEAN Map<T_KEY, T>::Iterator::operator !=(const typename Map<T_KEY, T>::Iterator& REF) const {
    return current != REF.current;
}

template <typename T_KEY, typename T>
Map<T_KEY, T>::Map() : implementation(0) {
    implementation = new MapImplementation;
    if (implementation)
        ++(implementation->reference);
}

template <typename T_KEY, typename T>
Map<T_KEY, T>::Map(const Map<T_KEY, T>& REF) : implementation(REF.implementation) {
    if (implementation)
        ++(implementation->reference);
}

template <typename T_KEY, typename T>
Map<T_KEY, T>::~Map() {
    if (implementation)
        if (--(implementation->reference) == 0) {
            implementation->clear();
            delete implementation;
        }
}

template <typename T_KEY, typename T>
SIZE Map<T_KEY, T>::total() const {
    if (implementation)
        return implementation->total();
    return 0;
}

template <typename T_KEY, typename T>
BOOLEAN Map<T_KEY, T>::empty() const {
    if (implementation)
        return implementation->empty();
    return true;
}

template <typename T_KEY, typename T>
void Map<T_KEY, T>::clear() {
    if (implementation)
        if (--(implementation->reference) == 0) {
            implementation->clear();
            delete implementation;
        }
    implementation = new MapImplementation;
    if (implementation)
        ++(implementation->reference);
}

template <typename T_KEY, typename T>
BOOLEAN Map<T_KEY, T>::exist(const typename Map<T_KEY, T>::KEY& REF_KEY) {
    if (implementation)
        return implementation->exist(REF_KEY);
}

template <typename T_KEY, typename T>
void Map<T_KEY, T>::append(const typename Map<T_KEY, T>::KEY& REF_KEY, const typename Map<T_KEY, T>::TYPE& REF_VALUE) {
    if (implementation) {
        if (implementation->reference != 1) {
            MapImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->append(REF_KEY, REF_VALUE);
    }
}

template <typename T_KEY, typename T>
void Map<T_KEY, T>::remove(const typename Map<T_KEY, T>::KEY& REF_KEY) {
    if (implementation) {
        if (implementation->reference != 1) {
            MapImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->remove(REF_KEY);
    }
}

template <typename T_KEY, typename T>
typename Map<T_KEY, T>::Iterator Map<T_KEY, T>::begin() {
    if (implementation)
        return Iterator(implementation->begin);
    return end();
}

template <typename T_KEY, typename T>
typename Map<T_KEY, T>::Iterator Map<T_KEY, T>::end() {
    return Iterator(0);
}

template <typename T_KEY, typename T>
typename Map<T_KEY, T>::Iterator Map<T_KEY, T>::find(const typename Map<T_KEY, T>::KEY& REF_KEY) {
    if (implementation->reference != 1) {
        MapImplementation* N_IMPL = implementation->duplicate();
        --(implementation->reference);
        implementation = N_IMPL;
        ++(implementation->reference);
    }
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_MUTEX(&(implementation->mutex));
#endif
    if (implementation->current)
        if (implementation->current->object.first == REF_KEY)
            return Iterator(implementation->current);
    for (Iterator P_ITER = begin(); P_ITER != end(); ++P_ITER)
        if ((*P_ITER).first == REF_KEY)
            return P_ITER;
    return end();
}

template <typename T_KEY, typename T>
const typename Map<T_KEY, T>::Iterator Map<T_KEY, T>::begin() const {
    if (implementation)
        return Iterator(implementation->begin);
    return end();
}

template <typename T_KEY, typename T>
const typename Map<T_KEY, T>::Iterator Map<T_KEY, T>::end() const {
    return Iterator(0);
}

template <typename T_KEY, typename T>
const typename Map<T_KEY, T>::Iterator Map<T_KEY, T>::find(const typename Map<T_KEY, T>::KEY& REF_KEY) const {
    if (implementation->current)
        if (implementation->current->object.first == REF_KEY)
            return Iterator(implementation->current);
    for (Iterator P_ITER = begin(); P_ITER != end(); ++P_ITER)
        if ((*P_ITER).first == REF_KEY)
            return (*P_ITER).second;
    return end();
}

template <typename T_KEY, typename T>
Map<T_KEY, T>& Map<T_KEY, T>::operator =(const Map<T_KEY, T>& REF) {
    if (implementation && REF.implementation) {
        ++(REF.implementation->reference);
        if (--(implementation->reference) == 0) {
            MapImplementation* OLD = implementation;
            implementation = REF.implementation;
            OLD->clear();
            delete OLD;
        } else
            implementation = REF.implementation;
    }
    return *this;
}

template <typename T_KEY, typename T>
typename Map<T_KEY, T>::TYPE& Map<T_KEY, T>::operator [](const typename Map<T_KEY, T>::KEY& REF_KEY) {
    return find(REF_KEY);
}

template <typename T_KEY, typename T>
const typename Map<T_KEY, T>::TYPE& Map<T_KEY, T>::operator [](const typename Map<T_KEY, T>::KEY& REF_KEY) const {
    return find(REF_KEY);
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
