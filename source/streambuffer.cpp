/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <streambuffer.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

StreamBuffer::StreamBuffer(Object* OBJ) : Object(OBJ) {
}

StreamBuffer::~StreamBuffer() {
}

//size StreamBuffer::Capacity() const {
//    return 0;
//}

AccessMode StreamBuffer::Mode() const {
    return UNDEFINED_MODE;
}

size StreamBuffer::Read(void*, size) {
    return 0;
}

size StreamBuffer::Write(void*, size) {
    return 0;
}

size StreamBuffer::Seek(size OFFSET, SeekPosition){return 0;}

END_SOURCECODE
