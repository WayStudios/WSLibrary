/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef VECTOR4_HEADER
#define	VECTOR4_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
struct EXPORT Vector4
{
    typedef VARIABLE TYPE;

    explicit Vector4(TYPE V_X = 0, TYPE V_Y = 0, TYPE V_Z = 0, TYPE V_W = 0);
    Vector4(const Vector4&);
    ~Vector4();

    TYPE& x();
    TYPE& y();
    TYPE& z();
    TYPE& w();

    const TYPE& x() const;
    const TYPE& y() const;
    const TYPE& z() const;
    const TYPE& w() const;
    
    Vector4& set(TYPE, TYPE, TYPE, TYPE);
    
    TYPE& operator [](SIZE);
    
    const TYPE& operator [](SIZE) const;

    Vector4& operator =(const Vector4&);
    
    BOOLEAN operator ==(const Vector4&) const;
    BOOLEAN operator !=(const Vector4&) const;
    
    BOOLEAN operator >(const Vector4&) const;
    BOOLEAN operator <(const Vector4&) const;
        
    BOOLEAN operator >=(const Vector4&) const;
    BOOLEAN operator <=(const Vector4&) const;
    
    const SIZE capacity;
    TYPE array[4];
};

typedef Vector4 vec4;

END_WS_NAMESPACE
        
END_HEADER

#endif
