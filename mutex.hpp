/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef MUTEX_HEADER
#define	MUTEX_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class Thread;

class EXPORT Mutex {
    DECLARE_IMPLEMENTATION(Mutex)
    UNCOPYABLE(Mutex)
public:
    Mutex();
    ~Mutex();

    Thread* Owner() const;
    boolean IsLocked() const;

    boolean Lock();
    boolean Unlock();

    boolean TryLock();
};

END_WS_NAMESPACE

END_HEADER

#endif
