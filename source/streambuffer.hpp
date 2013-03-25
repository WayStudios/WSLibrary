/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef STREAMBUFFER_HEADER
#define	STREAMBUFFER_HEADER


#include <object.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT StreamBuffer : public Object {

    UNCOPYABLE(StreamBuffer)
public:
    class Iterator;

    explicit StreamBuffer(Object* OBJ = 0);
    virtual ~StreamBuffer() = 0;

    //    virtual size Capacity() const = 0;

    virtual AccessMode Mode() const = 0;

    virtual size Read(void* BUF, size RD_SZ) = 0;
    virtual size Write(void* BUF, size IN_SZ) = 0;
    virtual size Seek(size OFFSET, SeekPosition);
};

END_WS_NAMESPACE

END_HEADER

#endif
