/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef QUADRILATERAL_HEADER
#define	QUADRILATERAL_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T>
struct EXPORT Quadrilateral
{
    typedef T TYPE;

    explicit Quadrilateral(const TYPE& VEC_A = TYPE(), const TYPE& VEC_B = TYPE(), const TYPE& VEC_C = TYPE(), const TYPE& VEC_D = TYPE());
    Quadrilateral(const Quadrilateral<T>&);
    ~Quadrilateral();
    
    TYPE& a();
    TYPE& b();
    TYPE& c();
    TYPE& d();

    const TYPE& a() const;
    const TYPE& b() const;
    const TYPE& c() const;
    const TYPE& d() const;

    Quadrilateral<T>& set(const TYPE&, const TYPE&, const TYPE&, const TYPE&);
    
    Quadrilateral<T>& operator =(const Quadrilateral<T>&);
    
//    BOOLEAN operator ==(const Quadrilateral<T>&) const;
//    BOOLEAN operator !=(const Quadrilateral<T>&) const;
    
//    boolean operator>(const Quadrilateral<T_VECTOR>&) const;
//    boolean operator<(const Quadrilateral<T_VECTOR>&) const;

//    boolean operator>=(const Quadrilateral<T_VECTOR>&) const;
//    boolean operator<=(const Quadrilateral<T_VECTOR>&) const;

    const SIZE capacity;
    TYPE array[4];
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
