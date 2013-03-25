/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ATOMICINTEGER_HEADER
#define	ATOMICINTEGER_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT AtomicInteger {
    volatile integer Value;
public:
    explicit AtomicInteger(integer V = 0);
    AtomicInteger(const AtomicInteger&);
    ~AtomicInteger();

    integer Load() const;

    AtomicInteger& Store(integer);

    boolean Compare(integer) const;

    integer Swap(integer);

    boolean CompareAndSwap(integer, integer);

    AtomicInteger& operator=(integer);

    AtomicInteger& operator+=(integer);
    AtomicInteger& operator-=(integer);

    boolean operator==(integer) const;
    boolean operator!=(integer) const;

    AtomicInteger& operator=(const AtomicInteger&);

    boolean operator==(const AtomicInteger&) const;
    boolean operator!=(const AtomicInteger&) const;

    AtomicInteger& operator++();
    AtomicInteger& operator--();
};

END_WS_NAMESPACE

END_HEADER

#endif
