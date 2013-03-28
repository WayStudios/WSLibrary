/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <pixel.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
Color Pixel::operator ()(UINTEGER V){return Color((V>>16)&0xff, (V>>8)&0xff), V&0xff, V>>24;}

UINTEGER Pixel::operator ()(const Color& REF){return ((REF.alpha()&0xff)<<24)|((REF.red()&0xff)<<16)|((REF.green()&0xff)<<8)|(REF.blue()&0xff);}
        
END_SOURCECODE
