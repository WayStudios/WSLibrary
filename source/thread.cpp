/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <thread.hpp>
#include <threadimpl.hpp>
#include <eventloopimpl.hpp>
#include <eventdispatcher.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

#if defined(API_POSIX)
void thread_create_key() {
    pthread_key_create(&thread_pthread_key, 0);
}
#elif defined(API_MSWINDOWS)
static DWORD thread_tls_index = TLS_OUT_OF_INDEXES;

DWORD thread_tls() {
    if (thread_tls_index == TLS_OUT_OF_INDEXES) {
        if ((thread_tls_index = TlsAlloc()) == TLS_OUT_OF_INDEXES)
            throw;
    }
    return thread_tls_index;
}
#endif

ThreadSpecific::ThreadSpecific(Thread* P_TH) : H_Thread(P_TH), H_EventQueue(0), H_EventLoopSpecific(0) {
}

ThreadSpecific::~ThreadSpecific() {
}

#if defined(API_POSIX)

void* Thread::ThreadImplementation::StartRoutine(void* P) {
    pthread_once(&thread_pthread_once_init, thread_create_key);
    ThreadImplementation *self = reinterpret_cast<Thread::ThreadImplementation*> (P);
    if (self) {
        ThreadSpecific Specific(self->H_Thread);
        self->H_Specific = &Specific;
        EventQueue TH_EQ;
        EventDispatcher TH_ED(Specific.H_Thread);
        EventLoop TH_EL(&TH_EQ, &TH_ED, Specific.H_Thread);
        pthread_setspecific(thread_pthread_key, &Specific);
        Specific.H_EventQueue = &TH_EQ;
        Specific.H_Thread->Routine();
        TH_EL.Enter();
        Specific.H_EventQueue = 0;
        self->H_Specific = 0;
        TH_EQ.Destroy();
    }
    return 0;
}
#elif defined(API_MSWINDOWS)

DWORD WINAPI Thread::ThreadImplementation::StartRoutine(LPVOID P) {
    ThreadImplementation *self = reinterpret_cast<Thread::ThreadImplementation*> (P);
    if (self) {
        ThreadSpecific Specific(self->H_Thread);
        self->H_Specific = &Specific;
        EventQueue TH_EQ;
        EventDispatcher TH_ED(Specific.H_Thread);
        EventLoop TH_EL(&TH_EQ, &TH_ED, Specific.H_Thread);
        TlsSetValue(thread_tls(), &Specific);
        Specific.H_EventQueue = &TH_EQ;
        Specific.H_Thread->Routine();
        TH_EL.Enter();
        Specific.H_EventQueue = 0;
        self->H_Specific = 0;
        TH_EQ.Destroy();
    }
    return 0;
}
#endif

Thread::ThreadImplementation::ThreadImplementation(Thread* P_TH) : H_Thread(P_TH), H_Specific(0) {
}

Thread::ThreadImplementation::~ThreadImplementation() {
}

void Thread::ThreadImplementation::Execute() {
    FixSpecific();
    if (!H_Specific) {
#if defined(API_POSIX)
        pthread_create(&H_PThread, 0, Thread::ThreadImplementation::StartRoutine, reinterpret_cast<void*> (this));
#elif defined(API_MSWINDOWS)
        H_MSThread = CreateThread(0, 0, Thread::ThreadImplementation::StartRoutine, reinterpret_cast<void*> (this), 0, 0);
#endif
    }
}

void Thread::ThreadImplementation::Terminate() {
    FixSpecific();
    if (H_Specific) {
        if (H_Specific->H_EventLoopSpecific)
            if (H_Specific->H_EventLoopSpecific->H_EventLoop)
                H_Specific->H_EventLoopSpecific->H_EventLoop->Exit();
    } else {
#if defined(API_POSIX)
        pthread_cancel(H_PThread);
#elif defined(API_MSWINDOWS)
        TerminateThread(H_MSThread, 0);
#endif
    }
}

void Thread::ThreadImplementation::Finish() {
    FixSpecific();
    if (H_Specific)
        if (H_Specific->H_EventLoopSpecific)
            if (H_Specific->H_EventLoopSpecific->H_EventLoop)
                H_Specific->H_EventLoopSpecific->H_EventLoop->Exit();
}

void Thread::ThreadImplementation::FixSpecific() {
    if (!H_Specific) {
#if defined(API_POSIX)
        pthread_once(&thread_pthread_once_init, thread_create_key);
        H_Specific = reinterpret_cast<ThreadSpecific*> (pthread_getspecific(thread_pthread_key));
#elif defined(API_MSWINDOWS)
        thread_tls();
        H_Specific = reinterpret_cast<ThreadSpecific*> (TlsGetValue(thread_tls_index));
#endif
        if (H_Specific)
            if (H_Specific->H_Thread != H_Thread)
                H_Specific = 0;
            else {
#if defined(API_POSIX)
                H_PThread = pthread_self();
#elif defined(API_MSWINDOWS)
                H_MSThread = GetCurrentThread();
#endif
            }
    }
}

Thread* Thread::Current() {
    ThreadSpecific* P_THSPEC = 0;
#if defined(API_POSIX)
    pthread_once(&thread_pthread_once_init, thread_create_key);
    P_THSPEC = reinterpret_cast<ThreadSpecific*> (pthread_getspecific(thread_pthread_key));
#elif defined(API_MSWINDOWS)
    P_THSPEC = reinterpret_cast<ThreadSpecific*> (TlsGetValue(thread_tls()));
#endif
    if (P_THSPEC)
        return P_THSPEC->H_Thread;
    return 0;
}

Thread::Thread(Object* OBJ) : Object(OBJ), Implementation(0) {
    Implementation = new ThreadImplementation(this);
}

Thread::~Thread() {
    if (Implementation)
        delete Implementation;
}

boolean Thread::IsRunning() const {
    if (Implementation) {
        if (Thread::Current() == Implementation->H_Thread)
            return true;
        Implementation->FixSpecific();
        if (Implementation->H_Specific)
            if (Implementation->H_Specific->H_EventLoopSpecific)
                return Implementation->H_Specific->H_EventLoopSpecific->H_EventLoop->IsActive();
    }
    return false;
}

void Thread::Execute() {
    if (Implementation)
        return Implementation->Execute();
}

void Thread::Terminate() {
    if (Implementation)
        return Implementation->Terminate();
}

void Thread::Finish() {
    if (Implementation)
        return Implementation->Finish();
}

boolean Thread::PostEvent(Event* E, Object* R, Object* S) {
    if (Implementation) {
        Implementation->FixSpecific();
        if (Implementation->H_Specific)
            if (Implementation->H_Specific->H_EventQueue) {
                Implementation->H_Specific->H_EventQueue->Append(E, R, S);
                return true;
            }
    }
    return false;
}

void Thread::Routine() {
}

END_WS_NAMESPACE

END_SOURCECODE
