/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef DEFINE_MACRO_HEADER
#define	DEFINE_MACRO_HEADER

#if !defined(BEGIN_HEADER) && !defined(END_HEADER)
#define BEGIN_HEADER
#define END_HEADER
#endif

#if !defined(BEGIN_SOURCECODE) && !defined(END_SOURCECODE)
#define BEGIN_SOURCECODE
#define END_SOURCECODE
#endif

#if !defined(BEGIN_TEMPLATE) && !defined(END_TEMPLATE)
#define BEGIN_TEMPLATE
#define END_TEMPLATE
#endif

#if !defined(BEGIN_WS_NAMESPACE) && !defined(END_WS_NAMESPACE) && !defined(USING_WS_NAMESPACE)
#define BEGIN_WS_NAMESPACE namespace WS{
#define END_WS_NAMESPACE }
#define USING_WS_NAMESPACE using namespace WS;
#endif

#if !defined(EXPORT) && !defined(IMPORT) && !defined(LOCAL) && !defined(EXTERN)
#if defined(__GNUC__)
#define EXPORT __attribute__ ((visibility("default")))
#define IMPORT __attribute__ ((visibility("default")))
#define LOCAL __attribute__ ((visibility("hidden")))
#elif defined(_MSC_VER)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#define LOCAL
#endif
#if defined(BUILD)
#define EXTERN EXPORT
#else
#define EXTERN IMPORT
#endif
#endif

#if !defined(UNCOPYABLE)
#define UNCOPYABLE(CLASS)\
private:\
    CLASS(const CLASS&);\
    CLASS& operator=(const CLASS&);
#endif

#if !defined(DECLARE_IMPLEMENTATION)
#define DECLARE_IMPLEMENTATION(CLASS)\
    private:\
        class CLASS##Implementation;\
        friend class CLASS##Implementation;\
        CLASS##Implementation* Implementation;
#endif

#if !defined(WITHOUT_SIGNALSLOT)
#if !defined(SIGNAL) && !defined(SLOT)
#define SIGNAL public
#define SLOT public
#endif
#if !defined(CONNECT_SIGNALSLOT)
#define CONNECT_SIGNALSLOT(T_ARG, T_SIGNHOST, SIGNHOST, SIGN, T_SLOTHOST, SLOTHOST, SLOT) SignalSlot::Connect<T_ARG, T_SIGNHOST, void(T_SIGNHOST::*)(T_ARG), T_SLOTHOST, void(T_SLOTHOST::*)(T_ARG)>(SIGNHOST, String(#SIGN), &T_SIGNHOST::SIGN, SLOTHOST, String(#SLOT), &T_SLOTHOST::SLOT)
#endif
#if !defined(DISCONNECT_SIGNALSLOT)
#define DISCONNECT_SIGNALSLOT(OBJ_SIGNHOST, STR_SIGN, OBJ_SLOTHOST, STR_SLOT) SignalSlot::Disconnect(SIGNHOST, String(#STR_SIGN), SLOTHOST, String(#STR_SLOT));
#endif
#if !defined(DECLARE_SIGNAL)
#define DECLARE_SIGNAL(T_ARG, T_SIGNHOST, SIGN)\
        void SIGN(T_ARG ARG){SignalSlot::Emit(static_cast<Object*>(this), String(#SIGN), SharedPointer<SignalSlotArgument>(static_cast<SignalSlotArgument*>(new SignalSlotArgumentImplementation<T_ARG>(ARG))));}
#endif
#if !defined(EMIT_SIGNAL)
#define EMIT_SIGNAL(SIGN, ARG) SIGN(ARG)
#endif
#if !defined(signal) && !defined(slot) && !defined(ConnectSignalSlot) && !defined(DisconnectSignalSlot) && !defined(EmitSignal)
#define signal SIGNAL
#define slot SLOT
#define ConnectSignalSlot CONNECT_SIGNALSLOT
#define DisconnectSignalSlot DISCONNECT_SIGNALSLOT
#define EmitSignal EMIT_SIGNAL
#endif
#endif

#endif
