/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 * todo:WS_Mutex only effect on WS_Thread
 *******************************************************************************/
#include <mutex.hpp>
#include <muteximpl.hpp>
//#include <ws_threadimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

Mutex::MutexImplementation::MutexImplementation(Mutex* P) : Handle(P), Locked(false), Owner(0) {
}

Mutex::MutexImplementation::~MutexImplementation() {
}

void Mutex::MutexImplementation::Initial() {
#if defined(API_POSIX)
    pthread_mutex_init(&pthread_mutex, 0);
#elif defined(API_MSWINDOWS)
    H_MSMutex = CreateMutex(NULL, false, NULL);
#endif
}

void Mutex::MutexImplementation::Cleanup() {
#if defined(API_POSIX)
    pthread_mutex_destroy(&pthread_mutex);
#elif defined(API_MSWINDOWS)
    CloseHandle(H_MSMutex);
#endif
}

boolean Mutex::MutexImplementation::Lock() {
#if defined(API_POSIX)
    if (pthread_mutex_lock(&pthread_mutex) == 0) {
        Locked = true;
        return true;
    } else
        return false;
#elif defined(API_MSWINDOWS)
    if (WaitForSingleObject(H_MSMutex, INFINITE) == WAIT_OBJECT_0) {
        Locked = true;
        return true;
    } else
        return false;
#endif
    /*    if(Locked)
        {
            ThreadSpecific* ThreadSpecific=0;
    #if defined(API_POSIX)
            ThreadSpecific=reinterpret_cast<WS_ThreadSpecific*>(pthread_getspecific(ws_thread_pthread_key));
    #endif
            if(ThreadSpecific)
            {
                Owner=ThreadSpecific->Handle;
                ThreadSpecific->Mutex.Append(Handle);
            }
            return true;
        }*/
    return false;
}

boolean Mutex::MutexImplementation::Unlock() {
#if defined(API_POSIX)
    if (pthread_mutex_unlock(&pthread_mutex) == 0) {
        Locked = false;
        return true;
    } else
        return false;
#elif defined(API_MSWINDOWS)
    if (ReleaseMutex(H_MSMutex)) {
        Locked = false;
        return true;
    } else
        return false;
#endif
    /*    if(!Locked)
        {
            WS_ThreadSpecific* ThreadSpecific=0;
    #if defined(WS_API_POSIX)
            ThreadSpecific=reinterpret_cast<WS_ThreadSpecific*>(pthread_getspecific(ws_thread_pthread_key));
    #endif
            if(ThreadSpecific)
            {
                ThreadSpecific->Mutex.Remove(Handle);
                Owner=0;
            }
            return true;
        }*/
    return false;
}

boolean Mutex::MutexImplementation::TryLock() {
#if defined(API_POSIX)
    if (pthread_mutex_trylock(&pthread_mutex) == 0) {
        Locked = true;
        return true;
    } else
        return false;
#elif defined(API_MSWINDOWS)
    if (WaitForSingleObject(H_MSMutex, 0) == WAIT_OBJECT_0) {
        Locked = true;
        return true;
    } else
        return false;
#endif
    /*    if(Locked)
        {
            WS_ThreadSpecific* ThreadSpecific=0;
    #if defined(WS_API_POSIX)
            ThreadSpecific=reinterpret_cast<WS_ThreadSpecific*>(pthread_getspecific(ws_thread_pthread_key));
    #endif
            if(ThreadSpecific)
            {
                Owner=ThreadSpecific->Handle;
                ThreadSpecific->Mutex.Append(Handle);
            }
            return true;
        }*/
    return false;
}

Mutex::Mutex() : Implementation(0) {
    Implementation = new MutexImplementation(this);
    if (Implementation)
        Implementation->Initial();
}

Mutex::~Mutex() {
    Unlock();
    if (Implementation) {
        Implementation->Cleanup();
        delete Implementation;
    }
}

Thread* Mutex::Owner() const {
    if (Implementation)
        return Implementation->Owner;
    return 0;
}

boolean Mutex::IsLocked() const {
    if (Implementation)
        return Implementation->Locked;
    return false;
}

boolean Mutex::Lock() {
    if (Implementation)
        return Implementation->Lock();
    return false;
}

boolean Mutex::Unlock() {
    if (Implementation)
        return Implementation->Unlock();
    return false;
}

boolean Mutex::TryLock() {
    if (Implementation)
        return Implementation->TryLock();
    return false;
}

END_WS_NAMESPACE

END_SOURCECODE
