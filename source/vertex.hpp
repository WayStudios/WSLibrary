/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef VERTEX_HEADER
#define	VERTEX_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_VECTOR>
struct EXPORT Vertex
{
    typedef T_VECTOR VALUE;

    explicit Vertex(const T_VECTOR& V_VEC=T_VECTOR());
    Vertex(const Vertex<T_VECTOR>&);
    ~Vertex();
    
    T_VECTOR& Vector();

    const T_VECTOR& Vector() const;
    
    Vertex<T_VECTOR>& Set(const T_VECTOR&);
    
    T_VECTOR& operator[](size);
    
    const T_VECTOR& operator[](size) const;

    Vertex<T_VECTOR>& operator=(const Vertex<T_VECTOR>&);

    boolean operator==(const Vertex<T_VECTOR>&) const;
    boolean operator!=(const Vertex<T_VECTOR>&) const;

    boolean operator>(const Vertex<T_VECTOR>&) const;
    boolean operator<(const Vertex<T_VECTOR>&) const;
        
    boolean operator>=(const Vertex<T_VECTOR>&) const;
    boolean operator<=(const Vertex<T_VECTOR>&) const;

    const size Capacity;
    T_VECTOR Array[1];
};

#include <vector2.hpp>

typedef Vertex<Vector2B> Vertex2B;
typedef Vertex<Vector2S> Vertex2S;
typedef Vertex<Vector2I> Vertex2I;
typedef Vertex<Vector2F> Vertex2F;
typedef Vertex<Vector2D> Vertex2D;

#include <vector3.hpp>

typedef Vertex<Vector3B> Vertex3B;
typedef Vertex<Vector3S> Vertex3S;
typedef Vertex<Vector3I> Vertex3I;
typedef Vertex<Vector3F> Vertex3F;
typedef Vertex<Vector3D> Vertex3D;

#include <vector4.hpp>

typedef Vertex<Vector4B> Vertex4B;
typedef Vertex<Vector4S> Vertex4S;
typedef Vertex<Vector4I> Vertex4I;
typedef Vertex<Vector4F> Vertex4F;
typedef Vertex<Vector4D> Vertex4D;

END_WS_NAMESPACE
        
END_TEMPLATE

END_HEADER
        
#include <vertex_impl.hpp>

#endif
