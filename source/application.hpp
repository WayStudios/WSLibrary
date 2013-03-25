/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef APPLICATION_HEADER
#define	APPLICATION_HEADER

#include <object.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT Application : public Object {
    DECLARE_IMPLEMENTATION(Application)
    UNCOPYABLE(Application)
public:
    Application(integer, byte**);
    virtual ~Application();

    boolean IsRunning() const;

    integer Execute();
    void Terminate();

    static Application* Instance();
};

END_WS_NAMESPACE

END_HEADER

#endif
