/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <atomicboolean.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

#if defined(C_GNUC) && (defined(ARCH_X86) || defined(ARCH_X64))
boolean AtomicBoolean::Swap(boolean V) {
    asm volatile("xchgb %1,%0"
                : "=r"(V)
                : "m"(Value), "0"(V)
                : "memory");
    return V;
}

boolean AtomicBoolean::CompareAndSwap(boolean COND, boolean V) {
    byte RESULT;
    asm volatile("lock;cmpxchgb %3,%0;setz %1"
                : "=m"(Value), "=q"(RESULT)
                : "m"(Value), "r"(V), "a"(COND)
                : "memory");
    return RESULT != 0;
}
/*#elif defined(C_MSC)
boolean AtomicBoolean::Swap(boolean V)
{
        _asm
        {
                mov eax, DWORD PTR V
                mov edx, DWORD PTR Value
                xchg [edx], eax
        }
    return V;
}

boolean AtomicBoolean::CompareAndSwap(boolean COND, boolean V)
{
        byte RESULT;
        _asm
        {
                mov eax, [Value]
                mov ecx, DWORD PTR V
                mov edx, DWORD PTR COND
                lock cmpxchg [edx], ecx
                setz RESULT
        }
        return RESULT!=0;
}*/
#else
boolean AtomicBoolean::Swap(boolean V) {
    boolean TMP = Value;
    Value = V;
    return TMP;
}

boolean AtomicBoolean::CompareAndSwap(boolean COND, boolean V) {
    if (Value == COND) {
        Value = V;
        return true;
    }
    return false;
}
#endif

AtomicBoolean::AtomicBoolean(boolean V) : Value(V) {
}

AtomicBoolean::AtomicBoolean(const AtomicBoolean& REF) : Value(REF.Value) {
}

AtomicBoolean::~AtomicBoolean() {
}

boolean AtomicBoolean::Load() const {
    return Value;
}

AtomicBoolean& AtomicBoolean::Store(boolean V) {
    Value = V;
    return *this;
}

boolean AtomicBoolean::Compare(boolean V) const {
    return Value == V;
}

AtomicBoolean& AtomicBoolean::operator =(boolean V) {
    return Store(V);
}

boolean AtomicBoolean::operator ==(boolean V) const {
    return Compare(V);
}

boolean AtomicBoolean::operator !=(boolean V) const {
    return !Compare(V);
}

AtomicBoolean& AtomicBoolean::operator =(const AtomicBoolean& REF) {
    return Store(REF.Value);
}

boolean AtomicBoolean::operator ==(const AtomicBoolean& REF) const {
    return Compare(REF.Value);
}

boolean AtomicBoolean::operator !=(const AtomicBoolean& REF) const {
    return !Compare(REF.Value);
}

END_SOURCECODE
