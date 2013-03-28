/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef MATRIX4X4_HEADER
#define	MATRIX4X4_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_VALUE>
struct EXPORT Matrix4x4
{
    typedef T_VALUE VALUE;
    
    T_VALUE Array[4][4];    
};

typedef Matrix4x4<byte> Matrix4x4B;
typedef Matrix4x4<word> Matrix4x4W;
typedef Matrix4x4<integer> Matrix4x4I;
typedef Matrix4x4<float32> Matrix4x4F;
typedef Matrix4x4<float64> Matrix4x4D;
        
END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
