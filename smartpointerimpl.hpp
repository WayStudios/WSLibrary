/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SMARTPOINTERIMPLEMENTATION_HEADER
#define	SMARTPOINTERIMPLEMENTATION_HEADER

#include <global.hpp>
#include <atomicinteger.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class LOCAL SmartPointerImplementation {
    UNCOPYABLE(SmartPointerImplementation)
public:
    explicit SmartPointerImplementation(TYPE*);
    ~SmartPointerImplementation();

    TYPE* Address;
    AtomicInteger Ref_Shared;
    AtomicInteger Ref_Weak;
};

template <typename TYPE>
SmartPointerImplementation<TYPE>::SmartPointerImplementation(TYPE* P_ADDR) : Address(P_ADDR) {
}

template <typename TYPE>
SmartPointerImplementation<TYPE>::~SmartPointerImplementation() {
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
