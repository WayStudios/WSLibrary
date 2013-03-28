/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SCOPEDPOINTER_HEADER
#define	SCOPEDPOINTER_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class EXPORT ScopedPointer {
    UNCOPYABLE(ScopedPointer<TYPE>);

    TYPE* Address;
public:
    explicit ScopedPointer(TYPE*);
    ~ScopedPointer();

    TYPE* Pointer() const;

    boolean operator!() const;

    TYPE* operator->() const;

    TYPE& operator*() const;

    boolean operator==(TYPE*) const;
    boolean operator!=(TYPE*) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <scopedpointer_impl.hpp>

#endif
