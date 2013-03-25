/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SHAREDPOINTER_IMPLEMENTATION_HEADER
#define	SHAREDPOINTER_IMPLEMENTATION_HEADER

#include <sharedpointer.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
SharedPointer<TYPE>::SharedPointer(TYPE* P_ADDR) : Implementation(0) {
    Implementation = new SmartPointerImplementation<TYPE > (P_ADDR);
    if (Implementation)
        ++(Implementation->Ref_Shared);
}

template <typename TYPE>
SharedPointer<TYPE>::SharedPointer(const SharedPointer<TYPE>& REF) : Implementation(REF.Implementation) {
    if (Implementation)
        ++(Implementation->Ref_Shared);
}

template <typename TYPE>
SharedPointer<TYPE>::~SharedPointer() {
    if (Implementation)
        if (--(Implementation->Ref_Shared) == 0) {
            delete Implementation->Address;
            if ((Implementation->Ref_Weak) == 0)
                delete Implementation;
            else
                Implementation->Address = 0;
        }
}

template <typename TYPE>
TYPE* SharedPointer<TYPE>::Address() const {
    if (Implementation)
        return Implementation->Address;
    return 0;
}

template <typename TYPE>
SharedPointer<TYPE>::operator bool() const {
    if (Implementation)
        return Implementation->Address != 0;
    return false;
}

template <typename TYPE>
boolean SharedPointer<TYPE>::operator!() const {
    if (Implementation)
        return !Implementation->Address;
    return true;
}

template <typename TYPE>
TYPE* SharedPointer<TYPE>::operator ->() const {
    if (Implementation)
        return Implementation->Address;
    return 0;
}

template <typename TYPE>
TYPE& SharedPointer<TYPE>::operator *() const {
    if (Implementation)
        return *(Implementation->Address);
    throw;
}

template <typename TYPE>
boolean SharedPointer<TYPE>::operator ==(const SharedPointer<TYPE>& REF) const {
    return Implementation == REF.Implementation;
}

template <typename TYPE>
boolean SharedPointer<TYPE>::operator !=(const SharedPointer<TYPE>& REF) const {
    return Implementation != REF.Implementation;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
