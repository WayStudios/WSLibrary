/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef QUADRILATERAL_IMPLEMENTATION_HEADER
#define	QUADRILATERAL_IMPLEMENTATION_HEADER

#include <quadrilateral.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T>
Quadrilateral<T>::Quadrilateral(const typename Quadrilateral<T>::TYPE& VEC_A, const typename Quadrilateral<T>::TYPE& VEC_B, const typename Quadrilateral<T>::TYPE& VEC_C, const typename Quadrilateral<T>::TYPE& VEC_D) : capacity(4) {
    array[0]=VEC_A;
    array[1]=VEC_B;
    array[2]=VEC_C;
    array[3]=VEC_D;
}

template <typename T>
Quadrilateral<T>::Quadrilateral(const Quadrilateral<T>& REF) : capacity(4) {
    array[0] = REF.array[0];
    array[1] = REF.array[1];
    array[2] = REF.array[2];
    array[3] = REF.array[3];
}

template <typename T>
Quadrilateral<T>::~Quadrilateral(){}

template <typename T>
typename Quadrilateral<T>::TYPE& Quadrilateral<T>::a(){return array[0];}

template <typename T>
typename Quadrilateral<T>::TYPE& Quadrilateral<T>::b(){return array[1];}

template <typename T>
typename Quadrilateral<T>::TYPE& Quadrilateral<T>::c(){return array[2];}

template <typename T>
typename Quadrilateral<T>::TYPE& Quadrilateral<T>::d(){return array[3];}

template <typename T>
const typename Quadrilateral<T>::TYPE& Quadrilateral<T>::a() const{return array[0];}

template <typename T>
const typename Quadrilateral<T>::TYPE& Quadrilateral<T>::b() const{return array[1];}

template <typename T>
const typename Quadrilateral<T>::TYPE& Quadrilateral<T>::c() const{return array[2];}

template <typename T>
const typename Quadrilateral<T>::TYPE& Quadrilateral<T>::d() const{return array[3];}

template <typename T>
Quadrilateral<T>& Quadrilateral<T>::set(const typename Quadrilateral<T>::TYPE& VEC_A, const typename Quadrilateral<T>::TYPE& VEC_B, const typename Quadrilateral<T>::TYPE& VEC_C, const typename Quadrilateral<T>::TYPE& VEC_D)
{
    a() = VEC_A;
    b() = VEC_B;
    c() = VEC_C;
    d() = VEC_D;
    return *this;
}

template <typename T>
Quadrilateral<T>& Quadrilateral<T>::operator =(const Quadrilateral<T>& REF)
{
    a()=REF.a();
    b()=REF.b();
    c()=REF.c();
    d()=REF.d();
    return *this;
}

/*
template <typename T>
BOOLEAN Quadrilateral<T>::operator ==(const Quadrilateral<T_VECTOR>& REF) const{return A()==REF.A() && B()==REF.B() && C()==REF.C() && D()==REF.D();}

template <typename T>
BOOLEAN Quadrilateral<T>::operator !=(const Quadrilateral<T_VECTOR>& REF) const{return A()!=REF.A() || B()!=REF.B() || C()!=REF.C() || D()!=REF.D();}

template <typename T_VECTOR>
boolean Quadrilateral<T_VECTOR>::operator >(const Quadrilateral<T_VECTOR>& REF) const{return A()>REF.A() && B()>REF.B() && C()>REF.C() && D()>REF.D();}

template <typename T_VECTOR>
boolean Quadrilateral<T_VECTOR>::operator <(const Quadrilateral<T_VECTOR>& REF) const{return A()<REF.A() && B()<REF.B() && C()<REF.C() && D()<REF.D();}

template <typename T_VECTOR>
boolean Quadrilateral<T_VECTOR>::operator >=(const Quadrilateral<T_VECTOR>& REF) const{return A()>=REF.A() && B()>=REF.B() && C()>=REF.C() && D()>=REF.D();}

template <typename T_VECTOR>
boolean Quadrilateral<T_VECTOR>::operator <=(const Quadrilateral<T_VECTOR>& REF) const{return A()<=REF.A() && B()<=REF.B() && C()<=REF.C() && D()<=REF.D();}
*/

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
