/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef POINTER_IMPLEMENTATION_HEADER
#define	POINTER_IMPLEMENTATION_HEADER

#include <pointer.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
Pointer<TYPE>::Pointer(TYPE* P) : address(P) {
}

template <typename TYPE>
Pointer<TYPE>::Pointer(const Pointer<TYPE>& REF) : address(REF.address) {
}

template <typename TYPE>
Pointer<TYPE>::~Pointer() {
}

template <typename TYPE>
Pointer<TYPE>& Pointer<TYPE>::Set(TYPE* P) {
    address = P;
    return *this;
}

template <typename TYPE>
BOOLEAN Pointer<TYPE>::operator !() const {
    return !address;
}

template <typename TYPE>
TYPE* Pointer<TYPE>::operator ->() const {
    return address;
}

template <typename TYPE>
TYPE& Pointer<TYPE>::operator *() const {
    return *address;
}

template <typename TYPE>
Pointer<TYPE>& Pointer<TYPE>::operator =(const Pointer<TYPE>& REF) {
    address = REF.address;
    return *this;
}

template <typename TYPE>
Pointer<TYPE>& Pointer<TYPE>::operator +=(PTRDIFF DIFF) {
    address += DIFF;
    return *this;
}

template <typename TYPE>
Pointer<TYPE>& Pointer<TYPE>::operator -=(PTRDIFF DIFF) {
    address -= DIFF;
    return *this;
}

template <typename TYPE>
Pointer<TYPE> Pointer<TYPE>::operator +(PTRDIFF DIFF) const {
    return Pointer<TYPE>(address + DIFF);
}

template <typename TYPE>
PTRDIFF Pointer<TYPE>::operator -(const Pointer<TYPE>& REF) const {
    return address - REF.address;
}

template <typename TYPE>
BOOLEAN Pointer<TYPE>::operator ==(const Pointer<TYPE>& REF) const {
    return address == REF.address;
}

template <typename TYPE>
BOOLEAN Pointer<TYPE>::operator !=(const Pointer<TYPE>& REF) const {
    return address != REF.address;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
