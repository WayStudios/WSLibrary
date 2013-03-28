/*******************************************************************************
 * Way Studios Graphics Library
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
        
    virtual BOOLEAN empty() const =0;

    virtual SIZE width() const =0;
    virtual SIZE height() const =0;
    
    virtual SIZE capacity() const=0;
protected:
    PixelBuffer();
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
