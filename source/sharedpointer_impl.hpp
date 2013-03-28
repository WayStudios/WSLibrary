/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SHAREDPOINTER_IMPLEMENTATION_HEADER
#define	SHAREDPOINTER_IMPLEMENTATION_HEADER

#include <sharedpointer.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
SharedPointer<T>::SharedPointer(typename SharedPointer<T>::TYPE * P_ADDR) : implementation(0) {
    implementation = new SmartPointerImplementation<TYPE>(P_ADDR);
    if (implementation)
        ++(implementation->sharedReference);
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& REF) : implementation(REF.implementation) {
    if (implementation)
        ++(implementation->sharedReference);
}

template <typename T>
SharedPointer<T>::~SharedPointer() {
    if (implementation)
        if (--(implementation->sharedReference) == 0) {
            delete implementation->address;
            if ((implementation->weakReference) == 0)
                delete implementation;
            else
                implementation->address = 0;
        }
}

template <typename T>
typename SharedPointer<T>::TYPE* SharedPointer<T>::address() const {
    if (implementation)
        return implementation->address;
    return 0;
}

template <typename T>
SharedPointer<T>::operator bool() const {
    if (implementation)
        return implementation->address != 0;
    return false;
}

template <typename T>
BOOLEAN SharedPointer<T>::operator !() const {
    if (implementation)
        return !implementation->address;
    return true;
}

template <typename T>
typename SharedPointer<T>::TYPE* SharedPointer<T>::operator ->() const {
    if (implementation)
        return implementation->address;
    return 0;
}

template <typename T>
typename SharedPointer<T>::TYPE& SharedPointer<T>::operator *() const {
    if (implementation)
        return *(implementation->address);
    throw;
}

template <typename T>
BOOLEAN SharedPointer<T>::operator ==(const SharedPointer<T>& REF) const {
    return implementation == REF.implementation;
}

template <typename T>
BOOLEAN SharedPointer<T>::operator !=(const SharedPointer<T>& REF) const {
    return implementation != REF.implementation;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
