/*******************************************************************************
 * Way Studios Library
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
    Application(INTEGER, BYTE**);
    virtual ~Application();

    BOOLEAN isRunning() const;

    INTEGER execute();
    void terminate();

    static Application* instance();
};

END_WS_NAMESPACE

END_HEADER

#endif
