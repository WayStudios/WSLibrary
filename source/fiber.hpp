/*******************************************************************************
 * Way Studios Library
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

    Thread* owner() const;

    void execute();
    void terminate();
    void finish();
    BOOLEAN swap(Fiber*);

    static Fiber* current();
    static BOOLEAN swap(Fiber*, Fiber*);
protected:
    virtual void routine() = 0;
};

END_WS_NAMESPACE

END_HEADER

#endif
