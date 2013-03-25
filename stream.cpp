/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <stream.hpp>
#include <streamimpl.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
Stream::StreamImplementation::StreamImplementation(StreamBuffer* P):Buf(P){}

Stream::StreamImplementation::~StreamImplementation(){}

Stream::Stream(StreamBuffer* BUF):Implementation(0)
{
    Implementation=new StreamImplementation(BUF);
}

Stream::~Stream(){}

StreamBuffer* Stream::Buffer() const
{
    if(Implementation)
        return Implementation->Buf;
}
        
END_SOURCECODE
