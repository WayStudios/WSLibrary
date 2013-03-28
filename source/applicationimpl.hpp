/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef APPLICATIONIMPLEMENTATION_HEADER
#define	APPLICATIONIMPLEMENTATION_HEADER

#include <application.hpp>
#include <threadimpl.hpp>
#include <list.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct LOCAL ApplicationSpecific {
    explicit ApplicationSpecific(Application*);
    ~ApplicationSpecific();

    Application* application;
    //   Thread* H_Thread;
    ThreadSpecific* threadSpecific;
    List<String> argumentList;

    UNCOPYABLE(ApplicationSpecific)
};

class LOCAL Application::ApplicationImplementation {
    UNCOPYABLE(ApplicationImplementation)
public:
    ApplicationImplementation();
    ~ApplicationImplementation();

    BOOLEAN initialize(INTEGER, BYTE**, Application*);
    void destroy();

    static INTEGER execute(ApplicationSpecific*);
    static void terminate();

    static ApplicationSpecific* instanceSpecific;

#if defined(API_MACOSX)
    //NSApplication
#endif
    ApplicationSpecific* applicationSpecific;
};

END_WS_NAMESPACE

END_HEADER

#endif
