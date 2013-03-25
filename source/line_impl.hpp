/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef LINE_IMPLEMENTATION_HEADER
#define	LINE_IMPLEMENTATION_HEADER

#include <line.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_VECTOR>
Line<T_VECTOR>::Line(const T_VECTOR& VEC_A, const T_VECTOR& VEC_B):Capacity(2)
{
    Array[0]=VEC_A;
    Array[1]=VEC_B;
}

template <typename T_VECTOR>
Line<T_VECTOR>::Line(const Line<T_VECTOR>& REF):Capacity(2)
{
    Array[0]=REF.Array[0];
    Array[1]=REF.Array[1];
}

template <typename T_VECTOR>
Line<T_VECTOR>::~Line(){}

template <typename T_VECTOR>
T_VECTOR& Line<T_VECTOR>::A(){return Array[0];}

template <typename T_VECTOR>
T_VECTOR& Line<T_VECTOR>::B(){return Array[1];}

template <typename T_VECTOR>
const T_VECTOR& Line<T_VECTOR>::A() const{return Array[0];}

template <typename T_VECTOR>
const T_VECTOR& Line<T_VECTOR>::B() const{return Array[1];}

template <typename T_VECTOR>
Line<T_VECTOR>& Line<T_VECTOR>::Set(const T_VECTOR& VEC_A, const T_VECTOR& VEC_B)
{
    A()=VEC_A;
    B()=VEC_B;
    return *this;
}

template <typename T_VECTOR>
T_VECTOR& Line<T_VECTOR>::operator [](size IDX){return Array[IDX];}

template <typename T_VECTOR>
const T_VECTOR& Line<T_VECTOR>::operator [](size IDX) const{return Array[IDX];}

template <typename T_VECTOR>
Line<T_VECTOR>& Line<T_VECTOR>::operator =(const Line<T_VECTOR>& REF)
{
    A()=REF.A();
    B()=REF.B();
    return *this;
}

template <typename T_VECTOR>
boolean Line<T_VECTOR>::operator ==(const Line<T_VECTOR>& REF) const{return A()==REF.A() && B()==REF.B();}

template <typename T_VECTOR>
boolean Line<T_VECTOR>::operator !=(const Line<T_VECTOR>& REF) const{return A()!=REF.A() || B()!=REF.B();}

template <typename T_VECTOR>
boolean Line<T_VECTOR>::operator >(const Line<T_VECTOR>& REF) const{return A()>REF.A() && B()>REF.B();}

template <typename T_VECTOR>
boolean Line<T_VECTOR>::operator <(const Line<T_VECTOR>& REF) const{return A()<REF.A() && B()<REF.B();}

template <typename T_VECTOR>
boolean Line<T_VECTOR>::operator >=(const Line<T_VECTOR>& REF) const{return A()>=REF.A() && B()>=REF.B();}

template <typename T_VECTOR>
boolean Line<T_VECTOR>::operator <=(const Line<T_VECTOR>& REF) const{return A()<=REF.A() && B()<=REF.B();}

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
