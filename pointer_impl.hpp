/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef POINTER_IMPLEMENTATION_HEADER
#define	POINTER_IMPLEMENTATION_HEADER

#include <pointer.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
Pointer<TYPE>::Pointer(TYPE* P) : Address(P) {
}

template <typename TYPE>
Pointer<TYPE>::Pointer(const Pointer<TYPE>& REF) : Address(REF.Address) {
}

template <typename TYPE>
Pointer<TYPE>::~Pointer() {
}

template <typename TYPE>
Pointer<TYPE>& Pointer<TYPE>::Set(TYPE* P) {
    Address = P;
    return *this;
}

template <typename TYPE>
boolean Pointer<TYPE>::operator !() const {
    return !Address;
}

template <typename TYPE>
TYPE* Pointer<TYPE>::operator ->() const {
    return Address;
}

template <typename TYPE>
TYPE& Pointer<TYPE>::operator *() const {
    return *Address;
}

template <typename TYPE>
        Pointer<TYPE>& Pointer<TYPE>::operator =(const Pointer<TYPE>& REF) {
    Address = REF.Address;
    return *this;
}

template <typename TYPE>
        Pointer<TYPE>& Pointer<TYPE>::operator +=(ptrdiff DIFF) {
    Address += DIFF;
    return *this;
}

template <typename TYPE>
        Pointer<TYPE>& Pointer<TYPE>::operator -=(ptrdiff DIFF) {
    Address -= DIFF;
    return *this;
}

template <typename TYPE>
Pointer<TYPE> Pointer<TYPE>::operator +(ptrdiff DIFF) const {
    return Pointer<TYPE > (Address + DIFF);
}

template <typename TYPE>
ptrdiff Pointer<TYPE>::operator -(const Pointer<TYPE>& REF) const {
    return Address - REF.Address;
}

template <typename TYPE>
boolean Pointer<TYPE>::operator ==(const Pointer<TYPE>& REF) const {
    return Address == REF.Address;
}

template <typename TYPE>
boolean Pointer<TYPE>::operator !=(const Pointer<TYPE>& REF) const {
    return Address != REF.Address;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
