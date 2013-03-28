/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SCOPEDLOCK_HEADER
#define	SCOPEDLOCK_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
class EXPORT ScopedLock {
    UNCOPYABLE(ScopedLock)
public:
	typedef T TYPE;

    explicit ScopedLock(TYPE*);
    ~ScopedLock();

    BOOLEAN operator ==(TYPE*) const;
    BOOLEAN operator !=(TYPE*) const;
private:
	mutable TYPE* lock;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <scopedlock_impl.hpp>

#endif
