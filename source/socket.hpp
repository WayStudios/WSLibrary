/*******************************************************************************
 * Way Studios Library
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
    explicit Socket(TYPEID, Object* OBJ = 0);
    virtual ~Socket() = 0;

    virtual BOOLEAN isConnected() const = 0;
    virtual BOOLEAN isListening() const = 0;

    virtual void shutdown() = 0;

    const TYPEID family;
};

END_WS_NAMESPACE

END_HEADER

#endif
