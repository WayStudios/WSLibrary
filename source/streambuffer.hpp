/*******************************************************************************
 * Way Studios Library
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

    //    virtual const SIZE capacity() const = 0;

    virtual AccessMode mode() const = 0;

    virtual SIZE read(void* BUF, SIZE RD_SZ) = 0;
    virtual SIZE write(void* BUF, SIZE IN_SZ) = 0;
    virtual SIZE seek(SIZE OFFSET, SeekPosition);
};

END_WS_NAMESPACE

END_HEADER

#endif
