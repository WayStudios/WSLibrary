/*******************************************************************************
 * WayStudio Network Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <internetsocket.hpp>
#include <internetsocketimpl.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
InternetSocket::InternetSocketImplementation::InternetSocketImplementation(){}

InternetSocket::InternetSocketImplementation::~InternetSocketImplementation(){}

InternetSocket::InternetSocket(Object* OBJ):Socket(WS_INTERNETSOCKET, OBJ),Implementation(0){}

InternetSocket::~InternetSocket()
{
    if(Implementation);
}

boolean InternetSocket::IsConnected() const
{
    return false;
}

boolean InternetSocket::IsListening() const
{
    return false;
}

void InternetSocket::Shutdown(){}

void InternetSocket::ProcessEvent(Event* E)
{
//    Object::ProcessEvent(E);
}

END_SOURCECODE
