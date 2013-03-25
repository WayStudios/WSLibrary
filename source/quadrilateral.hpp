/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef QUADRILATERAL_HEADER
#define	QUADRILATERAL_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_VECTOR>
struct EXPORT Quadrilateral
{
    typedef T_VECTOR VALUE;

    explicit Quadrilateral(const T_VECTOR& VEC_A=T_VECTOR(), const T_VECTOR& VEC_B=T_VECTOR(), const T_VECTOR& VEC_C=T_VECTOR(), const T_VECTOR& VEC_D=T_VECTOR());
    Quadrilateral(const Quadrilateral<T_VECTOR>&);
    ~Quadrilateral();
    
    T_VECTOR& A();
    T_VECTOR& B();
    T_VECTOR& C();
    T_VECTOR& D();

    const T_VECTOR& A() const;
    const T_VECTOR& B() const;
    const T_VECTOR& C() const;
    const T_VECTOR& D() const;

    Quadrilateral<T_VECTOR>& Set(const T_VECTOR&, const T_VECTOR&, const T_VECTOR&, const T_VECTOR&);
    
    Quadrilateral<T_VECTOR>& operator=(const Quadrilateral<T_VECTOR>&);
    
    boolean operator==(const Quadrilateral<T_VECTOR>&) const;
    boolean operator!=(const Quadrilateral<T_VECTOR>&) const;
    
    boolean operator>(const Quadrilateral<T_VECTOR>&) const;
    boolean operator<(const Quadrilateral<T_VECTOR>&) const;

    boolean operator>=(const Quadrilateral<T_VECTOR>&) const;
    boolean operator<=(const Quadrilateral<T_VECTOR>&) const;

    const size Capacity;
    T_VECTOR Array[4];
};

#include <vector2.hpp>
/*
typedef Quadrilateral<Vector2B> Quadrilateral2B;
typedef Quadrilateral<Vector2S> Quadrilateral2S;
typedef Quadrilateral<Vector2I> Quadrilateral2I;
typedef Quadrilateral<Vector2F> Quadrilateral2F;
typedef Quadrilateral<Vector2D> Quadrilateral2D;
typedef Quadrilateral<Vector2V> Quadrilateral2V;
*/        
END_WS_NAMESPACE        
        
END_TEMPLATE
        
END_HEADER

#include <quadrilateral_impl.hpp>
        
#endif
