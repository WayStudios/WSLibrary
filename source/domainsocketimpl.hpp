/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef DOMAINSOCKETIMPLEMENTATION_HEADER
#define	DOMAINSOCKETIMPLEMENTATION_HEADER

#include <domainsocket.hpp>
#if defined(API_POSIX)
#include <sys/socket.h>
#include <sys/un.h>
#elif defined(API_MSWINDOWS)
#include <windows.h>
#endif

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL DomainSocket::DomainSocketImplementation {
    UNCOPYABLE(DomainSocketImplementation)
public:
    DomainSocketImplementation();
    ~DomainSocketImplementation();

    BOOLEAN listenAt(const String&);
    BOOLEAN connectTo(const String&);
    void shutdown();

    String path;
    BOOLEAN connected;
    BOOLEAN listening;
#if defined(API_POSIX)
    integer fd_socket;
    sockaddr_un socket_address;
#elif defined(API_MSWINDOWS)
    HANDLE hSocket; //NamedPipe
#endif
};

END_WS_NAMESPACE

END_HEADER

#endif
