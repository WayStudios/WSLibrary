/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef VECTOR_IMPLEMENTATION_HEADER
#define	VECTOR_IMPLEMENTATION_HEADER

#include <vector.hpp>
#include <allocator.hpp>
#include <atomicinteger.hpp>
#include <mutex.hpp>
#include <scopedlock.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
class LOCAL Vector<T>::VectorImplementation : public Allocator<typename Vector<T>::TYPE> {
    UNCOPYABLE(VectorImplementation)
public:
    VectorImplementation();
    ~VectorImplementation();

    SIZE total() const;
    BOOLEAN full() const;
    BOOLEAN empty() const;
    VectorImplementation* duplicate();
    void clear();

    void reallocate(SIZE B_OFFSET = 0);

    void pushFront(const typename Vector<T>::TYPE&);
    void popFront();

    void pushBack(const typename Vector<T>::TYPE&);
    void popBack();

    void remove(typename Vector<T>::TYPE*);
    void remove(const typename Vector<T>::TYPE&);

#if !defined(WITHOUT_THREAD)
    AtomicInteger reference;
    Mutex mutex;
#endif
    typename Vector<T>::TYPE* allocatedBegin;
    typename Vector<T>::TYPE* allocatedEnd;
    typename Vector<T>::TYPE* begin;
    typename Vector<T>::TYPE* end;
};

template <typename T>
class EXPORT Vector<T>::Iterator {
    typename Vector<T>::TYPE* current;
public:
    explicit Iterator(typename Vector<T>::TYPE*);
    Iterator(const Iterator&);
    ~Iterator();

    Iterator& operator =(const Iterator&);
    Iterator& operator ++();
    Iterator& operator --();
    Iterator& operator +=(INTEGER);
    Iterator& operator -=(INTEGER);

    Iterator operator +(INTEGER) const;
    Iterator operator -(INTEGER) const;

    typename Vector<T>::TYPE& operator *();

    const typename Vector<T>::TYPE& operator *() const;

    BOOLEAN operator ==(const Iterator&) const;
    BOOLEAN operator !=(const Iterator&) const;
};

template <typename T>
Vector<T>::VectorImplementation::VectorImplementation() : allocatedBegin(0), allocatedEnd(0), begin(0), end(0) {
}

template <typename T>
Vector<T>::VectorImplementation::~VectorImplementation() {
}

template <typename T>
SIZE Vector<T>::VectorImplementation::total() const {
    return end - begin;
}

template <typename T>
BOOLEAN Vector<T>::VectorImplementation::full() const {
    return begin == allocatedBegin || end == allocatedEnd;
}

template <typename T>
BOOLEAN Vector<T>::VectorImplementation::empty() const {
    return begin == end;
}

template <typename T>
typename Vector<T>::VectorImplementation* Vector<T>::VectorImplementation::duplicate() {
    ScopedLock<Mutex> SL_MUTEX(&mutex);
    VectorImplementation* N_IMPL = new VectorImplementation;
    if (N_IMPL) {
        if (!empty()) {
            SIZE N_ALLOC_VOL = allocatedEnd - allocatedBegin;
            if (full())
                N_ALLOC_VOL *= N_ALLOC_VOL;
            SIZE N_VOL = total();
            N_IMPL->allocatedBegin = allocate(N_ALLOC_VOL);
            N_IMPL->allocatedEnd = N_IMPL->allocatedBegin + N_ALLOC_VOL;
            N_IMPL->begin = N_IMPL->allocatedBegin + (N_ALLOC_VOL - N_VOL) / 2;
            N_IMPL->end = N_IMPL->begin + N_VOL;
            for (SIZE i = 0; i < N_VOL; ++i)
                construct(N_IMPL->begin + i, *(begin + i));
        }
        return N_IMPL;
    }
    return 0;
}

template <typename T>
void Vector<T>::VectorImplementation::clear() {
    if (allocatedBegin && allocatedEnd) {
        ScopedLock<Mutex> SL_MUTEX(&mutex);
        if (begin && end) {
            for (Vector<T>::TYPE* P_ITER = begin; P_ITER != end; ++P_ITER)
                destruct(P_ITER);
            end = begin = 0;
        }
        deallocate(allocatedBegin);
        allocatedEnd = allocatedBegin = 0;
    }
}

template <typename T>
void Vector<T>::VectorImplementation::reallocate(SIZE B_OFFSET) {
    if (!full())
        return;
    ScopedLock<Mutex> SL_MUTEX(&mutex);
    SIZE N_ALLOC_VOL = 2;
    if (allocatedBegin != allocatedEnd) {
        N_ALLOC_VOL = allocatedEnd - allocatedBegin;
        N_ALLOC_VOL *= N_ALLOC_VOL;
    }
    Vector<T>::TYPE* N_VecAB = allocate(N_ALLOC_VOL);
    Vector<T>::TYPE* N_VecAE = N_VecAB + N_ALLOC_VOL;
    Vector<T>::TYPE* N_VecB = N_VecAB + B_OFFSET;
    Vector<T>::TYPE* N_VecE = N_VecB;
    if (!empty())
        for (Vector<T>::TYPE* P_ITER = begin; P_ITER != end; ++P_ITER) {
            construct(N_VecE++, *P_ITER);
            destruct(P_ITER);
        }
    if (allocatedBegin)
        deallocate(allocatedBegin);
    begin = N_VecB;
    end = N_VecE;
    allocatedBegin = N_VecAB;
    allocatedEnd = N_VecAE;
}

template <typename T>
void Vector<T>::VectorImplementation::pushFront(const typename Vector<T>::TYPE& REF) {
    if (full())
        reallocate((allocatedEnd - allocatedBegin - total()) / 2);
    ScopedLock<Mutex> SL_MUTEX(&mutex);
    construct(--begin, REF);
}

template <typename T>
void Vector<T>::VectorImplementation::popFront() {
    if (!empty())
        if (total() == 1)
            clear();
        else {
            ScopedLock<Mutex> SL_MUTEX(&mutex);
            destruct(begin++);
        }
}

template <typename T>
void Vector<T>::VectorImplementation::pushBack(const typename  Vector<T>::TYPE& REF) {
    if (full())
        reallocate((allocatedEnd - allocatedBegin - total()) / 2);
    ScopedLock<Mutex> SL_MUTEX(&mutex);
    construct(end++, REF);
}

template <typename T>
void Vector<T>::VectorImplementation::popBack() {
    if (!empty())
        if (total() == 1)
            clear();
        else {
            ScopedLock<Mutex> SL_MUTEX(&mutex);
            destruct(--end);
        }
}

template <typename T>
void Vector<T>::VectorImplementation::remove(typename Vector<T>::TYPE* P) {
    if (!empty()) {
        if (P == begin)
            return popFront();
        if (P == (end - 1))
            return popBack();
        if (P > begin && P < end) {
            ScopedLock<Mutex> SL_MUTEX(&mutex);
            destruct(P);
            if ((P - begin) >= (total() / 2)) {
                for (TYPE* P_ITER = (P + 1); P_ITER != end; ++P_ITER) {
                    construct(P++, *P_ITER);
                    destruct(P_ITER);
                }
                --end;
            } else {
                TYPE* MAX = begin - 1;
                for (TYPE* P_ITER = (P - 1); P_ITER != MAX; --P_ITER) {
                    construct(P--, *P_ITER);
                    destruct(P_ITER);
                }
                ++begin;
            }
        }
    }
}

template <typename T>
void Vector<T>::VectorImplementation::remove(const typename Vector<T>::TYPE& REF) {
    if (!empty()) {
        ScopedLock<Mutex> SL_MUTEX(&mutex);
        for (TYPE* P_ITER = begin; P_ITER != end; ++P_ITER)
            if ((*P_ITER) == REF) {
                if (P_ITER == begin) {
                    destruct(begin++);
                    return;
                }
                if (P_ITER == (end - 1)) {
                    destruct(--end);
                    return;
                }
                destruct(P_ITER);
                if (static_cast<SIZE> ((P_ITER - begin)) >= static_cast<SIZE> ((total() / 2))) {
                    for (TYPE* P_ITER_S = (P_ITER + 1); P_ITER_S != end; ++P_ITER_S) {
                        construct(P_ITER++, *P_ITER_S);
                        destruct(P_ITER_S);
                    }
                    --end;
                } else {
                    TYPE* MAX = begin - 1;
                    for (TYPE* P_ITER_S = (P_ITER - 1); P_ITER_S != MAX; --P_ITER_S) {
                        construct(P_ITER--, *P_ITER_S);
                        destruct(P_ITER_S);
                    }
                    ++begin;
                }
                return;
            }
    }
}

template <typename T>
Vector<T>::Iterator::Iterator(typename Vector<T>::TYPE* P_ITER) : current(P_ITER) {
}

template <typename T>
Vector<T>::Iterator::Iterator(const typename Vector<T>::Iterator& REF) : current(REF.current) {
}

template <typename T>
Vector<T>::Iterator::~Iterator() {
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator =(const Iterator& REF) {
    current = REF.current;
    return *this;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator ++() {
    ++current;
    return *this;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator --() {
    --current;
    return *this;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator +=(INTEGER DIFF) {
    current += DIFF;
    return *this;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator -=(INTEGER DIFF) {
    current -= DIFF;
    return *this;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator +(INTEGER DIFF) const {
    return Iterator(current + DIFF);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator -(INTEGER DIFF) const {
    return Iterator(current - DIFF);
}

template <typename T>
typename Vector<T>::TYPE& Vector<T>::Iterator::operator *() {
    return *current;
}

template <typename T>
const typename Vector<T>::TYPE& Vector<T>::Iterator::operator *() const {
    return *current;
}

template <typename T>
BOOLEAN Vector<T>::Iterator::operator ==(const typename Vector<T>::Iterator& REF) const {
    return current == REF.current;
}

template <typename T>
BOOLEAN Vector<T>::Iterator::operator !=(const typename Vector<T>::Iterator& REF) const {
    return current != REF.current;
}

template <typename T>
Vector<T>::Vector() : implementation(0) {
    implementation = new VectorImplementation;
    if (implementation)
        ++(implementation->reference);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& REF) : implementation(REF.implementation) {
    if (implementation)
        ++(implementation->reference);
}

template <typename T>
Vector<T>::~Vector() {
    if (implementation)
        if (--(implementation->reference) == 0) {
            implementation->clear();
            delete implementation;
        }
}

template <typename T>
SIZE Vector<T>::total() const {
    if (implementation)
        return implementation->total();
    return 0;
}

template <typename T>
BOOLEAN Vector<T>::empty() const {
    if (implementation)
        return implementation->empty();
    return true;
}

template <typename T>
void Vector<T>::clear() {
    if (implementation)
        if (--(implementation->reference) == 0) {
            implementation->clear();
            delete implementation;
        }
    implementation = new VectorImplementation;
    if (implementation)
        ++(implementation->reference);
}

template <typename T>
BOOLEAN Vector<T>::exist(const typename Vector<T>::TYPE& REF) const {
    if (implementation) {
        ScopedLock<Mutex> SL_MUTEX(&(implementation->mutex));
        for (Iterator P_ITER = begin(); P_ITER != end(); ++P_ITER)
            if (*P_ITER == REF)
                return true;
    }
    return false;
}

template <typename T>
typename Vector<T>::TYPE& Vector<T>::first() {
    if (implementation->reference != 1) {
        VectorImplementation* N_IMPL = implementation->duplicate();
        --(implementation->reference);
        implementation = N_IMPL;
        ++(implementation->reference);
    }
    return *(implementation->begin);
}

template <typename T>
typename Vector<T>::TYPE& Vector<T>::last() {
    if (implementation->reference != 1) {
        VectorImplementation* N_IMPL = implementation->duplicate();
        --(implementation->reference);
        implementation = N_IMPL;
        ++(implementation->reference);
    }
    return *(implementation->end - 1);
}

template <typename T>
typename Vector<T>::TYPE& Vector<T>::at(SIZE IDX) {
    if (implementation->reference != 1) {
        VectorImplementation* N_IMPL = implementation->duplicate();
        --(implementation->reference);
        implementation = N_IMPL;
        ++(implementation->reference);
    }
    return *(implementation->begin + IDX);
}

template <typename T>
const typename Vector<T>::TYPE& Vector<T>::first() const {
    return *(implementation->begin);
}

template <typename T>
const typename Vector<T>::TYPE& Vector<T>::last() const {
    return *(implementation->end - 1);
}

template <typename T>
const typename Vector<T>::TYPE& Vector<T>::at(SIZE IDX) const {
    return *(implementation->begin + IDX);
}

template <typename T>
void Vector<T>::pushFront(const typename Vector<T>::TYPE& REF) {
    if (implementation) {
        if (implementation->reference != 1) {
            VectorImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->pushFront(REF);
    }
}

template <typename T>
void Vector<T>::popFront() {
    if (implementation) {
        if (implementation->reference != 1) {
            VectorImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->popFront();
    }
}

template <typename T>
void Vector<T>::pushBack(const typename Vector<T>::TYPE& REF) {
    if (implementation) {
        if (implementation->reference != 1) {
            VectorImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->pushBack(REF);
    }
}

template <typename T>
void Vector<T>::popBack() {
    if (implementation) {
        if (implementation->reference != 1) {
            VectorImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->popBack();
    }
}

template <typename T>
void Vector<T>::append(const typename Vector<T>::TYPE& REF) {
    pushBack(REF);
}

template <typename T>
void Vector<T>::remove(const typename Vector<T>::TYPE& REF) {
    if (implementation) {
        if (implementation->reference != 1) {
            VectorImplementation* N_IMPL = implementation->duplicate();
            --(implementation->reference);
            implementation = N_IMPL;
            ++(implementation->reference);
        }
        implementation->remove(REF);
    }
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin() {
    if (implementation)
        return Iterator(implementation->begin);
    return Iterator(0);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end() {
    if (implementation)
        return Iterator(implementation->end);
    return Iterator(0);
}

template <typename T>
const typename Vector<T>::Iterator Vector<T>::begin() const {
    if (implementation)
        return Iterator(implementation->begin);
    return Iterator(0);
}

template <typename T>
const typename Vector<T>::Iterator Vector<T>::end() const {
    if (implementation)
        return Iterator(implementation->end);
    return Iterator(0);
}

template <typename T>
Vector<T>& Vector<T>::operator =(const Vector<T>& REF) {
    if (implementation && REF.implementation) {
        ++(REF.implementation->reference);
        if (--(implementation->reference) == 0) {
            VectorImplementation* OLD = implementation;
            implementation = REF.implementation;
            OLD->clear();
            delete OLD;
        } else
            implementation = REF.implementation;
    }
    return *this;
}

template <typename T>
BOOLEAN Vector<T>::operator ==(const Vector<T>& REF) const {
    if (implementation && REF.implementation) {
        if (implementation != REF.implementation) {
            ScopedLock<Mutex> SL_MUTEX_F(&(REF.implementation->mutex));
            ScopedLock<Mutex> SL_MUTEX_S(&(implementation->mutex));
            SIZE MAX = total();
            if (MAX != REF.total())
                return false;
            for (SIZE i = 0; i < MAX; ++i)
                if (*(implementation->begin + i) != *(REF.implementation->begin + i))
                    return false;
        }
        return true;
    }
    return false;
}

template <typename T>
BOOLEAN Vector<T>::operator !=(const Vector<T>& REF) const {
    if (implementation && REF.implementation) {
        if (implementation != REF.implementation) {
            ScopedLock<Mutex> SL_MUTEX_F(&(REF.implementation->mutex));
            ScopedLock<Mutex> SL_MUTEX_S(&(implementation->mutex));
            SIZE MAX = total();
            if (MAX != REF.total())
                return true;
            for (SIZE i = 0; i < MAX; ++i)
                if (*(implementation->begin + i) != *(REF.implementation->begin + i))
                    return true;
        }
        return false;
    }
    return true;
}

template <typename T>
typename Vector<T>::TYPE& Vector<T>::operator [](SIZE IDX) {
    return at(IDX);
}

template <typename T>
const typename Vector<T>::TYPE& Vector<T>::operator [](SIZE IDX) const {
    return at(IDX);
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
