/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef POINT_HEADER
#define	POINT_HEADER

#include <global.hpp>
#include <vector2.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE

template <typename T>
struct EXPORT Point
{
    typedef T TYPE;
    
    explicit Point(const TYPE& V_VEC = TYPE());
    Point(const Point<TYPE>&);
    ~Point();
    
    TYPE& vector();
    
    const TYPE& vector() const;
    
    Point<TYPE>& set(const TYPE&);
    
    TYPE& operator [](SIZE);
    
    const TYPE& operator [](SIZE) const;

    Point<TYPE>& operator =(const Point<TYPE>&);

    BOOLEAN operator ==(const Point<TYPE>&) const;
    BOOLEAN operator !=(const Point<TYPE>&) const;

    BOOLEAN operator >(const Point<TYPE>&) const;
    BOOLEAN operator <(const Point<TYPE>&) const;

    BOOLEAN operator >=(const Point<TYPE>&) const;
    BOOLEAN operator <=(const Point<TYPE>&) const;

    const SIZE capacity;
    TYPE array[1];
};

//typedef Point<Vector2> Point2;

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <point_impl.hpp>

#endif
