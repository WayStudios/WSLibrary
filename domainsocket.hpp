/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef DOMAINSOCKET_HEADER
#define	DOMAINSOCKET_HEADER

#include <socket.hpp>
#include <string.hpp>

BEGIN_HEADER

#ifndef WS_DOMAINSOCKET
#define WS_DOMAINSOCKET 0x8b
#endif

BEGIN_WS_NAMESPACE

class EXPORT DomainSocket : public Socket {
    DECLARE_IMPLEMENTATION(DomainSocket)
    UNCOPYABLE(DomainSocket)
public:
    explicit DomainSocket(Object* OBJ = 0);
    virtual ~DomainSocket();

    const String Path() const;

    boolean Listen(const String&);
    boolean Connect(const String&);

    boolean IsConnected() const;
    boolean IsListening() const;

    void Shutdown();
protected:
    void ProcessEvent(Event*);
};

END_WS_NAMESPACE

END_HEADER

#endif
