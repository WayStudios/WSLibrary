/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef MUTEXIMPLEMENTATION_HEADER
#define	MUTEXIMPLEMENTATION_HEADER

#include <mutex.hpp>
#if defined(API_POSIX)
#include <pthread.h>
#elif defined(API_MSWINDOWS)
#include <windows.h>
#endif

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL Mutex::MutexImplementation {
    UNCOPYABLE(MutexImplementation)
public:
    explicit MutexImplementation(Mutex*);
    ~MutexImplementation();

    void Initial();
    void Cleanup();

    boolean Lock();
    boolean Unlock();

    boolean TryLock();

    Mutex* Handle;
    boolean Locked;
    Thread* Owner;
#if defined(API_POSIX)
    pthread_mutex_t pthread_mutex;
#elif defined(API_MSWINDOWS)
    HANDLE H_MSMutex;
#endif
};

END_WS_NAMESPACE

END_HEADER

#endif
