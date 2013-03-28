/*******************************************************************************
 * Way Studios Library
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
    static BOOLEAN connect(T_SIGNHOST* P_SIGNHOST, const String& STR_SIGN, T_SIGN I_SIGN, T_SLOTHOST* P_SLOTHOST, const String& STR_SLOT, T_SLOT I_SLOT);

    template <typename T_ARG, typename T_SIGNHOST, typename T_SIGN>
    static Signal* prepareSignal(T_SIGNHOST* P_SIGNHOST, const String& STR_SIGN, T_SIGN I_SIGN);

    template <typename T_ARG, typename T_SLOTHOST, typename T_SLOT>
    static Slot* prepareSlot(T_SLOTHOST* P_SLOTHOST, const String& STR_SLOT, T_SLOT I_SLOT);

    END_TEMPLATE

    static BOOLEAN connect(Object*, const String&, Object*, const String&);
    static BOOLEAN disconnect(Object*, const String&, Object*, const String&);

    static BOOLEAN connect(Signal*, Slot*);
    static BOOLEAN disconnect(Signal*, Slot*);

    static Signal* fetchSignal(Object*, const String&);
    static Slot* fetchSlot(Object*, const String&);

    static void emit(Object*, const String&, const SharedPointer<SignalSlotArgument>&);
    static void call(Object*, const String&, const SharedPointer<SignalSlotArgument>&);

    static void openSignal(Object*, Signal*);
    static void openSlot(Object*, Slot*);

    static void closeSignal(Object*, const String&);
    static void closeSlot(Object*, const String&);

    static void close(Object*);

    static void closeSignal(Signal*);
    static void closeSlot(Slot*);
};

END_WS_NAMESPACE

END_HEADER

#include <signalslot_impl.hpp>

#endif
