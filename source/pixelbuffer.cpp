/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <pixelbuffer.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
PixelBuffer::PixelBuffer(){}

PixelBuffer::~PixelBuffer(){}

BOOLEAN PixelBuffer::empty() const{return true;}

SIZE PixelBuffer::width() const{return 0;}

SIZE PixelBuffer::height() const{return 0;}

SIZE PixelBuffer::capacity() const{return 0;}
        
END_SOURCECODE
