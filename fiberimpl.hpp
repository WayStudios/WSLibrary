/*******************************************************************************
 * WayStudio Library
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

    Fiber* H_Fiber;
    Thread* H_Thread;

    UNCOPYABLE(FiberSpecific)
};

class LOCAL Fiber::FiberImplementation {
    UNCOPYABLE(FiberImplementation)
public:
    explicit FiberImplementation(Fiber*);
    ~FiberImplementation();

    void Execute();
    void Terminate();
    void Finish();
    boolean Swap(Fiber*);

    Fiber* H_Fiber;
    FiberSpecific* H_Specific;
};

END_WS_NAMESPACE

END_HEADER

#endif
