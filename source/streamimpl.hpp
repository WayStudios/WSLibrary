/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef STREAMIMPLEMENTATION_HEADER
#define	STREAMIMPLEMENTATION_HEADER

#include <stream.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class LOCAL Stream::StreamImplementation
{
    UNCOPYABLE(StreamImplementation)
public:
    explicit StreamImplementation(StreamBuffer*);
    ~StreamImplementation();

    StreamBuffer* buffer;
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
