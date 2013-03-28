/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <atomicboolean.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

#if defined(COMPILER_GNUC) && (defined(ARCHITECTURE_X86) || defined(ARCHITECTURE_X64))
BOOLEAN AtomicBoolean::swap(BOOLEAN V) {
    asm volatile("xchgb %1,%0"
                : "=r"(V)
                : "m"(value), "0"(V)
                : "memory");
    return V;
}

BOOLEAN AtomicBoolean::compareAndSwap(BOOLEAN COND, BOOLEAN V) {
    BYTE RESULT;
    asm volatile("lock;cmpxchgb %3,%0;setz %1"
                : "=m"(value), "=q"(RESULT)
                : "m"(value), "r"(V), "a"(COND)
                : "memory");
    return RESULT != 0;
}
/*#elif defined(C_MSC)
BOOLEAN AtomicBoolean::swap(BOOLEAN V)
{
        _asm
        {
                mov eax, DWORD PTR V
                mov edx, DWORD PTR value
                xchg [edx], eax
        }
    return V;
}

BOOLEAN AtomicBoolean::cas(BOOLEAN COND, BOOLEAN V)
{
        BYTE RESULT;
        _asm
        {
                mov eax, [value]
                mov ecx, DWORD PTR V
                mov edx, DWORD PTR COND
                lock cmpxchg [edx], ecx
                setz RESULT
        }
        return RESULT!=0;
}*/
#else
BOOLEAN AtomicBoolean::swap(BOOLEAN V) {
    BOOLEAN TMP = value;
    value = V;
    return TMP;
}

BOOLEAN AtomicBoolean::compareAndSwap(BOOLEAN COND, BOOLEAN V) {
    if (value == COND) {
        value = V;
        return true;
    }
    return false;
}
#endif

AtomicBoolean::AtomicBoolean(BOOLEAN V) : value(V) {
}

AtomicBoolean::AtomicBoolean(const AtomicBoolean& REF) : value(REF.value) {
}

AtomicBoolean::~AtomicBoolean() {
}

BOOLEAN AtomicBoolean::load() const {
    return value;
}

AtomicBoolean& AtomicBoolean::store(BOOLEAN V) {
    value = V;
    return *this;
}

BOOLEAN AtomicBoolean::compare(BOOLEAN V) const {
    return value == V;
}

AtomicBoolean& AtomicBoolean::operator =(BOOLEAN V) {
    return store(V);
}

BOOLEAN AtomicBoolean::operator ==(BOOLEAN V) const {
    return compare(V);
}

BOOLEAN AtomicBoolean::operator !=(BOOLEAN V) const {
    return !compare(V);
}

AtomicBoolean& AtomicBoolean::operator =(const AtomicBoolean& REF) {
    return store(REF.value);
}

BOOLEAN AtomicBoolean::operator ==(const AtomicBoolean& REF) const {
    return compare(REF.value);
}

BOOLEAN AtomicBoolean::operator !=(const AtomicBoolean& REF) const {
    return !compare(REF.value);
}

END_SOURCECODE
