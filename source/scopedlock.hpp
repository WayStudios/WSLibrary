/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SCOPEDLOCK_HEADER
#define	SCOPEDLOCK_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T_LOCK>
class EXPORT ScopedLock {
    UNCOPYABLE(ScopedLock<T_LOCK>)

    T_LOCK* Lock;
public:
    explicit ScopedLock(T_LOCK*);
    ~ScopedLock();

    boolean operator==(T_LOCK*) const;
    boolean operator!=(T_LOCK*) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <scopedlock_impl.hpp>

#endif
