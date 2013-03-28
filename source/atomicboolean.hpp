/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ATOMICBOOLEAN_HEADER
#define	ATOMICBOOLEAN_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT AtomicBoolean {
    volatile BOOLEAN value;
public:
    explicit AtomicBoolean(BOOLEAN V = false);
    AtomicBoolean(const AtomicBoolean&);
    ~AtomicBoolean();

    BOOLEAN load() const;

    AtomicBoolean& store(BOOLEAN);

    BOOLEAN compare(BOOLEAN) const;

    BOOLEAN swap(BOOLEAN);

    BOOLEAN compareAndSwap(BOOLEAN, BOOLEAN);

    AtomicBoolean& operator =(BOOLEAN);

    BOOLEAN operator ==(BOOLEAN) const;
    BOOLEAN operator !=(BOOLEAN) const;

    AtomicBoolean& operator =(const AtomicBoolean&);

    BOOLEAN operator ==(const AtomicBoolean&) const;
    BOOLEAN operator !=(const AtomicBoolean&) const;
};

END_WS_NAMESPACE

END_HEADER

#endif
