/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SHAREDPOINTER_HEADER
#define	SHAREDPOINTER_HEADER

#include <smartpointerimpl.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class WeakPointer;

template <typename TYPE>
class EXPORT SharedPointer {
    friend class WeakPointer<TYPE>;
public:
    explicit SharedPointer(TYPE*);
    SharedPointer(const SharedPointer<TYPE>&);
    ~SharedPointer();

    TYPE* Address() const;

    operator bool() const;
    boolean operator!() const;

    TYPE* operator->() const;

    TYPE& operator*() const;

    boolean operator==(const SharedPointer<TYPE>&) const;
    boolean operator!=(const SharedPointer<TYPE>&) const;
private:
    SmartPointerImplementation<TYPE>* Implementation;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <sharedpointer_impl.hpp>

#endif
