/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef PIXELBUFFER_HEADER
#define	PIXELBUFFER_HEADER

#include <streambuffer.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE

//add format require
class EXPORT PixelBuffer:public StreamBuffer
{
    UNCOPYABLE(PixelBuffer)
public:
    virtual ~PixelBuffer() =0;
        
    virtual boolean Empty() const =0;

    virtual size Width() const =0;
    virtual size Height() const =0;
    
    virtual size Capacity() const=0;
protected:
    PixelBuffer();
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
