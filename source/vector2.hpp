/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef VECTOR2_HEADER
#define	VECTOR2_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
struct EXPORT Vector2
{
    typedef VARIABLE TYPE;
    
    explicit Vector2(TYPE V_X = 0, TYPE V_Y = 0);
    Vector2(const Vector2&);
    ~Vector2();
    
    TYPE& x();
    TYPE& y();
    
    const TYPE& x() const;
    const TYPE& y() const;

    Vector2& set(TYPE, TYPE);
    
    TYPE& operator [](SIZE);
    
    const TYPE& operator [](SIZE) const;
    
    Vector2& operator =(const Vector2&);
    
    BOOLEAN operator ==(const Vector2&) const;
    BOOLEAN operator !=(const Vector2&) const;

    BOOLEAN operator >(const Vector2&) const;
    BOOLEAN operator <(const Vector2&) const;
        
    BOOLEAN operator >=(const Vector2&) const;
    BOOLEAN operator <=(const Vector2&) const;

    const SIZE capacity;
    TYPE array[2];
};

typedef Vector2 vec2;

END_WS_NAMESPACE
                
END_HEADER

#endif
