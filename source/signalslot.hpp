/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SIGNALSLOT_HEADER
#define	SIGNALSLOT_HEADER

#include <global.hpp>
#include <string.hpp>
#include <signalslotargument.hpp>
#include <sharedpointer.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class Object;
class Signal;
class Slot;

class EXPORT SignalSlot {
    UNCOPYABLE(SignalSlot)
public:
    BEGIN_TEMPLATE

    template <typename T_ARG, typename T_SIGNHOST, typename T_SIGN, typename T_SLOTHOST, typename T_SLOT>
    static boolean Connect(T_SIGNHOST* P_SIGNHOST, const String& STR_SIGN, T_SIGN I_SIGN, T_SLOTHOST* P_SLOTHOST, const String& STR_SLOT, T_SLOT I_SLOT);

    template <typename T_ARG, typename T_SIGNHOST, typename T_SIGN>
    static Signal* PrepareSignal(T_SIGNHOST* P_SIGNHOST, const String& STR_SIGN, T_SIGN I_SIGN);

    template <typename T_ARG, typename T_SLOTHOST, typename T_SLOT>
    static Slot* PrepareSlot(T_SLOTHOST* P_SLOTHOST, const String& STR_SLOT, T_SLOT I_SLOT);

    END_TEMPLATE

    static boolean Connect(Object*, const String&, Object*, const String&);
    static boolean Disconnect(Object*, const String&, Object*, const String&);

    static boolean Connect(Signal*, Slot*);
    static boolean Disconnect(Signal*, Slot*);

    static Signal* FetchSignal(Object*, const String&);
    static Slot* FetchSlot(Object*, const String&);

    static void Emit(Object*, const String&, const SharedPointer<SignalSlotArgument>&);
    static void Call(Object*, const String&, const SharedPointer<SignalSlotArgument>&);

    static void OpenSignal(Object*, Signal*);
    static void OpenSlot(Object*, Slot*);

    static void CloseSignal(Object*, const String&);
    static void CloseSlot(Object*, const String&);

    static void Close(Object*);

    static void CloseSignal(Signal*);
    static void CloseSlot(Slot*);
};

END_WS_NAMESPACE

END_HEADER

#include <signalslot_impl.hpp>

#endif
