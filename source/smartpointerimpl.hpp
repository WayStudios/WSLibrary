/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SMARTPOINTERIMPLEMENTATION_HEADER
#define	SMARTPOINTERIMPLEMENTATION_HEADER

#include <global.hpp>
#include <atomicinteger.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
class LOCAL SmartPointerImplementation {
    UNCOPYABLE(SmartPointerImplementation)
public:
	typedef T TYPE;

    explicit SmartPointerImplementation(TYPE*);
    ~SmartPointerImplementation();

    TYPE* address;
    AtomicInteger sharedReference;
    AtomicInteger weakReference;
};

template <typename T>
SmartPointerImplementation<T>::SmartPointerImplementation(typename SmartPointerImplementation<T>::TYPE * P_ADDR) : address(P_ADDR) {
}

template <typename T>
SmartPointerImplementation<T>::~SmartPointerImplementation() {
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
