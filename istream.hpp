/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ISTREAM_HEADER
#define	ISTREAM_HEADER

#include <stream.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class EXPORT IStream:public Stream
{
    UNCOPYABLE(IStream)
public:
    explicit IStream(StreamBuffer*);
    virtual ~IStream();
    
    virtual void Read(byte* OUT, size OUT_SZ, size RD_SZ);
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
