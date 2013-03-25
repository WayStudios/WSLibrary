/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ATOMICPOINTER_IMPLEMENTATION_HEADER
#define	ATOMICPOINTER_IMPLEMENTATION_HEADER

#include <atomicpointer.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

#if defined(C_GNUC)
#if defined(ARCH_X86)
template <typename TYPE>
TYPE* AtomicPointer<TYPE>::Swap(TYPE* V) {
    asm volatile("xchgl %1,%0"
                : "=r"(V)
                : "m"(Value), "0"(V)
                : "memory");
    return V;
}

template <typename TYPE>
boolean AtomicPointer<TYPE>::CompareAndSwap(TYPE* COND, TYPE* V) {
    byte RESULT;
    asm volatile("lock;cmpxchgl %3,%0;setz %1"
                : "=m"(Value), "=q"(RESULT)
                : "m"(Value), "r"(V), "a"(COND)
                : "memory");
    return RESULT != 0;
}
#elif defined(ARCH_X64)
template <typename TYPE>
TYPE* AtomicPointer<TYPE>::Swap(TYPE* V) {
    asm volatile("xchgq %1,%0"
                : "=r"(V)
                : "m"(Value), "0"(V)
                : "memory");
    return V;
}

template <typename TYPE>
boolean AtomicPointer<TYPE>::CompareAndSwap(TYPE* COND, TYPE* V) {
    byte RESULT;
    asm volatile("lock;cmpxchgq %3,%0;setz %1"
                : "=m"(Value), "=q"(RESULT)
                : "m"(Value), "r"(V), "a"(COND)
                : "memory");
    return RESULT != 0;
}
#endif
/*#elif defined(C_MSC)
template <typename TYPE>
TYPE* AtomicPointer<TYPE>::Swap(TYPE* V)
{
    _asm
        {
                mov eax, [V]
                mov edx, [Value]
                xchg [edx], eax
        }
    return V;
}

template <typename TYPE>
boolean AtomicPointer<TYPE>::CompareAndSwap(TYPE* COND, TYPE* V)
{
    byte RESULT;
        _asm
        {
                mov eax, [Value]
                mov ecx, [V]
                mov edx, [COND]
                lock cmpxchg [edx], ecx
                setz RESULT
        }
    return RESULT!=0;
}*/
#else
template <typename TYPE>
TYPE* AtomicPointer<TYPE>::Swap(TYPE* V) {
    TYPE* TMP = Value;
    Value = V;
    return TMP;
}

template <typename TYPE>
boolean AtomicPointer<TYPE>::CompareAndSwap(TYPE* COND, TYPE* V) {
    if (Value == COND) {
        Value = V;
        return true;
    }
    return false;
}
#endif

template <typename TYPE>
AtomicPointer<TYPE>::AtomicPointer(TYPE* V) : Value(V) {
}

template <typename TYPE>
AtomicPointer<TYPE>::AtomicPointer(const AtomicPointer<TYPE>& REF) : Value(REF.Value) {
}

template <typename TYPE>
AtomicPointer<TYPE>::~AtomicPointer() {
}

template <typename TYPE>
TYPE* AtomicPointer<TYPE>::Load() const {
    return Value;
}

template <typename TYPE>
AtomicPointer<TYPE>& AtomicPointer<TYPE>::Store(TYPE* V) {
    Value = V;
    return *this;
}

template <typename TYPE>
boolean AtomicPointer<TYPE>::Compare(TYPE* V) const {
    return Value == V;
}

template <typename TYPE>
TYPE* AtomicPointer<TYPE>::operator ->() const {
    return Load();
}

template <typename TYPE>
TYPE& AtomicPointer<TYPE>::operator *() const {
    return *Load();
}

template <typename TYPE>
        AtomicPointer<TYPE>& AtomicPointer<TYPE>::operator =(TYPE* V) {
    return Store(V);
}

template <typename TYPE>
        AtomicPointer<TYPE>& AtomicPointer<TYPE>::operator +=(ptrdiff DIFF) {
    while (!CompareAndSwap(Load(), Load() + DIFF));
    return *this;
    ;
}

template <typename TYPE>
        AtomicPointer<TYPE>& AtomicPointer<TYPE>::operator -=(ptrdiff DIFF) {
    while (!CompareAndSwap(Load(), Load() - DIFF));
    return *this;
    ;
}

template <typename TYPE>
boolean AtomicPointer<TYPE>::operator ==(TYPE* V) const {
    return Compare(V);
}

template <typename TYPE>
boolean AtomicPointer<TYPE>::operator !=(TYPE* V) const {
    return !Compare(V);
}

template <typename TYPE>
        AtomicPointer<TYPE>& AtomicPointer<TYPE>::operator =(const AtomicPointer<TYPE>& REF) {
    return Store(REF.Value);
}

template <typename TYPE>
AtomicPointer<TYPE>& AtomicPointer<TYPE>::operator ++() {
    while (!CompareAndSwap(Load(), Load() + 1));
    return *this;
}

template <typename TYPE>
AtomicPointer<TYPE>& AtomicPointer<TYPE>::operator --() {
    while (!CompareAndSwap(Load(), Load() - 1));
    return *this;
}

template <typename TYPE>
boolean AtomicPointer<TYPE>::operator ==(const AtomicPointer<TYPE>& REF) const {
    return Compare(REF.Value);
}

template <typename TYPE>
boolean AtomicPointer<TYPE>::operator !=(const AtomicPointer<TYPE>& REF) const {
    return !Compare(REF.Value);
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
