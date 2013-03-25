/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef THREADIMPLEMENTATION_HEADER
#define THREADIMPLEMENTATION_HEADER

#include <thread.hpp>
#include <mutex.hpp>
#include <list.hpp>
#if defined(API_POSIX)
#include <pthread.h>
#elif defined(API_MSWINDOWS)
#include <windows.h>
#endif

BEGIN_HEADER

BEGIN_WS_NAMESPACE

#if defined(API_POSIX)
static pthread_key_t thread_pthread_key = 0;
static pthread_once_t thread_pthread_once_init = PTHREAD_ONCE_INIT;
EXPORT void thread_create_key();
#elif defined(API_MSWINDOWS)
EXPORT DWORD thread_tls();
#endif

class EventQueue;
struct EventLoopSpecific;
struct TimerSpecific;

struct LOCAL ThreadSpecific {
    explicit ThreadSpecific(Thread*);
    ~ThreadSpecific();

    Thread* H_Thread;
    EventQueue* H_EventQueue;
    EventLoopSpecific* H_EventLoopSpecific;
    List<Mutex*> LST_Mutex;
    List<TimerSpecific*> LST_TimerSpecific;

    UNCOPYABLE(ThreadSpecific)
};

class LOCAL Thread::ThreadImplementation {
    UNCOPYABLE(ThreadImplementation)
public:
    explicit ThreadImplementation(Thread*);
    ~ThreadImplementation();

    void Execute();
    void Terminate();
    void Finish();
    void FixSpecific();

    Thread* H_Thread;
    ThreadSpecific* H_Specific;
#if defined(API_POSIX)
    static void* StartRoutine(void*);
    pthread_t H_PThread;
#elif defined(API_MSWINDOWS)
    static DWORD WINAPI StartRoutine(LPVOID);
    HANDLE H_MSThread;
#endif
};

END_WS_NAMESPACE

END_HEADER

#endif
