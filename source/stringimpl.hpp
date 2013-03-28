/*******************************************************************************
 * Way Studios Library
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

class LOCAL String::StringImplementation : public Allocator<String::TYPE> {
    UNCOPYABLE(StringImplementation)
public:
    StringImplementation();
    ~StringImplementation();

    void constructString(const BYTE*);
    void constructString(const String::TYPE*, SIZE);
    void constructCString(const String::TYPE*, SIZE);
    StringImplementation* duplicate();
    void destructString();

#if !defined(WITHOUT_THREAD)
    AtomicInteger ref;
    Mutex mutex;
#endif
    String::TYPE* string;
    BYTE* cstring;
    SIZE length;
};

END_WS_NAMESPACE

END_HEADER

#endif
