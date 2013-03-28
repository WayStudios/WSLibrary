/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef POINTER_HEADER
#define	POINTER_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class EXPORT Pointer {
    TYPE* address;
public:
    explicit Pointer(TYPE* P = 0);
    Pointer(const Pointer<TYPE>&);
    ~Pointer();

    void setAddress(TYPE*);
	TYPE* getAddress(TYPE*) const;

    BOOLEAN operator!() const;

    TYPE* operator->() const;

    TYPE& operator*() const;

    Pointer<TYPE>& operator =(const Pointer<TYPE>&);

    Pointer<TYPE>& operator +=(PTRDIFF);
    Pointer<TYPE>& operator -=(PTRDIFF);

    Pointer<TYPE> operator +(PTRDIFF) const;

    PTRDIFF operator -(const Pointer<TYPE>&) const;

    BOOLEAN operator ==(const Pointer<TYPE>&) const;
    BOOLEAN operator !=(const Pointer<TYPE>&) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <pointer_impl.hpp>

#endif
