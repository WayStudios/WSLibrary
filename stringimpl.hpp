/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef STRINGIMPLEMENTATION_HEADER
#define	STRINGIMPLEMENTATION_HEADER

#include <string.hpp>
#include <allocator.hpp>
#include <atomicinteger.hpp>
#include <mutex.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL String::StringImplementation : public Allocator<String::VALUE> {
    UNCOPYABLE(StringImplementation)
public:
    StringImplementation();
    ~StringImplementation();

    void ConstructString(const byte*);
    void ConstructString(const String::VALUE*, size);
    void ConstructCString(const String::VALUE*, size);
    StringImplementation* Duplicate();
    void DestructString();

#if !defined(WITHOUT_THREAD)
    AtomicInteger Ref;
    Mutex MLock;
#endif
    String::VALUE* StringB;
    byte* CStringB;
    size Length;
};

END_WS_NAMESPACE

END_HEADER

#endif
