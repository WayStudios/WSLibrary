/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ALLOCATOR_IMPLEMENTATION_HEADER
#define	ALLOCATOR_IMPLEMENTATION_HEADER

#include <allocator.hpp>

BEGIN_HEADER

#if defined(_NEW) || defined(_NEW_)
#else

inline void* operator new(ws_size, void* PTR) throw () {
    return PTR;
}

inline void operator delete(void*, void*) throw () {
}

#endif

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
Allocator<TYPE>::Allocator() {
}

template <typename TYPE>
Allocator<TYPE>::~Allocator() {
}

template <typename TYPE>
TYPE* Allocator<TYPE>::Allocate(size T_SIZE) {
    void* P_ALLOC = ::operator new(T_SIZE * sizeof (TYPE));
    if (P_ALLOC)
        return reinterpret_cast<TYPE*> (P_ALLOC);
    return 0;
}

template <typename TYPE>
void Allocator<TYPE>::Deallocate(TYPE* P_ALLOC) {
    if (P_ALLOC)
        ::operator delete(P_ALLOC);
}

template <typename TYPE>
void Allocator<TYPE>::Construct(TYPE* P_T, const TYPE& REF_T) {
    if (P_T)
        new(P_T) TYPE(REF_T);
}

template <typename TYPE>
void Allocator<TYPE>::Destruct(TYPE* P_T) {
    if (P_T)
        P_T->~TYPE();
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
