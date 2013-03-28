/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SIGNALSLOT_IMPLEMENTATION_HEADER
#define	SIGNALSLOT_IMPLEMENTATION_HEADER

#include <signalslot.hpp>
#include <signalimpl.hpp>
#include <slotimpl.hpp>
//#include <meta.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

template <typename T_ARG, typename T_SIGNHOST, typename T_SIGN, typename T_SLOTHOST, typename T_SLOT>
BOOLEAN SignalSlot::connect(T_SIGNHOST* P_SIGNHOST, const String& STR_SIGN, T_SIGN I_SIGN, T_SLOTHOST* P_SLOTHOST, const String& STR_SLOT, T_SLOT I_SLOT) {
    if (P_SIGNHOST && P_SLOTHOST)
        return connect(prepareSignal<T_ARG, T_SIGNHOST, T_SIGN > (P_SIGNHOST, STR_SIGN, I_SIGN), prepareSlot<T_ARG, T_SLOTHOST, T_SLOT > (P_SLOTHOST, STR_SLOT, I_SLOT));
    return false;
}

template <typename T_ARG, typename T_SIGNHOST, typename T_SIGN>
Signal* SignalSlot::prepareSignal(T_SIGNHOST* P_SIGNHOST, const String& STR_SIGN, T_SIGN I_SIGN) {
    if (P_SIGNHOST) {
        Signal* P_SIGN = FetchSignal(static_cast<Object*> (P_SIGNHOST), STR_SIGN);
        if (P_SIGN)
            return P_SIGN;
        P_SIGN = static_cast<Signal*> (new SignalImplementation<T_SIGNHOST, T_SIGN, T_ARG > (I_SIGN, STR_SIGN, P_SIGNHOST));
        if (P_SIGN) {
            OpenSignal(static_cast<Object*> (P_SIGNHOST), P_SIGN);
            return P_SIGN;
        }
    }
    return 0;
}

template <typename T_ARG, typename T_SLOTHOST, typename T_SLOT>
Slot* SignalSlot::prepareSlot(T_SLOTHOST* P_SLOTHOST, const String& STR_SLOT, T_SLOT I_SLOT) {
    if (P_SLOTHOST) {
        Slot* P_SLOT = FetchSlot(static_cast<Object*> (P_SLOTHOST), STR_SLOT);
        if (P_SLOT)
            return P_SLOT;
        P_SLOT = static_cast<Slot*> (new SlotImplementation<T_SLOTHOST, T_SLOT, T_ARG > (I_SLOT, STR_SLOT, P_SLOTHOST));
        if (P_SLOT) {
            OpenSlot(static_cast<Object*> (P_SLOTHOST), P_SLOT);
            return P_SLOT;
        }
    }
    return 0;
}

END_WS_NAMESPACE

END_HEADER

#endif
