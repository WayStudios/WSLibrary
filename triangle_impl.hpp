/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef TRIANGLE_IMPLEMENTATION_HEADER
#define	TRIANGLE_IMPLEMENTATION_HEADER

#include <triangle.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_VECTOR>
Triangle<T_VECTOR>::Triangle(const T_VECTOR& VEC_A, const T_VECTOR& VEC_B, const T_VECTOR& VEC_C):Capacity(3)
{
    Array[0]=VEC_A;
    Array[1]=VEC_B;    
    Array[2]=VEC_C;    
}

template <typename T_VECTOR>
Triangle<T_VECTOR>::Triangle(const Triangle<T_VECTOR>& REF):Capacity(3)
{
    Array[0]=REF.Array[0];
    Array[1]=REF.Array[1];    
    Array[2]=REF.Array[2];    
}

template <typename T_VECTOR>
Triangle<T_VECTOR>::~Triangle(){}

template <typename T_VECTOR>
T_VECTOR& Triangle<T_VECTOR>::A(){return Array[0];}

template <typename T_VECTOR>
T_VECTOR& Triangle<T_VECTOR>::B(){return Array[1];}

template <typename T_VECTOR>
T_VECTOR& Triangle<T_VECTOR>::C(){return Array[2];}

template <typename T_VECTOR>
const T_VECTOR& Triangle<T_VECTOR>::A() const{return Array[0];}

template <typename T_VECTOR>
const T_VECTOR& Triangle<T_VECTOR>::B() const{return Array[1];}

template <typename T_VECTOR>
const T_VECTOR& Triangle<T_VECTOR>::C() const{return Array[2];}

template <typename T_VECTOR>
Triangle<T_VECTOR>& Triangle<T_VECTOR>::Set(const T_VECTOR& VEC_A, const T_VECTOR& VEC_B, const T_VECTOR& VEC_C)
{    
    A()=VEC_A;
    B()=VEC_B;    
    C()=VEC_C;
    return *this;
}

template <typename T_VECTOR>
Triangle<T_VECTOR>& Triangle<T_VECTOR>::operator =(const Triangle<T_VECTOR>& REF)
{
    A()=REF.A();
    B()=REF.B();
    C()=REF.C();
    return *this;
}

template <typename T_VECTOR>
boolean Triangle<T_VECTOR>::operator ==(const Triangle<T_VECTOR>& REF) const{return A()==REF.A() && B()==REF.B() && C()==REF.C();}

template <typename T_VECTOR>
boolean Triangle<T_VECTOR>::operator !=(const Triangle<T_VECTOR>& REF) const{return A()!=REF.A() || B()!=REF.B() || C()!=REF.C();}

template <typename T_VECTOR>
boolean Triangle<T_VECTOR>::operator >(const Triangle<T_VECTOR>& REF) const{return A()>REF.A() && B()>REF.B() && C()>REF.C();}

template <typename T_VECTOR>
boolean Triangle<T_VECTOR>::operator <(const Triangle<T_VECTOR>& REF) const{return A()<REF.A() && B()<REF.B() && C()<REF.C();}

template <typename T_VECTOR>
boolean Triangle<T_VECTOR>::operator >=(const Triangle<T_VECTOR>& REF) const{return A()>=REF.A() && B()>=REF.B() && C()>=REF.C();}

template <typename T_VECTOR>
boolean Triangle<T_VECTOR>::operator <=(const Triangle<T_VECTOR>& REF) const{return A()<=REF.A() && B()<=REF.B() && C()<=REF.C();}

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
