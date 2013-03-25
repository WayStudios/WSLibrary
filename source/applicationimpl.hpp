/*******************************************************************************
 * WayStudio Library
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

    Application* H_Application;
    //   Thread* H_Thread;
    ThreadSpecific* H_ThreadSpecific;
    List<String> LST_Argument;

    UNCOPYABLE(ApplicationSpecific)
};

class LOCAL Application::ApplicationImplementation {
    UNCOPYABLE(ApplicationImplementation)
public:
    ApplicationImplementation();
    ~ApplicationImplementation();

    boolean Initial(integer, byte**, Application*);
    void Cleanup();

    static integer Execute(ApplicationSpecific*);
    static void Terminate();

    static ApplicationSpecific* H_Instance;

#if defined(API_MACOSX)
    //NSApplication
#endif
    ApplicationSpecific* H_Specific;
};

END_WS_NAMESPACE

END_HEADER

#endif
