/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef MATRIX2X2_HEADER
#define	MATRIX2X2_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_VALUE>
struct EXPORT Matrix2x2
{
    typedef T_VALUE VALUE;
    
    T_VALUE Array[2][2];    
};

typedef Matrix2x2<byte> Matrix2x2B;
typedef Matrix2x2<word> Matrix2x2W;
typedef Matrix2x2<integer> Matrix2x2I;
typedef Matrix2x2<float32> Matrix2x2F;
typedef Matrix2x2<float64> Matrix2x2D;
        
END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
