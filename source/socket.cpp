/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <socket.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

Socket::Socket(TYPEID TI, Object* OBJ) : Object(OBJ), family(TI) {
}

Socket::~Socket() {
}

BOOLEAN Socket::isConnected() const {
    return false;
}

BOOLEAN Socket::isListening() const {
    return false;
}

void Socket::shutdown() {
}

END_SOURCECODE
