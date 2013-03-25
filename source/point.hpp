/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef POINT_HEADER
#define	POINT_HEADER

#include <global.hpp>
#include <vector2.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE

template <typename T_VECTOR>
struct EXPORT Point
{
    typedef T_VECTOR VALUE;
    
    explicit Point(const T_VECTOR& V_VEC=T_VECTOR());
    Point(const Point<T_VECTOR>&);
    ~Point();
    
    T_VECTOR& Vector();
    
    const T_VECTOR& Vector() const;
    
    Point<T_VECTOR>& Set(const T_VECTOR&);
    
    T_VECTOR& operator[](size);
    
    const T_VECTOR& operator[](size) const;

    Point<T_VECTOR>& operator=(const Point<T_VECTOR>&);

    boolean operator==(const Point<T_VECTOR>&) const;
    boolean operator!=(const Point<T_VECTOR>&) const;

    boolean operator>(const Point<T_VECTOR>&) const;
    boolean operator<(const Point<T_VECTOR>&) const;

    boolean operator>=(const Point<T_VECTOR>&) const;
    boolean operator<=(const Point<T_VECTOR>&) const;

    const size Capacity;
    T_VECTOR Array[1];
};

//typedef Point<Vector2> Point2;

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#include <point_impl.hpp>
        
#endif
