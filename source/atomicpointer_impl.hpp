/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ATOMICPOINTER_IMPLEMENTATION_HEADER
#define	ATOMICPOINTER_IMPLEMENTATION_HEADER

#include <atomicpointer.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

#if defined(COMPILER_GNUC)
#if defined(ARCHITECTURE_X86)
template <typename T>
AtomicPointer<T>::TYPE* AtomicPointer<T>::swap(AtomicPointer<T>::TYPE* V) {
    asm volatile("xchgl %1,%0"
                : "=r"(V)
                : "m"(value), "0"(V)
                : "memory");
    return V;
}

template <typename T>
BOOLEAN AtomicPointer<T>::compareAndSwap(AtomicPointer<T>::TYPE* COND, AtomicPointer<T>::TYPE* V) {
    BYTE RESULT;
    asm volatile("lock;cmpxchgl %3,%0;setz %1"
                : "=m"(value), "=q"(RESULT)
                : "m"(value), "r"(V), "a"(COND)
                : "memory");
    return RESULT != 0;
}
#elif defined(ARCHITECTURE_X64)
template <typename T>
AtomicPointer<T>::TYPE* AtomicPointer<T>::swap(AtomicPointer<T>::TYPE* V) {
    asm volatile("xchgq %1,%0"
                : "=r"(V)
                : "m"(value), "0"(V)
                : "memory");
    return V;
}

template <typename T>
BOOLEAN AtomicPointer<T>::compareAndSwap(AtomicPointer<T>::TYPE* COND, AtomicPointer<T>::TYPE* V) {
    BYTE RESULT;
    asm volatile("lock;cmpxchgq %3,%0;setz %1"
                : "=m"(value), "=q"(RESULT)
                : "m"(value), "r"(V), "a"(COND)
                : "memory");
    return RESULT != 0;
}
#endif
/*#elif defined(COMPILER_MSC)
template <typename T>
AtomicPointer<T>::TYPE* AtomicPointer<T>::swap(AtomicPointer<T>::TYPE* V)
{
    _asm
        {
                mov eax, [V]
                mov edx, [value]
                xchg [edx], eax
        }
    return V;
}

template <typename T>
BOOLEAN AtomicPointer<T>::compareAndSwap(AtomicPointer<T>::TYPE* COND, AtomicPointer<T>::TYPE* V)
{
    BYTE RESULT;
        _asm
        {
                mov eax, [value]
                mov ecx, [V]
                mov edx, [COND]
                lock cmpxchg [edx], ecx
                setz RESULT
        }
    return RESULT!=0;
}*/
#else
template <typename T>
AtomicPointer<T>::TYPE* AtomicPointer<T>::swap(AtomicPointer<T>::TYPE* V) {
    TYPE* TMP = value;
    value = V;
    return TMP;
}

template <typename T>
BOOLEAN AtomicPointer<T>::compareAndSwap(AtomicPointer<T>::TYPE* COND, AtomicPointer<T>::TYPE* V) {
    if (value == COND) {
        value = V;
        return true;
    }
    return false;
}
#endif

template <typename T>
AtomicPointer<T>::AtomicPointer(AtomicPointer<T>::TYPE* V) : value(V) {
}

template <typename T>
AtomicPointer<T>::AtomicPointer(const AtomicPointer<T>& REF) : value(REF.value) {
}

template <typename T>
AtomicPointer<T>::~AtomicPointer() {
}

template <typename T>
AtomicPointer<T>::TYPE* AtomicPointer<T>::load() const {
    return value;
}

template <typename T>
AtomicPointer<T>& AtomicPointer<T>::store(AtomicPointer<T>::TYPE* V) {
    value = V;
    return *this;
}

template <typename T>
BOOLEAN AtomicPointer<T>::compare(AtomicPointer<T>::TYPE* V) const {
    return value == V;
}

template <typename T>
AtomicPointer<T>::TYPE* AtomicPointer<T>::operator ->() const {
    return load();
}

template <typename T>
AtomicPointer<T>::TYPE& AtomicPointer<T>::operator *() const {
    return *load();
}

template <typename T>
AtomicPointer<T>& AtomicPointer<T>::operator =(AtomicPointer<T>::TYPE* V) {
    return store(V);
}

template <typename T>
AtomicPointer<T>& AtomicPointer<T>::operator +=(PTRDIFF DIFF) {
    while (!cas(load(), load() + DIFF));
    return *this;
}

template <typename T>
AtomicPointer<T>& AtomicPointer<T>::operator -=(PTRDIFF DIFF) {
    while (!cas(load(), load() - DIFF));
    return *this;
}

template <typename T>
BOOLEAN AtomicPointer<T>::operator ==(AtomicPointer<T>::TYPE* V) const {
    return compare(V);
}

template <typename T>
BOOLEAN AtomicPointer<T>::operator !=(AtomicPointer<T>::TYPE* V) const {
    return !compare(V);
}

template <typename T>
AtomicPointer<T>& AtomicPointer<T>::operator =(const AtomicPointer<T>& REF) {
    return store(REF.value);
}

template <typename T>
AtomicPointer<T>& AtomicPointer<T>::operator ++() {
    while (!compareAndSwap(load(), load() + 1));
    return *this;
}

template <typename T>
AtomicPointer<T>& AtomicPointer<T>::operator --() {
    while (!compareAndSwap(load(), load() - 1));
    return *this;
}

template <typename T>
BOOLEAN AtomicPointer<T>::operator ==(const AtomicPointer<T>& REF) const {
    return compare(REF.value);
}

template <typename T>
BOOLEAN AtomicPointer<T>::operator !=(const AtomicPointer<T>& REF) const {
    return !compare(REF.value);
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
