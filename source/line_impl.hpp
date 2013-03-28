/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef LINE_IMPLEMENTATION_HEADER
#define	LINE_IMPLEMENTATION_HEADER

#include <line.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T>
Line<T>::Line(const typename Line<T>::TYPE& VEC_A, const typename Line<T>::TYPE& VEC_B) : capacity(2) {
    array[0] = VEC_A;
    array[1] = VEC_B;
}

template <typename T>
Line<T>::Line(const Line<T>& REF) : capacity(2)
{
    array[0] = REF.array[0];
    array[1] = REF.array[1];
}

template <typename T>
Line<T>::~Line(){}

template <typename T>
typename Line<T>::TYPE& Line<T>::a() {
	return array[0];
}

template <typename T>
typename Line<T>::TYPE& Line<T>::b() {
	return array[1];
}

template <typename T>
const typename Line<T>::TYPE& Line<T>::a() const {
	return array[0];
}

template <typename T>
const typename Line<T>::TYPE& Line<T>::b() const {
	return array[1];
}

template <typename T>
Line<T>& Line<T>::set(const typename Line<T>::TYPE& VEC_A, const typename Line<T>::TYPE& VEC_B) {
    a() = VEC_A;
    b() = VEC_B;
    return *this;
}

template <typename T>
typename Line<T>::TYPE& Line<T>::operator [](SIZE IDX) {
	return array[IDX];
}

template <typename T>
const typename Line<T>::TYPE& Line<T>::operator [](SIZE IDX) const {
	return array[IDX];
}

template <typename T>
Line<T>& Line<T>::operator =(const Line<T>& REF) {
    a() = REF.a();
    b() = REF.b();
    return *this;
}

template <typename T>
BOOLEAN Line<T>::operator ==(const Line<T>& REF) const {
	return a() == REF.a() && b() == REF.b();
}

template <typename T>
BOOLEAN Line<T>::operator !=(const Line<T>& REF) const {
	return a() != REF.a() || b() != REF.b();
}

template <typename T>
BOOLEAN Line<T>::operator >(const Line<T>& REF) const {
	return a() > REF.a() && b() > REF.b();
}

template <typename T>
BOOLEAN Line<T>::operator <(const Line<T>& REF) const {
	return a() < REF.a() && b() < REF.b();
}

template <typename T>
BOOLEAN Line<T>::operator >=(const Line<T>& REF) const {
	return a() >= REF.a() && b() >= REF.b();
}

template <typename T>
BOOLEAN Line<T>::operator <=(const Line<T>& REF) const {
	return a() <= REF.a() && b() <= REF.b();
}

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
