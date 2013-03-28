/*******************************************************************************
 * Way Studios Library
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

ApplicationSpecific::ApplicationSpecific(Application* P_APP) : application(P_APP), threadSpecific(0) {
}

ApplicationSpecific::~ApplicationSpecific() {
}

ApplicationSpecific* Application::ApplicationImplementation::instanceSpecific = 0;

INTEGER Application::ApplicationImplementation::execute(ApplicationSpecific* P_APPSPEC) {
    if (!instanceSpecific) {
        instanceSpecific = P_APPSPEC;
        EventDispatcher I_ED(P_APPSPEC->application);
        EventLoop I_EL(P_APPSPEC->threadSpecific->eventQueue, &I_ED, P_APPSPEC->application);
        I_EL.enter();
        return 0;
    }
    return -1;
}

void Application::ApplicationImplementation::terminate() {
    if (instanceSpecific) {
        instanceSpecific->threadSpecific->eventLoopSpecific->eventLoop->exit();
        instanceSpecific = 0;
    }
}

Application* Application::instance() {
    if (ApplicationImplementation::instanceSpecific)
        return ApplicationImplementation::instanceSpecific->application;
    return 0;
}

Application::ApplicationImplementation::ApplicationImplementation() : applicationSpecific(0) {
}

Application::ApplicationImplementation::~ApplicationImplementation() {
}

BOOLEAN Application::ApplicationImplementation::initialize(INTEGER ARGC, BYTE** ARGV, Application* P_APP) {
    if (!Thread::current()) {
        applicationSpecific = new ApplicationSpecific(P_APP);
        if (applicationSpecific) {
//            for (integer i = 0; i < ARGC; ++i)
//                H_Specific->LST_Argument.Append(String(ARGV[i]));
            Thread* P_TH = new Thread(static_cast<Object*> (P_APP));
            EventQueue* P_EQ = new EventQueue;
            applicationSpecific->threadSpecific = new ThreadSpecific(P_TH);
            if (applicationSpecific->threadSpecific) {
                applicationSpecific->threadSpecific->eventQueue = P_EQ;
#if defined(API_POSIX)
                pthread_once(&thread_pthread_once_init, thread_create_key);
                pthread_setspecific(thread_pthread_key, reinterpret_cast<void*> (H_Specific->H_ThreadSpecific));
#elif defined(API_MSWINDOWS)
                TlsSetValue(thread_tls(), reinterpret_cast<LPVOID> (applicationSpecific->threadSpecific));
#endif
                if (Thread::current())
                    return true;
            }
        }
    }
    return false;
}

void Application::ApplicationImplementation::destroy() {
    if (applicationSpecific) {
        if (applicationSpecific->threadSpecific) {
            applicationSpecific->threadSpecific->eventQueue->destroy();
            delete applicationSpecific->threadSpecific->eventQueue;
            delete applicationSpecific->threadSpecific;
        }
        delete applicationSpecific;
    }
}

Application::Application(INTEGER ARGC, BYTE** ARGV) : Object(0), implementation(0) {
    Object::setMaster(static_cast<Object*> (this));
    implementation = new ApplicationImplementation();
    if (implementation)
        if (!(implementation->initialize(ARGC, ARGV, this)))
            throw;
}

Application::~Application() {
    if (implementation) {
        implementation->destroy();
        delete implementation;
    }
}

BOOLEAN Application::isRunning() const {
    if (implementation)
        if (implementation->applicationSpecific)
            if (implementation->applicationSpecific->threadSpecific)
                if (implementation->applicationSpecific->threadSpecific->thread)
                    return implementation->applicationSpecific->threadSpecific->thread->isRunning();
    return false;
}

INTEGER Application::execute() {
    return Application::ApplicationImplementation::execute(implementation->applicationSpecific);
}

void Application::terminate() {
    if (isRunning())
        Application::ApplicationImplementation::terminate();
}

END_WS_NAMESPACE

END_SOURCECODE
