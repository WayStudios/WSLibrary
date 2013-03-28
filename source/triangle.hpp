/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef TRIANGLE_HEADER
#define	TRIANGLE_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T>
struct EXPORT Triangle
{
    typedef T TYPE;

    explicit Triangle(const TYPE& VEC_A = TYPE(), const TYPE& VEC_B = TYPE(), const TYPE& VEC_C = TYPE());
    Triangle(const Triangle<T>&);
    ~Triangle();
    
    TYPE& a();
    TYPE& b();
    TYPE& c();

    const TYPE& a() const;
    const TYPE& b() const;
    const TYPE& c() const;

    Triangle<T>& set(const TYPE&, const TYPE&, const TYPE&);
    
    Triangle<T>& operator =(const Triangle<T>&);
    
    BOOLEAN operator ==(const Triangle<T>&) const;
    BOOLEAN operator !=(const Triangle<T>&) const;
    
    BOOLEAN operator >(const Triangle<T>&) const;
    BOOLEAN operator <(const Triangle<T>&) const;

    BOOLEAN operator >=(const Triangle<T>&) const;
    BOOLEAN operator <=(const Triangle<T>&) const;

    const SIZE capacity;
    TYPE array[3];
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
