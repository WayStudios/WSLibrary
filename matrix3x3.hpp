/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef MATRIX3X3_HEADER
#define	MATRIX3X3_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_VALUE>
struct EXPORT Matrix3x3
{
    typedef T_VALUE VALUE;
    
    T_VALUE Array[3][3];    
};

typedef Matrix3x3<byte> Matrix3x3B;
typedef Matrix3x3<word> Matrix3x3W;
typedef Matrix3x3<integer> Matrix3x3I;
typedef Matrix3x3<float32> Matrix3x3F;
typedef Matrix3x3<float64> Matrix3x3D;
        
END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
