/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef PIXEL_HEADER
#define	PIXEL_HEADER

#include <global.hpp>
#include <color.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class Pixel
{
public:
    Color operator()(uinteger);
    uinteger operator()(const Color&);
} Pixel;
        
END_WS_NAMESPACE
        
END_HEADER

#endif
