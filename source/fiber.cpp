/*******************************************************************************
 * Way Studios Library
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

BEGIN_WS_NAMESPACE

FiberSpecific::FiberSpecific(Fiber* P_F) : fiber(P_F), thread(0) {
}

FiberSpecific::~FiberSpecific() {
}

Fiber::FiberImplementation::FiberImplementation(Fiber* P_F) : fiber(P_F), fiberSpecific(0) {
}

Fiber::FiberImplementation::~FiberImplementation() {
}

void Fiber::FiberImplementation::execute() {
}

void Fiber::FiberImplementation::terminate() {
}

void Fiber::FiberImplementation::finish() {
}

BOOLEAN Fiber::FiberImplementation::swap(Fiber*) {
    return false;
}

Fiber* Fiber::current() {
    return 0;
}

BOOLEAN Fiber::swap(Fiber*, Fiber*) {
    return false;
}

Fiber::Fiber(Object* OBJ) : Object(OBJ), implementation(0) {
    implementation = new FiberImplementation(this);
    if (implementation) {
        implementation->fiberSpecific = new FiberSpecific(this);
        if (implementation->fiberSpecific)
            implementation->fiberSpecific->thread = Thread::current();
    }
}

Fiber::~Fiber() {
    if (implementation)
        delete implementation;
}

Thread* Fiber::owner() const {
    return 0;
}

void Fiber::execute() {
}

void Fiber::terminate() {
}

void Fiber::finish() {
}

BOOLEAN Fiber::swap(Fiber*) {
    return false;
}

void Fiber::routine() {
}

END_WS_NAMESPACE

END_SOURCECODE
