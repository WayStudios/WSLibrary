/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <pixel.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
Color Pixel::operator ()(uinteger V){return Color((V>>16)&0xff, (V>>8)&0xff), V&0xff, V>>24;}

uinteger Pixel::operator ()(const Color& REF){return ((REF.Alpha()&0xff)<<24)|((REF.Red()&0xff)<<16)|((REF.Green()&0xff)<<8)|(REF.Blue()&0xff);}
        
END_SOURCECODE
