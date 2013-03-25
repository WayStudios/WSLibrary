/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef TRIANGLE_HEADER
#define	TRIANGLE_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_VECTOR>
struct EXPORT Triangle
{
    typedef T_VECTOR VALUE;

    explicit Triangle(const T_VECTOR& VEC_A=T_VECTOR(), const T_VECTOR& VEC_B=T_VECTOR(), const T_VECTOR& VEC_C=T_VECTOR());
    Triangle(const Triangle<T_VECTOR>&);
    ~Triangle();
    
    T_VECTOR& A();
    T_VECTOR& B();
    T_VECTOR& C();

    const T_VECTOR& A() const;
    const T_VECTOR& B() const;
    const T_VECTOR& C() const;

    Triangle<T_VECTOR>& Set(const T_VECTOR&, const T_VECTOR&, const T_VECTOR&);
    
    Triangle<T_VECTOR>& operator=(const Triangle<T_VECTOR>&);
    
    boolean operator==(const Triangle<T_VECTOR>&) const;
    boolean operator!=(const Triangle<T_VECTOR>&) const;
    
    boolean operator>(const Triangle<T_VECTOR>&) const;
    boolean operator<(const Triangle<T_VECTOR>&) const;

    boolean operator>=(const Triangle<T_VECTOR>&) const;
    boolean operator<=(const Triangle<T_VECTOR>&) const;

    const size Capacity;
    T_VECTOR Array[3];
};

#include <vector2.hpp>
/*
typedef Triangle<Vector2B> Triangle2B;
typedef Triangle<Vector2S> Triangle2S;
typedef Triangle<Vector2I> Triangle2I;
typedef Triangle<Vector2F> Triangle2F;
typedef Triangle<Vector2D> Triangle2D;
typedef Triangle<Vector2V> Triangle2V;
*/        
END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER
        
#include <triangle_impl.hpp>

#endif
