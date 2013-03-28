/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef TRIANGLE_IMPLEMENTATION_HEADER
#define	TRIANGLE_IMPLEMENTATION_HEADER

#include <triangle.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T>
Triangle<T>::Triangle(const typename Triangle<T>::TYPE& VEC_A, const typename Triangle<T>::TYPE& VEC_B, const typename Triangle<T>::TYPE& VEC_C) : capacity(3) {
    array[0] = VEC_A;
    array[1] = VEC_B;    
    array[2] = VEC_C;    
}

template <typename T>
Triangle<T>::Triangle(const Triangle<T>& REF) : capacity(3) {
    array[0] = REF.array[0];
    array[1] = REF.array[1];    
    array[2] = REF.array[2];    
}

template <typename T>
Triangle<T>::~Triangle() {}

template <typename T>
typename Triangle<T>::TYPE& Triangle<T>::a() {
	return array[0];
}

template <typename T>
typename Triangle<T>::TYPE& Triangle<T>::b() {
	return array[1];
}

template <typename T>
typename Triangle<T>::TYPE& Triangle<T>::c() {
	return array[2];
}

template <typename T>
const typename Triangle<T>::TYPE& Triangle<T>::a() const {
	return array[0];
}

template <typename T>
const typename Triangle<T>::TYPE& Triangle<T>::b() const {
	return array[1];
}

template <typename T>
const typename Triangle<T>::TYPE& Triangle<T>::c() const {
	return array[2];
}

template <typename T>
Triangle<T>& Triangle<T>::set(const typename Triangle<T>::TYPE& VEC_A, const typename Triangle<T>::TYPE& VEC_B, const typename Triangle<T>::TYPE& VEC_C) {
    a() = VEC_A;
    b() = VEC_B;    
    c() = VEC_C;
    return *this;
}

template <typename T>
Triangle<T>& Triangle<T>::operator =(const Triangle<T>& REF) {
    a() = REF.a();
    b() = REF.b();
    c() = REF.c();
    return *this;
}

template <typename T>
BOOLEAN Triangle<T>::operator ==(const Triangle<T>& REF) const{return a()==REF.a() && b()==REF.b() && c()==REF.c();}

template <typename T>
BOOLEAN Triangle<T>::operator !=(const Triangle<T>& REF) const{return a()!=REF.a() || b()!=REF.b() || c()!=REF.c();}

template <typename T>
BOOLEAN Triangle<T>::operator >(const Triangle<T>& REF) const{return a()>REF.a() && b()>REF.b() && c()>REF.c();}

template <typename T>
BOOLEAN Triangle<T>::operator <(const Triangle<T>& REF) const{return a()<REF.a() && b()<REF.b() && c()<REF.c();}

template <typename T>
BOOLEAN Triangle<T>::operator >=(const Triangle<T>& REF) const {
	return a() >= REF.a() && b() >= REF.b() && c() >= REF.c();
}

template <typename T>
BOOLEAN Triangle<T>::operator <=(const Triangle<T>& REF) const {
	return a() <= REF.a() && b() <= REF.b() && c() <= REF.c();
}

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
