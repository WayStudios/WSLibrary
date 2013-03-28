/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef SIGNALIMPLEMENTATION_HEADER
#define	SIGNALIMPLEMENTATION_HEADER

#include <signal.hpp>
#include <slot.hpp>
#include <signalslotevent.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_OBJ,typename T_SIGN,typename T_ARG>
class LOCAL SignalImplementation:public Signal
{
    UNCOPYABLE(SignalImplementation)
            
    T_SIGN Identity;
public:
    explicit SignalImplementation(const T_SIGN&, const String&, T_OBJ*);
    ~SignalImplementation();

	void Emit(const SharedPointer<SignalSlotArgument>&);
};

template <typename T_OBJ,typename T_SIGN,typename T_ARG>
SignalImplementation<T_OBJ,T_SIGN,T_ARG>::SignalImplementation(const T_SIGN& REF_SIGN, const String& REF_STR, T_OBJ* P_OBJ):Signal(REF_STR,static_cast<Object*>(P_OBJ)),Identity(REF_SIGN){}

template <typename T_OBJ,typename T_SIGN,typename T_ARG>
SignalImplementation<T_OBJ,T_SIGN,T_ARG>::~SignalImplementation(){}

template <typename T_OBJ,typename T_SIGN,typename T_ARG>
void SignalImplementation<T_OBJ,T_SIGN,T_ARG>::Emit(const SharedPointer<SignalSlotArgument>& SP_ARG)
{
	if(!Connections().Empty() && Host() && SP_ARG)
	{
		for(Vector<Slot*>::Iterator ITER=Connections().Begin();ITER!=Connections().End();++ITER)
			Host()->PostEvent(new SignalSlotEvent(Name(), (*ITER)->Name(), SP_ARG), (*ITER)->Host(), Host());
	}
}

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
