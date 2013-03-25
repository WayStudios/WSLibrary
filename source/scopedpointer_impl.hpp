/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SCOPEDPOINTER_IMPLEMENTATION_HEADER
#define	SCOPEDPOINTER_IMPLEMENTATION_HEADER

#include <scopedpointer.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
ScopedPointer<TYPE>::ScopedPointer(TYPE* P) : Address(P) {
}

template <typename TYPE>
ScopedPointer<TYPE>::~ScopedPointer() {
    delete Address;
}

template <typename TYPE>
TYPE* ScopedPointer<TYPE>::Pointer() const {
    return Address;
}

template <typename TYPE>
boolean ScopedPointer<TYPE>::operator !() const {
    return !Address;
}

template <typename TYPE>
TYPE* ScopedPointer<TYPE>::operator ->() const {
    return Address;
}

template <typename TYPE>
TYPE& ScopedPointer<TYPE>::operator *() const {
    return *Address;
}

template <typename TYPE>
boolean ScopedPointer<TYPE>::operator ==(TYPE* P) const {
    return Address == P;
}

template <typename TYPE>
boolean ScopedPointer<TYPE>::operator !=(TYPE* P) const {
    return Address != P;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
