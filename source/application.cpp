/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <application.hpp>
#include <applicationimpl.hpp>
#include <eventqueue.hpp>
#include <eventdispatcher.hpp>
#include <eventloop.hpp>
#include <eventloopimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

ApplicationSpecific::ApplicationSpecific(Application* P_APP) : H_Application(P_APP), H_ThreadSpecific(0) {
}

ApplicationSpecific::~ApplicationSpecific() {
}

ApplicationSpecific* Application::ApplicationImplementation::H_Instance = 0;

integer Application::ApplicationImplementation::Execute(ApplicationSpecific* P_APPSPEC) {
    if (!H_Instance) {
        H_Instance = P_APPSPEC;
        EventDispatcher I_ED(P_APPSPEC->H_Application);
        EventLoop I_EL(P_APPSPEC->H_ThreadSpecific->H_EventQueue, &I_ED, P_APPSPEC->H_Application);
        I_EL.Enter();
        return 0;
    }
    return -1;
}

void Application::ApplicationImplementation::Terminate() {
    if (H_Instance) {
        H_Instance->H_ThreadSpecific->H_EventLoopSpecific->H_EventLoop->Exit();
        H_Instance = 0;
    }
}

Application* Application::Instance() {
    if (ApplicationImplementation::H_Instance)
        return ApplicationImplementation::H_Instance->H_Application;
    return 0;
}

Application::ApplicationImplementation::ApplicationImplementation() : H_Specific(0) {
}

Application::ApplicationImplementation::~ApplicationImplementation() {
}

boolean Application::ApplicationImplementation::Initial(integer ARGC, byte** ARGV, Application* P_APP) {
    if (!Thread::Current()) {
        H_Specific = new ApplicationSpecific(P_APP);
        if (H_Specific) {
            for (integer i = 0; i < ARGC; ++i)
                H_Specific->LST_Argument.Append(String(ARGV[i]));
            Thread* P_TH = new Thread(static_cast<Object*> (P_APP));
            EventQueue* P_EQ = new EventQueue;
            H_Specific->H_ThreadSpecific = new ThreadSpecific(P_TH);
            if (H_Specific->H_ThreadSpecific) {
                H_Specific->H_ThreadSpecific->H_EventQueue = P_EQ;
#if defined(API_POSIX)
                pthread_once(&thread_pthread_once_init, thread_create_key);
                pthread_setspecific(thread_pthread_key, reinterpret_cast<void*> (H_Specific->H_ThreadSpecific));
#elif defined(API_MSWINDOWS)
                TlsSetValue(thread_tls(), reinterpret_cast<LPVOID> (H_Specific->H_ThreadSpecific));
#endif
                if (Thread::Current())
                    return true;
            }
        }
    }
    return false;
}

void Application::ApplicationImplementation::Cleanup() {
    if (H_Specific) {
        if (H_Specific->H_ThreadSpecific) {
            H_Specific->H_ThreadSpecific->H_EventQueue->Destroy();
            delete H_Specific->H_ThreadSpecific->H_EventQueue;
            delete H_Specific->H_ThreadSpecific;
        }
        delete H_Specific;
    }
}

Application::Application(integer ARGC, byte** ARGV) : Object(0), Implementation(0) {
    Object::SetMaster(static_cast<Object*> (this));
    Implementation = new ApplicationImplementation();
    if (Implementation)
        if (!(Implementation->Initial(ARGC, ARGV, this)))
            throw;
}

Application::~Application() {
    if (Implementation) {
        Implementation->Cleanup();
        delete Implementation;
    }
}

boolean Application::IsRunning() const {
    if (Implementation)
        if (Implementation->H_Specific)
            if (Implementation->H_Specific->H_ThreadSpecific)
                if (Implementation->H_Specific->H_ThreadSpecific->H_Thread)
                    return Implementation->H_Specific->H_ThreadSpecific->H_Thread->IsRunning();
    return false;
}

integer Application::Execute() {
    return Application::ApplicationImplementation::Execute(Implementation->H_Specific);
}

void Application::Terminate() {
    if (IsRunning())
        Application::ApplicationImplementation::Terminate();
}

END_WS_NAMESPACE

END_SOURCECODE
