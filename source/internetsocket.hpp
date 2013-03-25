/*******************************************************************************
 * WayStudio Network Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef INTERNETSOCKET_HEADER
#define	INTERNETSOCKET_HEADER

#include <socket.hpp>

BEGIN_HEADER
        
#ifndef WS_INTERNETSOCKET
#define WS_INTERNETSOCKET 0x8c
#endif
        
BEGIN_WS_NAMESPACE
        
class EXPORT InternetSocket:public Socket
{
    DECLARE_IMPLEMENTATION(InternetSocket)
    UNCOPYABLE(InternetSocket)
public:
    explicit InternetSocket(Object* OBJ=0);
    virtual ~InternetSocket();
    
    boolean IsConnected() const;
    boolean IsListening() const;
    
    void Shutdown();
protected:
    void ProcessEvent(Event*);
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
