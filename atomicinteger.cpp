/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <atomicinteger.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

#if defined(C_GNUC) && (defined(ARCH_X86) || defined(ARCH_X64))
integer AtomicInteger::Swap(integer V) {
    asm volatile("xchgl %1,%0"
                : "=r"(V)
                : "m"(Value), "0"(V)
                : "memory");
    return V;
}

boolean AtomicInteger::CompareAndSwap(integer COND, integer V) {
    byte RESULT;
    asm volatile("lock;cmpxchgl %3,%0;setz %1"
                : "=m"(Value), "=q"(RESULT)
                : "m"(Value), "r"(V), "a"(COND)
                : "memory");
    return RESULT != 0;
}
/*#elif defined(C_MSC)
integer AtomicInteger::Swap(integer V)
{
        _asm
        {
                mov eax, [V]
                mov edx, [Value]
                xchg [edx], eax
        }
    return V;
}

boolean AtomicInteger::CompareAndSwap(integer COND, integer V)
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
integer AtomicInteger::Swap(integer V) {
    integer TMP = Value;
    Value = V;
    return TMP;
}

boolean AtomicInteger::CompareAndSwap(integer COND, integer V) {
    if (Value == COND) {
        Value = V;
        return true;
    }
    return false;
}
#endif

AtomicInteger::AtomicInteger(integer V) : Value(V) {
}

AtomicInteger::AtomicInteger(const AtomicInteger& REF) : Value(REF.Value) {
}

AtomicInteger::~AtomicInteger() {
}

integer AtomicInteger::Load() const {
    return Value;
}

AtomicInteger& AtomicInteger::Store(integer V) {
    Value = V;
    return *this;
}

boolean AtomicInteger::Compare(integer V) const {
    return Value == V;
}

AtomicInteger& AtomicInteger::operator =(integer V) {
    return Store(V);
}

AtomicInteger& AtomicInteger::operator +=(integer V) {
    while (!CompareAndSwap(Load(), Load() + V));
    return *this;
}

AtomicInteger& AtomicInteger::operator -=(integer V) {
    while (!CompareAndSwap(Load(), Load() - V));
    return *this;
}

boolean AtomicInteger::operator ==(integer V) const {
    return Compare(V);
}

boolean AtomicInteger::operator !=(integer V) const {
    return !Compare(V);
}

AtomicInteger& AtomicInteger::operator =(const AtomicInteger& REF) {
    return Store(REF.Value);
}

boolean AtomicInteger::operator ==(const AtomicInteger& REF) const {
    return Compare(REF.Value);
}

boolean AtomicInteger::operator !=(const AtomicInteger& REF) const {
    return !Compare(REF.Value);
}

AtomicInteger& AtomicInteger::operator ++() {
    while (!CompareAndSwap(Load(), Load() + 1));
    return *this;
}

AtomicInteger& AtomicInteger::operator --() {
    while (!CompareAndSwap(Load(), Load() - 1));
    return *this;
}

END_SOURCECODE
