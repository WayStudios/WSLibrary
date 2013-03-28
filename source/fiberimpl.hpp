/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef FIBERIMPLEMENTATION_HEADER
#define	FIBERIMPLEMENTATION_HEADER

#include <fiber.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct LOCAL FiberSpecific {
    explicit FiberSpecific(Fiber*);
    ~FiberSpecific();

    Fiber* fiber;
    Thread* thread;

    UNCOPYABLE(FiberSpecific)
};

class LOCAL Fiber::FiberImplementation {
    UNCOPYABLE(FiberImplementation)
public:
    explicit FiberImplementation(Fiber*);
    ~FiberImplementation();

    void execute();
    void terminate();
    void finish();
    BOOLEAN swap(Fiber*);

    Fiber* fiber;
    FiberSpecific* fiberSpecific;
};

END_WS_NAMESPACE

END_HEADER

#endif
