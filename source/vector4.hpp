/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef VECTOR4_HEADER
#define	VECTOR4_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
struct EXPORT Vector4
{
    typedef variable VALUE;

    explicit Vector4(variable V_X=0, variable V_Y=0, variable V_Z=0, variable V_W=0);
    Vector4(const Vector4&);
    ~Vector4();

    VALUE& X();
    VALUE& Y();
    VALUE& Z();
    VALUE& W();

    const VALUE& X() const;
    const VALUE& Y() const;
    const VALUE& Z() const;
    const VALUE& W() const;
    
    Vector4& Set(VALUE, VALUE, VALUE, VALUE);
    
    VALUE& operator[](size);
    
    const VALUE& operator[](size) const;

    Vector4& operator=(const Vector4&);
    
    boolean operator==(const Vector4&) const;
    boolean operator!=(const Vector4&) const;
    
    boolean operator>(const Vector4&) const;
    boolean operator<(const Vector4&) const;
        
    boolean operator>=(const Vector4&) const;
    boolean operator<=(const Vector4&) const;
    
    const size Capacity;
    VALUE Array[4];
};

typedef Vector4 vec4;

END_WS_NAMESPACE
        
END_HEADER

#endif
