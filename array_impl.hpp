/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ARRAY_IMPLEMENTATION_HEADER
#define	ARRAY_IMPLEMENTATION_HEADER

#include <array.hpp>
#include <allocator.hpp>
#if !defined(WITHOUT_THREAD)
#include <atomicinteger.hpp>
#include <mutex.hpp>
#include <scopedlock.hpp>
#endif

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class LOCAL Array<TYPE>::ArrayImplementation : public Allocator<TYPE> {
    UNCOPYABLE(ArrayImplementation)
public:
    ArrayImplementation();
    ~ArrayImplementation();

    void Initial(const TYPE&, size);
    void Initial(TYPE*, size);
    ArrayImplementation* Duplicate();
    void Cleanup();

#if !defined(WITHOUT_THREAD)
    AtomicInteger Ref;
    Mutex MLock;
#endif
    TYPE* ArrayB;
    size ArraySize;
};

template <typename TYPE>
Array<TYPE>::ArrayImplementation::ArrayImplementation() : ArrayB(0), ArraySize(0) {
}

template <typename TYPE>
Array<TYPE>::ArrayImplementation::~ArrayImplementation() {
}

template <typename TYPE>
void Array<TYPE>::ArrayImplementation::Initial(const Array<TYPE>::VALUE& REF, size SZ) {
    if (SZ != 0) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        ArrayB = Allocator<TYPE>::Allocate(SZ);
        ArraySize = SZ;
        for (size i = 0; i < SZ; ++i)
            Construct(ArrayB + i, REF);
    }
}

template <typename TYPE>
void Array<TYPE>::ArrayImplementation::Initial(Array<TYPE>::VALUE* P, size SZ) {
    if (SZ != 0) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        ArrayB = Allocator<TYPE>::Allocate(SZ);
        ArraySize = SZ;
        if (P)
            for (size i = 0; i < SZ; ++i)
                Construct(ArrayB + i, *(P + i));
        else
            for (size i = 0; i < SZ; ++i)
                Construct(ArrayB + i, Array<TYPE>::VALUE());
    }
}

template <typename TYPE>
class Array<TYPE>::ArrayImplementation* Array<TYPE>::ArrayImplementation::Duplicate() {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
    ArrayImplementation* N_IMPL = new ArrayImplementation;
    if (N_IMPL) {
        N_IMPL->ArrayB = Allocator<TYPE>::Allocate(ArraySize);
        N_IMPL->ArraySize = ArraySize;
        for (size i = 0; i < ArraySize; ++i)
            Construct(N_IMPL->ArrayB + i, *(ArrayB + i));
    }
    return N_IMPL;
}

template <typename TYPE>
void Array<TYPE>::ArrayImplementation::Cleanup() {
    if (ArrayB) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        for (size i = 0; i < ArraySize; ++i)
            Destruct(ArrayB + i);
        Deallocate(ArrayB);
        ArrayB = 0;
        ArraySize = 0;
    }
}

template <typename TYPE>
Array<TYPE>::Array(const TYPE& REF, size SZ) : Implementation(0) {
    Implementation = new ArrayImplementation;
    if (Implementation) {
#if !defined(WITHOUT_THREAD)
        ++(Implementation->Ref);
#endif
        Implementation->Initial(REF, SZ);
    }
}

template <typename TYPE>
Array<TYPE>::Array(TYPE* P_ARRAY, size SZ) : Implementation(0) {
    Implementation = new ArrayImplementation;
    if (Implementation) {
#if !defined(WITHOUT_THREAD)
        ++(Implementation->Ref);
#endif
        Implementation->Initial(P_ARRAY, SZ);
    }
}

#if !defined(WITHOUT_THREAD)

template <typename TYPE>
Array<TYPE>::Array(const Array<TYPE>& REF) : Implementation(REF.Implementation) {
    if (Implementation)
        ++(Implementation->Ref);
}

#else

template <typename TYPE>
Array<TYPE>::Array(const Array<TYPE>& REF) : Implementation(0) {
    Implementation = new ArrayImplementation;
    if (Implementation) {
        Implementation->Initial(REF.Implementation->ArrayB, REF.Implementation->ArraySize);
    }
}

#endif

template <typename TYPE>
Array<TYPE>::~Array() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->Cleanup();
            delete Implementation;
        }
}

template <typename TYPE>
size Array<TYPE>::Size() const {
    if (Implementation)
        return Implementation->Size();
    return 0;
}

template <typename TYPE>
TYPE& Array<TYPE>::At(size IDX) {
    if (Implementation->Ref != 1) {
        ArrayImplementation* N_IMPL = Implementation->Duplicate();
        --(Implementation->Ref);
        Implementation = N_IMPL;
        ++(Implementation->Ref);
    }
    return *(Implementation->ArrayB + IDX);
}

template <typename TYPE>
const TYPE& Array<TYPE>::At(size IDX) const {
    return *(Implementation->ArrayB + IDX);
}

template <typename TYPE>
        Array<TYPE>& Array<TYPE>::operator =(const Array<TYPE>& REF) {
    if (Implementation && REF.Implementation) {
        ++(REF.Implementation->Ref);
        if (--(Implementation->Ref) == 0) {
            ArrayImplementation* OLD = Implementation;
            Implementation = REF.Implementation;
            OLD->Cleanup();
            delete OLD;
        } else
            Implementation = REF.Implementation;
    }
    return *this;
}

template <typename TYPE>
boolean Array<TYPE>::operator ==(const Array<TYPE>& REF) const {
    if (Implementation && REF.Implementation) {
        if (Implementation != REF.Implementation) {
            ScopedLock<Mutex> SL_Mutex_F(&(REF.Implementation->MLock));
            ScopedLock<Mutex> SL_Mutex_S(&(Implementation->MLock));
            if (Implementation->ArraySize != REF.Implementation->ArraySize)
                return false;
            for (size i = 0; i < Implementation->ArraySize; ++i)
                if (*(Implementation->ArrayB + i) != *(REF.Implementation->ArrayB + i))
                    return false;
        }
        return true;
    }
    return false;
}

template <typename TYPE>
boolean Array<TYPE>::operator !=(const Array<TYPE>& REF) const {
    if (Implementation && REF.Implementation) {
        if (Implementation != REF.Implementation) {
            ScopedLock<Mutex> SL_Mutex_F(&(REF.Implementation->MLock));
            ScopedLock<Mutex> SL_Mutex_S(&(Implementation->MLock));
            if (Implementation->ArraySize != REF.Implementation->ArraySize)
                return true;
            for (size i = 0; i < Implementation->ArraySize; ++i)
                if (*(Implementation->ArrayB + i) != *(REF.Implementation->ArrayB + i))
                    return true;
        }
        return false;
    }
    return true;
}

template <typename TYPE>
TYPE& Array<TYPE>::operator [](size IDX) {
    return At(IDX);
}

template <typename TYPE>
const TYPE& Array<TYPE>::operator [](size IDX) const {
    return At(IDX);
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
