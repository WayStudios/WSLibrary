/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SCOPEDLOCK_IMPLEMENTATION_HEADER
#define	SCOPEDLOCK_IMPLEMENTATION_HEADER

#include <scopedlock.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T_LOCK>
ScopedLock<T_LOCK>::ScopedLock(T_LOCK* P) : Lock(P) {
    if (P)
        P->Lock();
}

template <typename T_LOCK>
ScopedLock<T_LOCK>::~ScopedLock() {
    if (Lock)
        Lock->Unlock();
}

template <typename T_LOCK>
boolean ScopedLock<T_LOCK>::operator ==(T_LOCK* P) const {
    return Lock == P;
}

template <typename T_LOCK>
boolean ScopedLock<T_LOCK>::operator !=(T_LOCK* P) const {
    return Lock != P;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
