/*******************************************************************************
 * WayStudio Library
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

template <typename TYPE>
class LOCAL Vector<TYPE>::VectorImplementation : public Allocator<TYPE> {
    UNCOPYABLE(VectorImplementation)
public:
    VectorImplementation();
    ~VectorImplementation();

    size Total() const;
    boolean Full() const;
    boolean Empty() const;
    VectorImplementation* Duplicate();
    void Clear();

    void Reallocate(size B_OFFSET = 0);

    void PushFront(const TYPE&);
    void PopFront();

    void PushBack(const TYPE&);
    void PopBack();

    void Remove(TYPE*);
    void Remove(const TYPE&);

#if !defined(WITHOUT_THREAD)
    AtomicInteger Ref;
    Mutex MLock;
#endif
    TYPE* VecAB;
    TYPE* VecAE;
    TYPE* VecB;
    TYPE* VecE;
};

template <typename TYPE>
class EXPORT Vector<TYPE>::Iterator {
    TYPE* Current;
public:
    explicit Iterator(TYPE*);
    Iterator(const Iterator&);
    ~Iterator();

    Iterator& operator=(const Iterator&);
    Iterator& operator++();
    Iterator& operator--();
    Iterator& operator+=(integer);
    Iterator& operator-=(integer);

    Iterator operator+(integer) const;
    Iterator operator-(integer) const;

    TYPE& operator*();

    const TYPE& operator*() const;

    boolean operator==(const Iterator&) const;
    boolean operator!=(const Iterator&) const;
};

template <typename TYPE>
Vector<TYPE>::VectorImplementation::VectorImplementation() : VecAB(0), VecAE(0), VecB(0), VecE(0) {
}

template <typename TYPE>
Vector<TYPE>::VectorImplementation::~VectorImplementation() {
}

template <typename TYPE>
size Vector<TYPE>::VectorImplementation::Total() const {
    return VecE - VecB;
}

template <typename TYPE>
boolean Vector<TYPE>::VectorImplementation::Full() const {
    return VecB == VecAB || VecE == VecAE;
}

template <typename TYPE>
boolean Vector<TYPE>::VectorImplementation::Empty() const {
    return VecB == VecE;
}

template <typename TYPE>
typename Vector<TYPE>::VectorImplementation* Vector<TYPE>::VectorImplementation::Duplicate() {
    ScopedLock<Mutex> SL_Mutex(&MLock);
    VectorImplementation* N_IMPL = new VectorImplementation;
    if (N_IMPL) {
        if (!Empty()) {
            size N_ALLOC_VOL = VecAE - VecAB;
            if (Full())
                N_ALLOC_VOL *= N_ALLOC_VOL;
            size N_VOL = Total();
            N_IMPL->VecAB = Allocator<TYPE>::Allocate(N_ALLOC_VOL);
            N_IMPL->VecAE = N_IMPL->VecAB + N_ALLOC_VOL;
            N_IMPL->VecB = N_IMPL->VecAB + (N_ALLOC_VOL - N_VOL) / 2;
            N_IMPL->VecE = N_IMPL->VecB + N_VOL;
            for (size i = 0; i < N_VOL; ++i)
                Construct(N_IMPL->VecB + i, *(VecB + i));
        }
        return N_IMPL;
    }
    return 0;
}

template <typename TYPE>
void Vector<TYPE>::VectorImplementation::Clear() {
    if (VecAB && VecAE) {
        ScopedLock<Mutex> SL_Mutex(&MLock);
        if (VecB && VecE) {
            for (TYPE* P_ITER = VecB; P_ITER != VecE; ++P_ITER)
                Destruct(P_ITER);
            VecE = VecB = 0;
        }
        Deallocate(VecAB);
        VecAE = VecAB = 0;
    }
}

template <typename TYPE>
void Vector<TYPE>::VectorImplementation::Reallocate(size B_OFFSET) {
    if (!Full())
        return;
    ScopedLock<Mutex> SL_Mutex(&MLock);
    size N_ALLOC_VOL = 2;
    if (VecAB != VecAE) {
        N_ALLOC_VOL = VecAE - VecAB;
        N_ALLOC_VOL *= N_ALLOC_VOL;
    }
    TYPE* N_VecAB = Allocator<TYPE>::Allocate(N_ALLOC_VOL);
    TYPE* N_VecAE = N_VecAB + N_ALLOC_VOL;
    TYPE* N_VecB = N_VecAB + B_OFFSET;
    TYPE* N_VecE = N_VecB;
    if (!Empty())
        for (TYPE* P_ITER = VecB; P_ITER != VecE; ++P_ITER) {
            Construct(N_VecE++, *P_ITER);
            Destruct(P_ITER);
        }
    if (VecAB)
        Deallocate(VecAB);
    VecB = N_VecB;
    VecE = N_VecE;
    VecAB = N_VecAB;
    VecAE = N_VecAE;
}

template <typename TYPE>
void Vector<TYPE>::VectorImplementation::PushFront(const TYPE& REF) {
    if (Full())
        Reallocate((VecAE - VecAB - Total()) / 2);
    ScopedLock<Mutex> SL_Mutex(&MLock);
    Construct(--VecB, REF);
}

template <typename TYPE>
void Vector<TYPE>::VectorImplementation::PopFront() {
    if (!Empty())
        if (Total() == 1)
            Clear();
        else {
            ScopedLock<Mutex> SL_Mutex(&MLock);
            Destruct(VecB++);
        }
}

template <typename TYPE>
void Vector<TYPE>::VectorImplementation::PushBack(const TYPE& REF) {
    if (Full())
        Reallocate((VecAE - VecAB - Total()) / 2);
    ScopedLock<Mutex> SL_Mutex(&MLock);
    Construct(VecE++, REF);
}

template <typename TYPE>
void Vector<TYPE>::VectorImplementation::PopBack() {
    if (!Empty())
        if (Total() == 1)
            Clear();
        else {
            ScopedLock<Mutex> SL_Mutex(&MLock);
            Destruct(--VecE);
        }
}

template <typename TYPE>
void Vector<TYPE>::VectorImplementation::Remove(TYPE* P) {
    if (!Empty()) {
        if (P == VecB)
            return PopFront();
        if (P == (VecE - 1))
            return PopBack();
        if (P > VecB && P < VecE) {
            ScopedLock<Mutex> SL_Mutex(&MLock);
            Destruct(P);
            if ((P - VecB) >= (Total() / 2)) {
                for (TYPE* P_ITER = (P + 1); P_ITER != VecE; ++P_ITER) {
                    Construct(P++, *P_ITER);
                    Destruct(P_ITER);
                }
                --VecE;
            } else {
                TYPE* MAX = VecB - 1;
                for (TYPE* P_ITER = (P - 1); P_ITER != MAX; --P_ITER) {
                    Construct(P--, *P_ITER);
                    Destruct(P_ITER);
                }
                ++VecB;
            }
        }
    }
}

template <typename TYPE>
void Vector<TYPE>::VectorImplementation::Remove(const TYPE& REF) {
    if (!Empty()) {
        ScopedLock<Mutex> SL_Mutex(&MLock);
        for (TYPE* P_ITER = VecB; P_ITER != VecE; ++P_ITER)
            if ((*P_ITER) == REF) {
                if (P_ITER == VecB) {
                    Destruct(VecB++);
                    return;
                }
                if (P_ITER == (VecE - 1)) {
                    Destruct(--VecE);
                    return;
                }
                Destruct(P_ITER);
                if (static_cast<size> ((P_ITER - VecB)) >= static_cast<size> ((Total() / 2))) {
                    for (TYPE* P_ITER_S = (P_ITER + 1); P_ITER_S != VecE; ++P_ITER_S) {
                        Construct(P_ITER++, *P_ITER_S);
                        Destruct(P_ITER_S);
                    }
                    --VecE;
                } else {
                    TYPE* MAX = VecB - 1;
                    for (TYPE* P_ITER_S = (P_ITER - 1); P_ITER_S != MAX; --P_ITER_S) {
                        Construct(P_ITER--, *P_ITER_S);
                        Destruct(P_ITER_S);
                    }
                    ++VecB;
                }
                return;
            }
    }
}

template <typename TYPE>
Vector<TYPE>::Iterator::Iterator(TYPE* P_ITER) : Current(P_ITER) {
}

template <typename TYPE>
Vector<TYPE>::Iterator::Iterator(const Iterator& REF) : Current(REF.Current) {
}

template <typename TYPE>
Vector<TYPE>::Iterator::~Iterator() {
}

template <typename TYPE>
        typename Vector<TYPE>::Iterator& Vector<TYPE>::Iterator::operator =(const Iterator& REF) {
    Current = REF.Current;
    return *this;
}

template <typename TYPE>
typename Vector<TYPE>::Iterator& Vector<TYPE>::Iterator::operator ++() {
    ++Current;
    return *this;
}

template <typename TYPE>
typename Vector<TYPE>::Iterator& Vector<TYPE>::Iterator::operator --() {
    --Current;
    return *this;
}

template <typename TYPE>
        typename Vector<TYPE>::Iterator& Vector<TYPE>::Iterator::operator +=(integer DIFF) {
    Current += DIFF;
    return *this;
}

template <typename TYPE>
        typename Vector<TYPE>::Iterator& Vector<TYPE>::Iterator::operator -=(integer DIFF) {
    Current -= DIFF;
    return *this;
}

template <typename TYPE>
typename Vector<TYPE>::Iterator Vector<TYPE>::Iterator::operator +(integer DIFF) const {
    return Iterator(Current + DIFF);
}

template <typename TYPE>
typename Vector<TYPE>::Iterator Vector<TYPE>::Iterator::operator -(integer DIFF) const {
    return Iterator(Current - DIFF);
}

template <typename TYPE>
TYPE& Vector<TYPE>::Iterator::operator *() {
    return *Current;
}

template <typename TYPE>
const TYPE& Vector<TYPE>::Iterator::operator *() const {
    return *Current;
}

template <typename TYPE>
boolean Vector<TYPE>::Iterator::operator ==(const Iterator& REF) const {
    return Current == REF.Current;
}

template <typename TYPE>
boolean Vector<TYPE>::Iterator::operator !=(const Iterator& REF) const {
    return Current != REF.Current;
}

template <typename TYPE>
Vector<TYPE>::Vector() : Implementation(0) {
    Implementation = new VectorImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

template <typename TYPE>
Vector<TYPE>::Vector(const Vector<TYPE>& REF) : Implementation(REF.Implementation) {
    if (Implementation)
        ++(Implementation->Ref);
}

template <typename TYPE>
Vector<TYPE>::~Vector() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->Clear();
            delete Implementation;
        }
}

template <typename TYPE>
size Vector<TYPE>::Total() const {
    if (Implementation)
        return Implementation->Total();
    return 0;
}

template <typename TYPE>
boolean Vector<TYPE>::Empty() const {
    if (Implementation)
        return Implementation->Empty();
    return true;
}

template <typename TYPE>
void Vector<TYPE>::Clear() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->Clear();
            delete Implementation;
        }
    Implementation = new VectorImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

template <typename TYPE>
boolean Vector<TYPE>::Exist(const TYPE& REF) const {
    if (Implementation) {
        ScopedLock<Mutex> SL_Mutex(&(Implementation->MLock));
        for (Iterator P_ITER = Begin(); P_ITER != End(); ++P_ITER)
            if (*P_ITER == REF)
                return true;
    }
    return false;
}

template <typename TYPE>
TYPE& Vector<TYPE>::First() {
    if (Implementation->Ref != 1) {
        VectorImplementation* N_IMPL = Implementation->Duplicate();
        --(Implementation->Ref);
        Implementation = N_IMPL;
        ++(Implementation->Ref);
    }
    return *(Implementation->VecB);
}

template <typename TYPE>
TYPE& Vector<TYPE>::Last() {
    if (Implementation->Ref != 1) {
        VectorImplementation* N_IMPL = Implementation->Duplicate();
        --(Implementation->Ref);
        Implementation = N_IMPL;
        ++(Implementation->Ref);
    }
    return *(Implementation->VecE - 1);
}

template <typename TYPE>
TYPE& Vector<TYPE>::At(size IDX) {
    if (Implementation->Ref != 1) {
        VectorImplementation* N_IMPL = Implementation->Duplicate();
        --(Implementation->Ref);
        Implementation = N_IMPL;
        ++(Implementation->Ref);
    }
    return *(Implementation->VecB + IDX);
}

template <typename TYPE>
const TYPE& Vector<TYPE>::First() const {
    return *(Implementation->VecB);
}

template <typename TYPE>
const TYPE& Vector<TYPE>::Last() const {
    return *(Implementation->VecE - 1);
}

template <typename TYPE>
const TYPE& Vector<TYPE>::At(size IDX) const {
    return *(Implementation->VecB + IDX);
}

template <typename TYPE>
void Vector<TYPE>::PushFront(const TYPE& REF) {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            VectorImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->PushFront(REF);
    }
}

template <typename TYPE>
void Vector<TYPE>::PopFront() {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            VectorImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->PopFront();
    }
}

template <typename TYPE>
void Vector<TYPE>::PushBack(const TYPE& REF) {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            VectorImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->PushBack(REF);
    }
}

template <typename TYPE>
void Vector<TYPE>::PopBack() {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            VectorImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->PopBack();
    }
}

template <typename TYPE>
void Vector<TYPE>::Append(const TYPE& REF) {
    PushBack(REF);
}

template <typename TYPE>
void Vector<TYPE>::Remove(const TYPE& REF) {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            VectorImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->Remove(REF);
    }
}

template <typename TYPE>
typename Vector<TYPE>::Iterator Vector<TYPE>::Begin() {
    if (Implementation)
        return Iterator(Implementation->VecB);
    return Iterator(0);
}

template <typename TYPE>
typename Vector<TYPE>::Iterator Vector<TYPE>::End() {
    if (Implementation)
        return Iterator(Implementation->VecE);
    return Iterator(0);
}

template <typename TYPE>
const typename Vector<TYPE>::Iterator Vector<TYPE>::Begin() const {
    if (Implementation)
        return Iterator(Implementation->VecB);
    return Iterator(0);
}

template <typename TYPE>
const typename Vector<TYPE>::Iterator Vector<TYPE>::End() const {
    if (Implementation)
        return Iterator(Implementation->VecE);
    return Iterator(0);
}

template <typename TYPE>
        Vector<TYPE>& Vector<TYPE>::operator =(const Vector<TYPE>& REF) {
    if (Implementation && REF.Implementation) {
        ++(REF.Implementation->Ref);
        if (--(Implementation->Ref) == 0) {
            VectorImplementation* OLD = Implementation;
            Implementation = REF.Implementation;
            OLD->Clear();
            delete OLD;
        } else
            Implementation = REF.Implementation;
    }
    return *this;
}

template <typename TYPE>
boolean Vector<TYPE>::operator ==(const Vector<TYPE>& REF) const {
    if (Implementation && REF.Implementation) {
        if (Implementation != REF.Implementation) {
            ScopedLock<Mutex> SL_Mutex_F(&(REF.Implementation->MLock));
            ScopedLock<Mutex> SL_Mutex_S(&(Implementation->MLock));
            size MAX = Total();
            if (MAX != REF.Total())
                return false;
            for (size i = 0; i < MAX; ++i)
                if (*(Implementation->VecB + i) != *(REF.Implementation->VecB + i))
                    return false;
        }
        return true;
    }
    return false;
}

template <typename TYPE>
boolean Vector<TYPE>::operator !=(const Vector<TYPE>& REF) const {
    if (Implementation && REF.Implementation) {
        if (Implementation != REF.Implementation) {
            ScopedLock<Mutex> SL_Mutex_F(&(REF.Implementation->MLock));
            ScopedLock<Mutex> SL_Mutex_S(&(Implementation->MLock));
            size MAX = Total();
            if (MAX != REF.Total())
                return true;
            for (size i = 0; i < MAX; ++i)
                if (*(Implementation->VecB + i) != *(REF.Implementation->VecB + i))
                    return true;
        }
        return false;
    }
    return true;
}

template <typename TYPE>
TYPE& Vector<TYPE>::operator [](size IDX) {
    return At(IDX);
}

template <typename TYPE>
const TYPE& Vector<TYPE>::operator [](size IDX) const {
    return At(IDX);
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
