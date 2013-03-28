/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ATOMICINTEGER_HEADER
#define	ATOMICINTEGER_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT AtomicInteger {
    volatile INTEGER value;
public:
    explicit AtomicInteger(INTEGER V = 0);
    AtomicInteger(const AtomicInteger&);
    ~AtomicInteger();

    INTEGER load() const;

    AtomicInteger& store(INTEGER);

    BOOLEAN compare(INTEGER) const;

    INTEGER swap(INTEGER);
	
    BOOLEAN compareAndSwap(INTEGER, INTEGER);

    AtomicInteger& operator =(INTEGER);

    AtomicInteger& operator +=(INTEGER);
    AtomicInteger& operator -=(INTEGER);

    BOOLEAN operator ==(INTEGER) const;
    BOOLEAN operator !=(INTEGER) const;

    AtomicInteger& operator =(const AtomicInteger&);

    BOOLEAN operator ==(const AtomicInteger&) const;
    BOOLEAN operator !=(const AtomicInteger&) const;

    AtomicInteger& operator ++();
    AtomicInteger& operator --();
};

END_WS_NAMESPACE

END_HEADER

#endif
