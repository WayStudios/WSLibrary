/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef VECTOR2_HEADER
#define	VECTOR2_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
struct EXPORT Vector2
{
    typedef variable VALUE;
    
    explicit Vector2(VALUE V_X=0, VALUE V_Y=0);
    Vector2(const Vector2&);
    ~Vector2();
    
    VALUE& X();
    VALUE& Y();
    
    const VALUE& X() const;
    const VALUE& Y() const;

    Vector2& Set(VALUE, VALUE);
    
    VALUE& operator[](size);
    
    const VALUE& operator[](size) const;
    
    Vector2& operator=(const Vector2&);
    
    boolean operator==(const Vector2&) const;
    boolean operator!=(const Vector2&) const;

    boolean operator>(const Vector2&) const;
    boolean operator<(const Vector2&) const;
        
    boolean operator>=(const Vector2&) const;
    boolean operator<=(const Vector2&) const;

    const size Capacity;
    VALUE Array[2];
};

typedef Vector2 vec2;

END_WS_NAMESPACE
                
END_HEADER

#endif
