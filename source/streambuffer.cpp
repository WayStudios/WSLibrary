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

AccessMode StreamBuffer::mode() const {
    return UNDEFINED_MODE;
}

SIZE StreamBuffer::read(void*, SIZE) {
    return 0;
}

SIZE StreamBuffer::write(void*, SIZE) {
    return 0;
}

SIZE StreamBuffer::seek(SIZE OFFSET, SeekPosition) {
	return 0;
}

END_SOURCECODE
