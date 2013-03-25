/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef THREAD_HEADER
#define	THREAD_HEADER

#include <object.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class EXPORT Thread:public Object
{
    DECLARE_IMPLEMENTATION(Thread)
    UNCOPYABLE(Thread)
public:
    explicit Thread(Object* OBJ=0);
    virtual ~Thread();
    
    boolean IsRunning() const;
    
    void Execute();
    void Terminate();
    void Finish();
    
    boolean PostEvent(Event*,Object* R=0,Object* S=0);
    
    static Thread* Current();
protected:
    virtual void Routine();
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
