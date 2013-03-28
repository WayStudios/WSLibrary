/*******************************************************************************
 * Way Studios Library
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

    void initialize();
    void destroy();

    BOOLEAN lock();
    BOOLEAN unlock();

    BOOLEAN tryLock();

    Mutex* handle;
    BOOLEAN locked;
    Thread* owner;
#if defined(API_POSIX)
    pthread_mutex_t pthread_mutex;
#elif defined(API_MSWINDOWS)
    HANDLE h_mutex;
#endif
};

END_WS_NAMESPACE

END_HEADER

#endif
