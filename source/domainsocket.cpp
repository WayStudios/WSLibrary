/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <domainsocket.hpp>
#include <domainsocketimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

DomainSocket::DomainSocketImplementation::DomainSocketImplementation() : Listening(false), Connected(false)
#if defined(API_POSIX)
, fd_socket(0)
#elif defined(API_MSWINDOWS)
, H_Socket(NULL)
#endif
{
}

DomainSocket::DomainSocketImplementation::~DomainSocketImplementation() {
}

boolean DomainSocket::DomainSocketImplementation::Listen(const String&) {
#if defined(API_POSIX)
    if ((fd_socket = socket(AF_LOCAL, SOCK_STREAM, 0)) != -1) {
        socket_address.sun_family = AF_LOCAL;
        //        socket_address.sun_path=Path.CString();
        socket_address.sun_len = 0;
        if (bind(fd_socket, reinterpret_cast<sockaddr*> (&socket_address), sizeof (socket_address)) != -1)
            if (listen(fd_socket, SOMAXCONN) != -1);
    }
#elif defined(API_MSWINDOWS)
    ConnectNamedPipe(H_Socket, 0);
#endif        
    return false;
}

boolean DomainSocket::DomainSocketImplementation::Connect(const String&) {
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

void DomainSocket::DomainSocketImplementation::Shutdown() {
#if defined(API_POSIX)
    shutdown(fd_socket, SHUT_RDWR);
    fd_socket = 0;
#elif defined(API_MSWINDOWS)
    CloseHandle(H_Socket);
#endif
}

DomainSocket::DomainSocket(Object* OBJ) : Socket(WS_DOMAINSOCKET, OBJ), Implementation(0) {
    Implementation = new DomainSocketImplementation;
}

DomainSocket::~DomainSocket() {
    Shutdown();
    if (Implementation)
        delete Implementation;
}

const String DomainSocket::Path() const {
    if (Implementation)
        return Implementation->Path;
    return String();
}

boolean DomainSocket::Listen(const String& STR) {
    if (Implementation)
        return Implementation->Listen(STR);
    return false;
}

boolean DomainSocket::Connect(const String& STR) {
    if (Implementation)
        return Implementation->Connect(STR);
    return false;
}

boolean DomainSocket::IsConnected() const {
    if (Implementation)
        return Implementation->Connected;
    return false;
}

boolean DomainSocket::IsListening() const {
    if (Implementation)
        return Implementation->Listening;
    return false;
}

void DomainSocket::Shutdown() {
    if (Implementation)
        Implementation->Shutdown();
}

void DomainSocket::ProcessEvent(Event*) {
}

END_WS_NAMESPACE

END_SOURCECODE
