/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <pixelbuffer.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
PixelBuffer::PixelBuffer(){}

PixelBuffer::~PixelBuffer(){}

boolean PixelBuffer::Empty() const{return true;}

size PixelBuffer::Width() const{return 0;}

size PixelBuffer::Height() const{return 0;}

size PixelBuffer::Capacity() const{return 0;}
        
END_SOURCECODE
