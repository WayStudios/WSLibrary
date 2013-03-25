/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef QUADRILATERAL_IMPLEMENTATION_HEADER
#define	QUADRILATERAL_IMPLEMENTATION_HEADER

#include <quadrilateral.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_VECTOR>
Quadrilateral<T_VECTOR>::Quadrilateral(const T_VECTOR& VEC_A, const T_VECTOR& VEC_B, const T_VECTOR& VEC_C, const T_VECTOR& VEC_D):Capacity(4)
{
    Array[0]=VEC_A;
    Array[1]=VEC_B;
    Array[2]=VEC_C;
    Array[3]=VEC_D;
}

template <typename T_VECTOR>
Quadrilateral<T_VECTOR>::Quadrilateral(const Quadrilateral<T_VECTOR>& REF):Capacity(4)
{
    Array[0]=REF.Array[0];
    Array[1]=REF.Array[1];
    Array[2]=REF.Array[2];
    Array[3]=REF.Array[3];
}

template <typename T_VECTOR>
Quadrilateral<T_VECTOR>::~Quadrilateral(){}

template <typename T_VECTOR>
T_VECTOR& Quadrilateral<T_VECTOR>::A(){return Array[0];}

template <typename T_VECTOR>
T_VECTOR& Quadrilateral<T_VECTOR>::B(){return Array[1];}

template <typename T_VECTOR>
T_VECTOR& Quadrilateral<T_VECTOR>::C(){return Array[2];}

template <typename T_VECTOR>
T_VECTOR& Quadrilateral<T_VECTOR>::D(){return Array[3];}

template <typename T_VECTOR>
const T_VECTOR& Quadrilateral<T_VECTOR>::A() const{return Array[0];}

template <typename T_VECTOR>
const T_VECTOR& Quadrilateral<T_VECTOR>::B() const{return Array[1];}

template <typename T_VECTOR>
const T_VECTOR& Quadrilateral<T_VECTOR>::C() const{return Array[2];}

template <typename T_VECTOR>
const T_VECTOR& Quadrilateral<T_VECTOR>::D() const{return Array[3];}

template <typename T_VECTOR>
Quadrilateral<T_VECTOR>& Quadrilateral<T_VECTOR>::Set(const T_VECTOR& VEC_A, const T_VECTOR& VEC_B, const T_VECTOR& VEC_C, const T_VECTOR& VEC_D)
{
    A()=VEC_A;
    B()=VEC_B;
    C()=VEC_C;
    D()=VEC_D;
    return *this;
}

template <typename T_VECTOR>
Quadrilateral<T_VECTOR>& Quadrilateral<T_VECTOR>::operator =(const Quadrilateral<T_VECTOR>& REF)
{
    A()=REF.A();
    B()=REF.B();
    C()=REF.C();
    D()=REF.D();
    return *this;
}

template <typename T_VECTOR>
boolean Quadrilateral<T_VECTOR>::operator ==(const Quadrilateral<T_VECTOR>& REF) const{return A()==REF.A() && B()==REF.B() && C()==REF.C() && D()==REF.D();}

template <typename T_VECTOR>
boolean Quadrilateral<T_VECTOR>::operator !=(const Quadrilateral<T_VECTOR>& REF) const{return A()!=REF.A() || B()!=REF.B() || C()!=REF.C() || D()!=REF.D();}

template <typename T_VECTOR>
boolean Quadrilateral<T_VECTOR>::operator >(const Quadrilateral<T_VECTOR>& REF) const{return A()>REF.A() && B()>REF.B() && C()>REF.C() && D()>REF.D();}

template <typename T_VECTOR>
boolean Quadrilateral<T_VECTOR>::operator <(const Quadrilateral<T_VECTOR>& REF) const{return A()<REF.A() && B()<REF.B() && C()<REF.C() && D()<REF.D();}

template <typename T_VECTOR>
boolean Quadrilateral<T_VECTOR>::operator >=(const Quadrilateral<T_VECTOR>& REF) const{return A()>=REF.A() && B()>=REF.B() && C()>=REF.C() && D()>=REF.D();}

template <typename T_VECTOR>
boolean Quadrilateral<T_VECTOR>::operator <=(const Quadrilateral<T_VECTOR>& REF) const{return A()<=REF.A() && B()<=REF.B() && C()<=REF.C() && D()<=REF.D();}

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
