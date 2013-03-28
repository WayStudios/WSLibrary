/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ALLOCATOR_IMPLEMENTATION_HEADER
#define	ALLOCATOR_IMPLEMENTATION_HEADER

#include <allocator.hpp>

BEGIN_HEADER

#if defined(_NEW) || defined(_NEW_)
#else

inline void* operator new(WS::SIZE, void* PTR) throw () {
    return PTR;
}

inline void operator delete(void*, void*) throw () {
}

#endif

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
Allocator<T>::Allocator() {
}

template <typename T>
Allocator<T>::~Allocator() {
}

template <typename T>
typename Allocator<T>::TYPE* Allocator<T>::allocate(SIZE T_SIZE) {
    void* P_ALLOC = ::operator new(T_SIZE * sizeof (Allocator<T>::TYPE));
    if (P_ALLOC)
        return reinterpret_cast<Allocator<T>::TYPE*> (P_ALLOC);
    return 0;
}

template <typename T>
void Allocator<T>::deallocate(typename Allocator<T>::TYPE* P_ALLOC) {
    if (P_ALLOC)
        ::operator delete(P_ALLOC);
}

template <typename T>
void Allocator<T>::construct(typename Allocator<T>::TYPE* P_T, const typename Allocator<T>::TYPE& REF_T) {
    if (P_T)
        new(P_T) Allocator<T>::TYPE(REF_T);
}

template <typename T>
void Allocator<T>::destruct(typename Allocator<T>::TYPE* P_T) {
    if (P_T)
        P_T->~TYPE();
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
