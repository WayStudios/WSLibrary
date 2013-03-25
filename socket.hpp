/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SOCKET_HEADER
#define	SOCKET_HEADER

#include <object.hpp>

BEGIN_HEADER

#ifndef WS_SOCKET
#define WS_SOCKET 0x8a
#endif

BEGIN_WS_NAMESPACE

class EXPORT Socket : public Object {
    UNCOPYABLE(Socket)
public:
    explicit Socket(ws_typeid, Object* OBJ = 0);
    virtual ~Socket() = 0;

    virtual boolean IsConnected() const = 0;
    virtual boolean IsListening() const = 0;

    virtual void Shutdown() = 0;

    const ws_typeid Family;
protected:
    virtual void ProcessEvent(Event*);
};

END_WS_NAMESPACE

END_HEADER

#endif
