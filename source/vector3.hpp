/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef VECTOR3_HEADER
#define	VECTOR3_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
struct EXPORT Vector3
{
    typedef VARIABLE TYPE;

    explicit Vector3(TYPE V_X = 0, TYPE V_Y = 0, TYPE V_Z = 0);
    Vector3(const Vector3&);
    ~Vector3();
    
    TYPE& x();
    TYPE& y();
    TYPE& z();

    const TYPE& x() const;
    const TYPE& y() const;
    const TYPE& z() const;
    
    Vector3& set(TYPE, TYPE, TYPE);
    
    TYPE& operator [](SIZE);
    
    const TYPE& operator [](SIZE) const;
    
    Vector3& operator =(const Vector3&);
    
    BOOLEAN operator ==(const Vector3&) const;
    BOOLEAN operator !=(const Vector3&) const;
    
    BOOLEAN operator >(const Vector3&) const;
    BOOLEAN operator <(const Vector3&) const;
        
    BOOLEAN operator >=(const Vector3&) const;
    BOOLEAN operator <=(const Vector3&) const;

    const SIZE capacity;
    TYPE array[3];
};

typedef Vector3 vec3;
        
END_WS_NAMESPACE
        
END_HEADER

#endif
