/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <atomicinteger.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

#if defined(COMPILER_GNUC) && (defined(ARCHITECTURE_X86) || defined(ARCHITECTURE_X64))
INTEGER AtomicInteger::swap(INTEGER V) {
    asm volatile("xchgl %1,%0"
                : "=r"(V)
                : "m"(value), "0"(V)
                : "memory");
    return V;
}

BOOLEAN AtomicInteger::compareAndSwap(INTEGER COND, INTEGER V) {
    BYTE RESULT;
    asm volatile("lock;cmpxchgl %3,%0;setz %1"
                : "=m"(value), "=q"(RESULT)
                : "m"(value), "r"(V), "a"(COND)
                : "memory");
    return RESULT != 0;
}
/*#elif defined(C_MSC)
INTEGER AtomicInteger::swap(INTEGER V)
{
        _asm
        {
                mov eax, [V]
                mov edx, [value]
                xchg [edx], eax
        }
    return V;
}

BOOLEAN AtomicInteger::cas(INTEGER COND, INTEGER V)
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
INTEGER AtomicInteger::swap(INTEGER V) {
    INTEGER TMP = value;
    value = V;
    return TMP;
}

BOOLEAN AtomicInteger::compareAndSwap(INTEGER COND, INTEGER V) {
    if (value == COND) {
        value = V;
        return true;
    }
    return false;
}
#endif

AtomicInteger::AtomicInteger(INTEGER V) : value(V) {
}

AtomicInteger::AtomicInteger(const AtomicInteger& REF) : value(REF.value) {
}

AtomicInteger::~AtomicInteger() {
}

INTEGER AtomicInteger::load() const {
    return value;
}

AtomicInteger& AtomicInteger::store(INTEGER V) {
    value = V;
    return *this;
}

BOOLEAN AtomicInteger::compare(INTEGER V) const {
    return value == V;
}

AtomicInteger& AtomicInteger::operator =(INTEGER V) {
    return store(V);
}

AtomicInteger& AtomicInteger::operator +=(INTEGER V) {
    while (!compareAndSwap(load(), load() + V));
    return *this;
}

AtomicInteger& AtomicInteger::operator -=(INTEGER V) {
    while (!compareAndSwap(load(), load() - V));
    return *this;
}

BOOLEAN AtomicInteger::operator ==(INTEGER V) const {
    return compare(V);
}

BOOLEAN AtomicInteger::operator !=(INTEGER V) const {
    return !compare(V);
}

AtomicInteger& AtomicInteger::operator =(const AtomicInteger& REF) {
    return store(REF.value);
}

BOOLEAN AtomicInteger::operator ==(const AtomicInteger& REF) const {
    return compare(REF.value);
}

BOOLEAN AtomicInteger::operator !=(const AtomicInteger& REF) const {
    return !compare(REF.value);
}

AtomicInteger& AtomicInteger::operator ++() {
    while (!compareAndSwap(load(), load() + 1));
    return *this;
}

AtomicInteger& AtomicInteger::operator --() {
    while (!compareAndSwap(load(), load() - 1));
    return *this;
}

END_SOURCECODE
