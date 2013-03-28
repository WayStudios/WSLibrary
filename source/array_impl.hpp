/*******************************************************************************
 * Way Studios Library
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

template <typename T>
class LOCAL Array<T>::ArrayImplementation : public Allocator<Array<T>::TYPE> {
    UNCOPYABLE(ArrayImplementation)
public:
    ArrayImplementation();
    ~ArrayImplementation();

    void initialize(const TYPE&, SIZE);
    void initialize(TYPE*, SIZE);
    ArrayImplementation* duplicate();
    void destroy();

#if !defined(WITHOUT_THREAD)
    AtomicInteger reference;
    Mutex mutex;
#endif
    Array<T>::TYPE* array;
    SIZE size;
};

template <typename T>
Array<T>::ArrayImplementation::ArrayImplementation() : array(0), size(0) {
}

template <typename T>
Array<T>::ArrayImplementation::~ArrayImplementation() {
}

template <typename T>
void Array<T>::ArrayImplementation::initialize(const Array<T>::TYPE& REF, SIZE SZ) {
    if (SZ != 0) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        array = allocate(SZ);
        size = SZ;
        for (SIZE i = 0; i < SZ; ++i)
            construct(array + i, REF);
    }
}

template <typename T>
void Array<T>::ArrayImplementation::initialize(Array<T>::TYPE* P, SIZE SZ) {
    if (SZ != 0) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        array = allocate(SZ);
        size = SZ;
        if (P)
            for (SIZE i = 0; i < SZ; ++i)
                construct(array + i, *(P + i));
        else
            for (SIZE i = 0; i < SZ; ++i)
                construct(array + i, Array<T>::TYPE());
    }
}

template <typename T>
class Array<T>::ArrayImplementation* Array<T>::ArrayImplementation::duplicate() {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
    ArrayImplementation* N_IMPL = new ArrayImplementation;
    if (N_IMPL) {
        N_IMPL->array = allocate(size);
        N_IMPL->size = size;
        for (SIZE i = 0; i < size; ++i)
            construct(N_IMPL->array + i, *(array + i));
    }
    return N_IMPL;
}

template <typename T>
void Array<T>::ArrayImplementation::destroy() {
    if (array) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        for (SIZE i = 0; i < size; ++i)
            destruct(array + i);
        deallocate(array);
        array = 0;
        size = 0;
    }
}

template <typename T>
Array<T>::Array(const Array<T>::TYPE& REF, SIZE SZ) : implementation(0) {
    implementation = new ArrayImplementation;
    if (implementation) {
#if !defined(WITHOUT_THREAD)
        ++(implementation->reference);
#endif
        implementation->initialize(REF, SZ);
    }
}

template <typename T>
Array<T>::Array(Array<T>::TYPE* P_ARRAY, SIZE SZ) : implementation(0) {
    implementation = new ArrayImplementation;
    if (implementation) {
#if !defined(WITHOUT_THREAD)
        ++(implementation->reference);
#endif
        implementation->initialize(P_ARRAY, SZ);
    }
}

#if !defined(WITHOUT_THREAD)

template <typename T>
Array<T>::Array(const Array<T>& REF) : implementation(REF.implementation) {
    if (implementation)
        ++(implementation->reference);
}

#else

template <typename T>
Array<T>::Array(const Array<T>& REF) : implementation(0) {
    implementation = new ArrayImplementation;
    if (implementation) {
        implementation->initial(REF.implementation->array, REF.implementation->size);
    }
}

#endif

template <typename T>
Array<T>::~Array() {
    if (implementation)
        if (--(implementation->ref) == 0) {
            implementation->cleanup();
            delete implementation;
        }
}

template <typename T>
SIZE Array<T>::size() const {
    if (implementation)
        return implementation->size();
    return 0;
}

template <typename T>
Array<T>::TYPE& Array<T>::at(SIZE IDX) {
    if (implementation->ref != 1) {
        ArrayImplementation* N_IMPL = implementation->duplicate();
        --(implementation->reference);
        implementation = N_IMPL;
        ++(implementation->reference);
    }
    return *(implementation->array + IDX);
}

template <typename T>
const Array<T>::TYPE& Array<T>::at(SIZE IDX) const {
    return *(implementation->array + IDX);
}

template <typename T>
Array<T>& Array<T>::operator =(const Array<T>& REF) {
    if (implementation && REF.implementation) {
        ++(REF.implementation->ref);
        if (--(implementation->ref) == 0) {
            ArrayImplementation* OLD = implementation;
            implementation = REF.implementation;
            OLD->cleanup();
            delete OLD;
        } else
            implementation = REF.implementation;
    }
    return *this;
}

template <typename T>
BOOLEAN Array<T>::operator ==(const Array<T>& REF) const {
    if (implementation && REF.implementation) {
        if (implementation != REF.implementation) {
            ScopedLock<Mutex> SL_MUTEX_F(&(REF.implementation->mutex));
            ScopedLock<Mutex> SL_MUTEX_S(&(implementation->mutex));
            if (implementation->size != REF.implementation->size)
                return false;
            for (SIZE i = 0; i < implementation->size; ++i)
                if (*(implementation->array + i) != *(REF.implementation->array + i))
                    return false;
        }
        return true;
    }
    return false;
}

template <typename T>
BOOLEAN Array<T>::operator !=(const Array<T>& REF) const {
    if (implementation && REF.implementation) {
        if (implementation != REF.implementation) {
            ScopedLock<Mutex> SL_MUTEX_F(&(REF.implementation->mutex));
            ScopedLock<Mutex> SL_MUTEX_S(&(implementation->mutex));
            if (implementation->size != REF.implementation->size)
                return true;
            for (SIZE i = 0; i < implementation->size; ++i)
                if (*(implementation->array + i) != *(REF.implementation->array + i))
                    return true;
        }
        return false;
    }
    return true;
}

template <typename T>
Array<T>::TYPE& Array<T>::operator [](SIZE IDX) {
    return at(IDX);
}

template <typename T>
const Array<T>::TYPE& Array<T>::operator [](SIZE IDX) const {
    return at(IDX);
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
