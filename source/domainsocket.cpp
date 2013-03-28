/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <domainsocket.hpp>
#include <domainsocketimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

DomainSocket::DomainSocketImplementation::DomainSocketImplementation() : listening(false)
																	   , connected(false)
#if defined(API_POSIX)
, fd_socket(0)
#elif defined(API_MSWINDOWS)
																	   , hSocket(NULL)
#endif
{
}

DomainSocket::DomainSocketImplementation::~DomainSocketImplementation() {
}

BOOLEAN DomainSocket::DomainSocketImplementation::listenAt(const String&) {
#if defined(API_POSIX)
    if ((fd_socket = socket(AF_LOCAL, SOCK_STREAM, 0)) != -1) {
        socket_address.sun_family = AF_LOCAL;
        //        socket_address.sun_path=Path.CString();
        socket_address.sun_len = 0;
        if (bind(fd_socket, reinterpret_cast<sockaddr*> (&socket_address), sizeof (socket_address)) != -1)
            if (listen(fd_socket, SOMAXCONN) != -1);
    }
#elif defined(API_MSWINDOWS)
    ConnectNamedPipe(hSocket, 0);
#endif        
    return false;
}

BOOLEAN DomainSocket::DomainSocketImplementation::connectTo(const String&) {
#if defined(API_POSIX)
    if ((fd_socket = socket(AF_LOCAL, SOCK_STREAM, 0)) != -1) {
        socket_address.sun_family = AF_LOCAL;
        //      socket_address.sun_path;
        socket_address.sun_len = 0;
        if (connect(fd_socket, reinterpret_cast<sockaddr*> (&socket_address), sizeof (socket_address)) != -1)
            return true;
    }
#elif defined(API_MSWINDOWS)
    //	CallNamedPipe();
#endif
    return false;
}

void DomainSocket::DomainSocketImplementation::shutdown() {
#if defined(API_POSIX)
    shutdown(fd_socket, SHUT_RDWR);
    fd_socket = 0;
#elif defined(API_MSWINDOWS)
    CloseHandle(hSocket);
#endif
}

DomainSocket::DomainSocket(Object* OBJ) : Socket(WS_DOMAINSOCKET, OBJ), implementation(0) {
    implementation = new DomainSocketImplementation;
}

DomainSocket::~DomainSocket() {
    shutdown();
    if (implementation)
        delete implementation;
}

const String DomainSocket::path() const {
    if (implementation)
        return implementation->path;
    return String();
}

BOOLEAN DomainSocket::listenAt(const String& STR) {
    if (implementation)
        return implementation->listenAt(STR);
    return false;
}

BOOLEAN DomainSocket::connectTo(const String& STR) {
    if (implementation)
        return implementation->connectTo(STR);
    return false;
}

BOOLEAN DomainSocket::isConnected() const {
    if (implementation)
        return implementation->connected;
    return false;
}

BOOLEAN DomainSocket::isListening() const {
    if (implementation)
        return implementation->listening;
    return false;
}

void DomainSocket::shutdown() {
    if (implementation)
        implementation->shutdown();
}

void DomainSocket::processEvent(Event*) {
}

END_WS_NAMESPACE

END_SOURCECODE
