/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SCOPEDLOCK_IMPLEMENTATION_HEADER
#define	SCOPEDLOCK_IMPLEMENTATION_HEADER

#include <scopedlock.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
ScopedLock<T>::ScopedLock(typename ScopedLock<T>::TYPE* P) : lock(P) {
    if (lock)
        lock->lock();
}

template <typename T>
ScopedLock<T>::~ScopedLock() {
    if (lock)
        lock->unlock();
}

template <typename T>
BOOLEAN ScopedLock<T>::operator ==(typename ScopedLock<T>::TYPE* P) const {
    return lock == P;
}

template <typename T>
BOOLEAN ScopedLock<T>::operator !=(typename ScopedLock<T>::TYPE* P) const {
    return lock != P;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
