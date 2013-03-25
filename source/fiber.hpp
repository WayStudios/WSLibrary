/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef FIBER_HEADER
#define	FIBER_HEADER

#include <object.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class Thread;

class EXPORT Fiber : public Object {
    DECLARE_IMPLEMENTATION(Fiber)
    UNCOPYABLE(Fiber)
public:
    explicit Fiber(Object* OBJ = 0);
    virtual ~Fiber();

    Thread* Owner() const;

    void Execute();
    void Terminate();
    void Finish();
    boolean Swap(Fiber*);

    static Fiber* Current();
    static boolean Swap(Fiber*, Fiber*);
protected:
    virtual void Routine() = 0;
};

END_WS_NAMESPACE

END_HEADER

#endif
