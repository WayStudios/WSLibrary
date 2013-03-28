/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SHAREDPOINTER_HEADER
#define	SHAREDPOINTER_HEADER

#include <smartpointerimpl.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
class WeakPointer;

template <typename T>
class EXPORT SharedPointer {
    friend class WeakPointer<T>;
public:
	typedef T TYPE;

    explicit SharedPointer(TYPE*);
    SharedPointer(const SharedPointer<T>&);
    ~SharedPointer();

    TYPE* address() const;

    operator bool() const;
    BOOLEAN operator !() const;

    TYPE* operator ->() const;

    TYPE& operator *() const;

    BOOLEAN operator ==(const SharedPointer<T>&) const;
    BOOLEAN operator !=(const SharedPointer<T>&) const;
private:
    SmartPointerImplementation<T>* implementation;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <sharedpointer_impl.hpp>

#endif
