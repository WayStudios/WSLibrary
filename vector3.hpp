/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef VECTOR3_HEADER
#define	VECTOR3_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
struct EXPORT Vector3
{
    typedef variable VALUE;

    explicit Vector3(VALUE V_X=0, VALUE V_Y=0, VALUE V_Z=0);
    Vector3(const Vector3&);
    ~Vector3();
    
    VALUE& X();
    VALUE& Y();
    VALUE& Z();

    const VALUE& X() const;
    const VALUE& Y() const;
    const VALUE& Z() const;
    
    Vector3& Set(VALUE, VALUE, VALUE);
    
    VALUE& operator[](size);
    
    const VALUE& operator[](size) const;
    
    Vector3& operator=(const Vector3&);
    
    boolean operator==(const Vector3&) const;
    boolean operator!=(const Vector3&) const;
    
    boolean operator>(const Vector3&) const;
    boolean operator<(const Vector3&) const;
        
    boolean operator>=(const Vector3&) const;
    boolean operator<=(const Vector3&) const;

    const size Capacity;
    VALUE Array[3];
};

typedef Vector3 vec3;
        
END_WS_NAMESPACE
        
END_HEADER

#endif
