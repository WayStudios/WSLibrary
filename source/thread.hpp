/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef THREAD_HEADER
#define	THREAD_HEADER

#include <object.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE

/*
TODO:Thread will handle the signal and slot, remove signal and slot from event 
*/
        
class EXPORT Thread:public Object
{
    DECLARE_IMPLEMENTATION(Thread)
    UNCOPYABLE(Thread)
public:
    explicit Thread(Object* OBJ=0);
    virtual ~Thread();
    
    BOOLEAN isRunning() const;
    
    void execute();
    void terminate();
    void finish();
    
    BOOLEAN postEvent(Event*, Object* R=0, Object* S=0);
    BOOLEAN sendEvent(Event*, Object* R=0, Object* S=0);

    static Thread* current();
protected:
    virtual void routine();
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
