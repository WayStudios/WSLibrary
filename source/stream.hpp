/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef STREAM_HEADER
#define	STREAM_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE

class StreamBuffer;

class EXPORT Stream
{
    DECLARE_IMPLEMENTATION(Stream)
    UNCOPYABLE(Stream)
public:
    explicit Stream(StreamBuffer*);
    virtual ~Stream();
protected:
    StreamBuffer* buffer() const;
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
