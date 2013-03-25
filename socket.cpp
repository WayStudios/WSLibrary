/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <socket.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

Socket::Socket(ws_typeid TI, Object* OBJ) : Object(OBJ), Family(TI) {
}

Socket::~Socket() {
}

boolean Socket::IsConnected() const {
    return false;
}

boolean Socket::IsListening() const {
    return false;
}

void Socket::Shutdown() {
}

void Socket::ProcessEvent(Event*) {
}

END_SOURCECODE
