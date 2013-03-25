/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef WEAKPOINTER_IMPLEMENTATION_HEADER
#define	WEAKPOINTER_IMPLEMENTATION_HEADER

#include <weakpointer.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
WeakPointer<TYPE>::WeakPointer(const SharedPointer<TYPE>& REF_SP) : Implementation(REF_SP.Implementation) {
    if (Implementation)
        ++(Implementation->Ref_Weak);
}

template <typename TYPE>
WeakPointer<TYPE>::WeakPointer(const WeakPointer<TYPE>& REF) : Implementation(REF.Implementation) {
    if (Implementation)
        ++(Implementation->Ref_Weak);
}

template <typename TYPE>
WeakPointer<TYPE>::~WeakPointer() {
    if (Implementation)
        if (--(Implementation->Ref_Weak) == 0)
            if ((Implementation->Ref_Shared) == 0)
                delete Implementation;
}

template <typename TYPE>
boolean WeakPointer<TYPE>::Valid() const {
    return (Implementation->Address) != 0;
}

template <typename TYPE>
boolean WeakPointer<TYPE>::Invalid() const {
    return (Implementation->Address) == 0;
}

template <typename TYPE>
TYPE* WeakPointer<TYPE>::operator ->() const {
    if (Implementation)
        return Implementation->Address;
    return 0;
}

template <typename TYPE>
TYPE& WeakPointer<TYPE>::operator *() const {
    if (Implementation)
        return *(Implementation->Address);
    throw;
}

template <typename TYPE>
boolean WeakPointer<TYPE>::operator ==(const WeakPointer<TYPE>& REF) const {
    return Implementation == REF.Implementation;
}

template <typename TYPE>
boolean WeakPointer<TYPE>::operator !=(const WeakPointer<TYPE>& REF) const {
    return Implementation != REF.Implementation;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
