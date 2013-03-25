/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <fiber.hpp>
#include <fiberimpl.hpp>
#include <threadimpl.hpp>
#if defined(API_POSIX)
//#include <ucontext.h>
#elif defined(API_MSWINDOWS)
#include <windows.h>
#endif

BEGIN_SOURCECODE

USING_WS_NAMESPACE

FiberSpecific::FiberSpecific(Fiber* P_F) : H_Fiber(P_F), H_Thread(0) {
}

FiberSpecific::~FiberSpecific() {
}

Fiber::FiberImplementation::FiberImplementation(Fiber* P_F) : H_Fiber(P_F), H_Specific(0) {
}

Fiber::FiberImplementation::~FiberImplementation() {
}

void Fiber::FiberImplementation::Execute() {
}

void Fiber::FiberImplementation::Terminate() {
}

void Fiber::FiberImplementation::Finish() {
}

boolean Fiber::FiberImplementation::Swap(Fiber*) {
    return false;
}

Fiber* Fiber::Current() {
    return 0;
}

boolean Fiber::Swap(Fiber*, Fiber*) {
    return false;
}

Fiber::Fiber(Object* OBJ) : Object(OBJ), Implementation(0) {
    Implementation = new FiberImplementation(this);
    if (Implementation) {
        Implementation->H_Specific = new FiberSpecific(this);
        if (Implementation->H_Specific)
            Implementation->H_Specific->H_Thread = Thread::Current();
    }
}

Fiber::~Fiber() {
    if (Implementation)
        delete Implementation;
}

Thread* Fiber::Owner() const {
    return 0;
}

void Fiber::Execute() {
}

void Fiber::Terminate() {
}

void Fiber::Finish() {
}

boolean Fiber::Swap(Fiber*) {
    return false;
}

void Fiber::Routine() {
}

END_SOURCECODE
