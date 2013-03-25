/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ATOMICPOINTER_HEADER
#define	ATOMICPOINTER_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class EXPORT AtomicPointer {
    TYPE * volatile Value;
public:
    explicit AtomicPointer(TYPE* V = 0);
    AtomicPointer(const AtomicPointer<TYPE>&);
    ~AtomicPointer();

    TYPE* Load() const;

    AtomicPointer<TYPE>& Store(TYPE*);

    boolean Compare(TYPE*) const;

    TYPE* Swap(TYPE*);

    boolean CompareAndSwap(TYPE*, TYPE*);

    TYPE* operator->() const;

    TYPE& operator*() const;

    AtomicPointer<TYPE>& operator=(TYPE*);

    AtomicPointer<TYPE>& operator+=(ptrdiff);
    AtomicPointer<TYPE>& operator-=(ptrdiff);

    boolean operator==(TYPE*) const;
    boolean operator!=(TYPE*) const;

    AtomicPointer<TYPE>& operator=(const AtomicPointer<TYPE>&);

    AtomicPointer<TYPE>& operator++();
    AtomicPointer<TYPE>& operator--();

    boolean operator==(const AtomicPointer<TYPE>&) const;
    boolean operator!=(const AtomicPointer<TYPE>&) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <atomicpointer_impl.hpp>

#endif
