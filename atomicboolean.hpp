/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ATOMICBOOLEAN_HEADER
#define	ATOMICBOOLEAN_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT AtomicBoolean {
    volatile boolean Value;
public:
    explicit AtomicBoolean(boolean V = false);
    AtomicBoolean(const AtomicBoolean&);
    ~AtomicBoolean();

    boolean Load() const;

    AtomicBoolean& Store(boolean);

    boolean Compare(boolean) const;

    boolean Swap(boolean);

    boolean CompareAndSwap(boolean, boolean);

    AtomicBoolean& operator=(boolean);

    boolean operator==(boolean) const;
    boolean operator!=(boolean) const;

    AtomicBoolean& operator=(const AtomicBoolean&);

    boolean operator==(const AtomicBoolean&) const;
    boolean operator!=(const AtomicBoolean&) const;
};

END_WS_NAMESPACE

END_HEADER

#endif
