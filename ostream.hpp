/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef OSTREAM_HEADER
#define	OSTREAM_HEADER

#include <stream.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class EXPORT OStream:public Stream
{
    UNCOPYABLE(OStream)
public:
    explicit OStream(StreamBuffer*);
    virtual ~OStream();
    
    virtual void Write(const byte* IN, size IN_SZ);
};

END_WS_NAMESPACE
        
END_HEADER

#endif
