/*******************************************************************************
 * Way Studios Library
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

ThreadSpecific::ThreadSpecific(Thread* P_TH) : thread(P_TH), eventQueue(0), eventLoopSpecific(0) {
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

DWORD WINAPI Thread::ThreadImplementation::startRoutine(LPVOID P) {
    ThreadImplementation *self = reinterpret_cast<Thread::ThreadImplementation*> (P);
    if (self) {
        ThreadSpecific Specific(self->thread);
        self->threadSpecific = &Specific;
        EventQueue TH_EQ;
        EventDispatcher TH_ED(Specific.thread);
        EventLoop TH_EL(&TH_EQ, &TH_ED, Specific.thread);
        TlsSetValue(thread_tls(), &Specific);
        Specific.eventQueue = &TH_EQ;
        Specific.thread->routine();
        TH_EL.enter();
        Specific.eventQueue = 0;
        self->threadSpecific = 0;
        TH_EQ.destroy();
    }
    return 0;
}
#endif

Thread::ThreadImplementation::ThreadImplementation(Thread* P_TH) : thread(P_TH), threadSpecific(0) {
}

Thread::ThreadImplementation::~ThreadImplementation() {
}

void Thread::ThreadImplementation::execute() {
    fixSpecific();
    if (!threadSpecific) {
#if defined(API_POSIX)
        pthread_create(&H_PThread, 0, Thread::ThreadImplementation::StartRoutine, reinterpret_cast<void*> (this));
#elif defined(API_MSWINDOWS)
        hThread = CreateThread(0, 0, Thread::ThreadImplementation::startRoutine, reinterpret_cast<void*> (this), 0, 0);
#endif
    }
}

void Thread::ThreadImplementation::terminate() {
    fixSpecific();
    if (threadSpecific) {
        if (threadSpecific->eventLoopSpecific)
            if (threadSpecific->eventLoopSpecific->eventLoop)
                threadSpecific->eventLoopSpecific->eventLoop->exit();
    } else {
#if defined(API_POSIX)
        pthread_cancel(H_PThread);
#elif defined(API_MSWINDOWS)
        TerminateThread(hThread, 0);
#endif
    }
}

void Thread::ThreadImplementation::finish() {
    fixSpecific();
    if (threadSpecific)
        if (threadSpecific->eventLoopSpecific)
            if (threadSpecific->eventLoopSpecific->eventLoop)
                threadSpecific->eventLoopSpecific->eventLoop->exit();
}

void Thread::ThreadImplementation::fixSpecific() {
    if (!threadSpecific) {
#if defined(API_POSIX)
        pthread_once(&thread_pthread_once_init, thread_create_key);
        H_Specific = reinterpret_cast<ThreadSpecific*> (pthread_getspecific(thread_pthread_key));
#elif defined(API_MSWINDOWS)
        thread_tls();
        threadSpecific = reinterpret_cast<ThreadSpecific*> (TlsGetValue(thread_tls_index));
#endif
        if (threadSpecific)
            if (threadSpecific->thread != thread)
                threadSpecific = 0;
            else {
#if defined(API_POSIX)
                H_PThread = pthread_self();
#elif defined(API_MSWINDOWS)
                hThread = GetCurrentThread();
#endif
            }
    }
}

Thread* Thread::current() {
    ThreadSpecific* P_THSPEC = 0;
#if defined(API_POSIX)
    pthread_once(&thread_pthread_once_init, thread_create_key);
    P_THSPEC = reinterpret_cast<ThreadSpecific*> (pthread_getspecific(thread_pthread_key));
#elif defined(API_MSWINDOWS)
    P_THSPEC = reinterpret_cast<ThreadSpecific*> (TlsGetValue(thread_tls()));
#endif
    if (P_THSPEC)
        return P_THSPEC->thread;
    return 0;
}

Thread::Thread(Object* OBJ) : Object(OBJ), implementation(0) {
    implementation = new ThreadImplementation(this);
}

Thread::~Thread() {
    if (implementation)
        delete implementation;
}

BOOLEAN Thread::isRunning() const {
    if (implementation) {
        if (Thread::current() == implementation->thread)
            return true;
        implementation->fixSpecific();
        if (implementation->threadSpecific)
            if (implementation->threadSpecific->eventLoopSpecific)
                return implementation->threadSpecific->eventLoopSpecific->eventLoop->isActive();
    }
    return false;
}

void Thread::execute() {
    if (implementation)
        return implementation->execute();
}

void Thread::terminate() {
    if (implementation)
        return implementation->terminate();
}

void Thread::finish() {
    if (implementation)
        return implementation->finish();
}

BOOLEAN Thread::postEvent(Event* E, Object* R, Object* S) {
    if (implementation) {
        implementation->fixSpecific();
        if (implementation->threadSpecific)
            if (implementation->threadSpecific->eventLoopSpecific) {
				implementation->threadSpecific->eventLoopSpecific->eventLoop->postEvent(E, R, S);
                return true;
            }
			else
				if (implementation->threadSpecific->eventQueue)
					implementation->threadSpecific->eventQueue->append(E, R, S);
    }
    return false;
}

BOOLEAN Thread::sendEvent(Event* E, Object* R, Object* S) {
    if (implementation) {
        implementation->fixSpecific();
        if (implementation->threadSpecific)
            if (implementation->threadSpecific->eventLoopSpecific)
				return implementation->threadSpecific->eventLoopSpecific->eventLoop->sendEvent(E, R, S);
			else
				return R->notifyEvent(E, R, S);
	}
	return false;
}

void Thread::routine() {
}

END_WS_NAMESPACE

END_SOURCECODE
