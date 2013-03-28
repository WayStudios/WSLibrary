/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef POINT_IMPLEMENTATION_HEADER
#define	POINT_IMPLEMENTATION_HEADER

#include <point.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T>
Point<T>::Point(const typename Point<T>::TYPE& V_VEC) : capacity(1) {
    array[0] = V_VEC;
}

template <typename T>
Point<T>::Point(const Point<T>& REF) : capacity(1) {
    array[0] = REF.array[0];
}

template <typename T>
Point<T>::~Point() {}

template <typename T>
typename Point<T>::TYPE& Point<T>::vector() {
	return array[0];
}

template <typename T>
const typename Point<T>::TYPE& Point<T>::vector() const {
	return array[0];
}

template <typename T>
Point<T>& Point<T>::set(const typename Point<T>::TYPE& V_VEC) {
    vector() = V_VEC;
    return *this;
}

template <typename T>
typename Point<T>::TYPE& Point<T>::operator [](SIZE IDX) {
	return array[IDX];
}

template <typename T>
const typename Point<T>::TYPE& Point<T>::operator [](SIZE IDX) const {
	return array[IDX];
}

template <typename T>
Point<T>& Point<T>::operator =(const Point<T>& REF) {
    vector() = REF.vector();
    return *this;
}

template <typename T>
BOOLEAN Point<T>::operator ==(const Point<T>& REF) const {
	return vector() == REF.vector();
}

template <typename T>
BOOLEAN Point<T>::operator !=(const Point<T>& REF) const {
	return vector() != REF.vector();
}

template <typename T>
BOOLEAN Point<T>::operator >(const Point<T>& REF) const {
	return vector() > REF.vector();
}

template <typename T>
BOOLEAN Point<T>::operator <(const Point<T>& REF) const {
	return vector() < REF.vector();
}

template <typename T>
BOOLEAN Point<T>::operator >=(const Point<T>& REF) const {
	return vector() >= REF.vector();
}

template <typename T>
BOOLEAN Point<T>::operator <=(const Point<T>& REF) const {
	return vector()<=REF.vector();
}

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
