/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef VERTEX_IMPLEMENTATION_HEADER
#define	VERTEX_IMPLEMENTATION_HEADER

#include <vertex.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_VECTOR>
Vertex<T_VECTOR>::Vertex(const T_VECTOR& V_VEC):Capacity(1)
{
    Array[0]=V_VEC;
}

template <typename T_VECTOR>
Vertex<T_VECTOR>::Vertex(const Vertex<T_VECTOR>& REF):Capacity(1)
{
    Array[0]=REF.Array[0];
}

template <typename T_VECTOR>
Vertex<T_VECTOR>::~Vertex(){}

template <typename T_VECTOR>
T_VECTOR& Vertex<T_VECTOR>::Vector(){return Array[0];}

template <typename T_VECTOR>
const T_VECTOR& Vertex<T_VECTOR>::Vector() const{return Array[0];}

template <typename T_VECTOR>
Vertex<T_VECTOR>& Vertex<T_VECTOR>::Set(const T_VECTOR& V_VEC)
{
    Vector()=V_VEC;
    return *this;
}

template <typename T_VECTOR>
T_VECTOR& Vertex<T_VECTOR>::operator[](size IDX){return Array[IDX];}

template <typename T_VECTOR>
const T_VECTOR& Vertex<T_VECTOR>::operator[](size IDX) const{return Array[IDX];}

template <typename T_VECTOR>
Vertex<T_VECTOR>& Vertex<T_VECTOR>::operator=(const Vertex<T_VECTOR>& REF)
{
    Vector()=REF.Vector();
    return *this;
}

template <typename T_VECTOR>
boolean Vertex<T_VECTOR>::operator ==(const Vertex<T_VECTOR>& REF) const{return Vector()==REF.Vector();}

template <typename T_VECTOR>
boolean Vertex<T_VECTOR>::operator !=(const Vertex<T_VECTOR>& REF) const{return Vector()!=REF.Vector();}

template <typename T_VECTOR>
boolean Vertex<T_VECTOR>::operator >(const Vertex<T_VECTOR>& REF) const{return Vector()>REF.Vector();}

template <typename T_VECTOR>
boolean Vertex<T_VECTOR>::operator <(const Vertex<T_VECTOR>& REF) const{return Vector()<REF.Vector();}

template <typename T_VECTOR>
boolean Vertex<T_VECTOR>::operator >=(const Vertex<T_VECTOR>& REF) const{return Vector()>=REF.Vector();}

template <typename T_VECTOR>
boolean Vertex<T_VECTOR>::operator <=(const Vertex<T_VECTOR>& REF) const{return Vector()<=REF.Vector();}

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
