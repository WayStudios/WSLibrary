/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 * todo:WS_Mutex only effect on WS_Thread
 *******************************************************************************/
#include <mutex.hpp>
#include <muteximpl.hpp>
//#include <threadimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

Mutex::MutexImplementation::MutexImplementation(Mutex* P) : handle(P), locked(false), owner(0) {
}

Mutex::MutexImplementation::~MutexImplementation() {
}

void Mutex::MutexImplementation::initialize() {
#if defined(API_POSIX)
    pthread_mutex_init(&pthread_mutex, 0);
#elif defined(API_MSWINDOWS)
    h_mutex = CreateMutex(NULL, false, NULL);
#endif
}

void Mutex::MutexImplementation::destroy() {
#if defined(API_POSIX)
    pthread_mutex_destroy(&pthread_mutex);
#elif defined(API_MSWINDOWS)
    CloseHandle(h_mutex);
#endif
}

BOOLEAN Mutex::MutexImplementation::lock() {
#if defined(API_POSIX)
    if (pthread_mutex_lock(&pthread_mutex) == 0) {
        Locked = true;
        return true;
    } else
        return false;
#elif defined(API_MSWINDOWS)
    if (WaitForSingleObject(h_mutex, INFINITE) == WAIT_OBJECT_0) {
        locked = true;
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

BOOLEAN Mutex::MutexImplementation::unlock() {
#if defined(API_POSIX)
    if (pthread_mutex_unlock(&pthread_mutex) == 0) {
        Locked = false;
        return true;
    } else
        return false;
#elif defined(API_MSWINDOWS)
    if (ReleaseMutex(h_mutex)) {
        locked = false;
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

BOOLEAN Mutex::MutexImplementation::tryLock() {
#if defined(API_POSIX)
    if (pthread_mutex_trylock(&pthread_mutex) == 0) {
        Locked = true;
        return true;
    } else
        return false;
#elif defined(API_MSWINDOWS)
    if (WaitForSingleObject(h_mutex, 0) == WAIT_OBJECT_0) {
        locked = true;
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

Mutex::Mutex() : implementation(0) {
    implementation = new MutexImplementation(this);
    if (implementation)
        implementation->initialize();
}

Mutex::~Mutex() {
    unlock();
    if (implementation) {
        implementation->destroy();
        delete implementation;
    }
}

Thread* Mutex::owner() const {
    if (implementation)
        return implementation->owner;
    return 0;
}

BOOLEAN Mutex::isLocked() const {
    if (implementation)
        return implementation->locked;
    return false;
}

BOOLEAN Mutex::lock() {
    if (implementation)
        return implementation->lock();
    return false;
}

BOOLEAN Mutex::unlock() {
    if (implementation)
        return implementation->unlock();
    return false;
}

BOOLEAN Mutex::tryLock() {
    if (implementation)
        return implementation->tryLock();
    return false;
}

END_WS_NAMESPACE

END_SOURCECODE
