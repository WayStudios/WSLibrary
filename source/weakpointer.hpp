/*******************************************************************************
 * WayStudios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef WEAKPOINTER_HEADER
#define	WEAKPOINTER_HEADER

#include <smartpointerimpl.hpp>
#include <sharedpointer.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class EXPORT WeakPointer {
    SmartPointerImplementation<TYPE>* Implementation;
public:
    explicit WeakPointer(const SharedPointer<TYPE>&);
    WeakPointer(const WeakPointer<TYPE>&);
    ~WeakPointer();

    boolean Valid() const;
    boolean Invalid() const;

    TYPE* operator->() const;
    TYPE& operator*() const;

    boolean operator==(const WeakPointer<TYPE>&) const;
    boolean operator!=(const WeakPointer<TYPE>&) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
