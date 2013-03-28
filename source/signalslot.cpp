/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <signalslot.hpp>
#include <string.hpp>
#include <signal.hpp>
#include <slot.hpp>
#include <meta.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

BOOLEAN SignalSlot::connect(Object* OBJ_SIGN, const String& STR_SIGN, Object* OBJ_SLOT, const String& STR_SLOT) {
    if (OBJ_SIGN && !STR_SIGN.empty() && OBJ_SLOT && !STR_SLOT.empty())
        return connect(fetchSignal(OBJ_SIGN, STR_SIGN), fetchSlot(OBJ_SLOT, STR_SLOT));
    return false;
}

BOOLEAN SignalSlot::disconnect(Object* OBJ_SIGN, const String& STR_SIGN, Object* OBJ_SLOT, const String& STR_SLOT) {
    if (OBJ_SIGN && !STR_SIGN.empty() && OBJ_SLOT && !STR_SLOT.empty())
        return disconnect(fetchSignal(OBJ_SIGN, STR_SIGN), fetchSlot(OBJ_SLOT, STR_SLOT));
    return false;
}

BOOLEAN SignalSlot::connect(Signal* P_SIGN, Slot* P_SLOT) {
    if (P_SIGN && P_SLOT)
        if (!P_SIGN->connections().exist(P_SLOT) && !P_SLOT->connections().exist(P_SIGN)) {
            P_SIGN->connections().append(P_SLOT);
            P_SLOT->connections().append(P_SIGN);
            return true;
        }
    return false;
}

BOOLEAN SignalSlot::disconnect(Signal* P_SIGN, Slot* P_SLOT) {
    if (P_SIGN && P_SLOT)
        if (P_SIGN->connections().exist(P_SLOT) && P_SLOT->connections().exist(P_SIGN)) {
            P_SIGN->connections().remove(P_SLOT);
            P_SLOT->connections().remove(P_SIGN);
            return true;
        }
    return false;
}

Signal* SignalSlot::fetchSignal(Object* OBJ, const String& STR_SIGN) {
    if (OBJ && !STR_SIGN.empty()) {
        Meta* P_META = Meta::Pool.find(OBJ);
        if (P_META) {
            Map<String, Signal*>::Iterator ITER_SIGN = P_META->signalMap.find(STR_SIGN);
            if (ITER_SIGN != P_META->signalMap.end())
                return (*ITER_SIGN).second;
        }
    }
    return 0;
}

Slot* SignalSlot::fetchSlot(Object* OBJ, const String& STR_SLOT) {
    if (OBJ && !STR_SLOT.empty()) {
        Meta* P_META = Meta::Pool.find(OBJ);
        if (P_META) {
            Map<String, Slot*>::Iterator ITER_SLOT = P_META->slotMap.find(STR_SLOT);
            if (ITER_SLOT != P_META->slotMap.end())
                return (*ITER_SLOT).second;
        }
    }
    return 0;
}

void SignalSlot::emit(Object* OBJ, const String& STR_SIGN, const SharedPointer<SignalSlotArgument>& SP_ARG) {
    if (OBJ && !STR_SIGN.empty() && SP_ARG) {
        Signal* P_SIGN = fetchSignal(OBJ, STR_SIGN);
        if (P_SIGN)
            P_SIGN->emit(SP_ARG);
    }
}

void SignalSlot::call(Object* OBJ, const String& STR_SLOT, const SharedPointer<SignalSlotArgument>& SP_ARG) {
    if (OBJ && !STR_SLOT.empty() && SP_ARG) {
        Slot* P_SLOT = fetchSlot(OBJ, STR_SLOT);
        if (P_SLOT)
            P_SLOT->call(SP_ARG);
    }
}

void SignalSlot::openSignal(Object* OBJ, Signal* P_SIGN) {
    if (OBJ && P_SIGN) {
        Meta* P_META = Meta::Pool.find(OBJ);
        if (P_META)
            P_META->signalMap.append(P_SIGN->identity(), P_SIGN);
    }
}

void SignalSlot::openSlot(Object* OBJ, Slot* P_SLOT) {
    if (OBJ && P_SLOT) {
        Meta* P_META = Meta::Pool.find(OBJ);
        if (P_META)
            P_META->slotMap.append(P_SLOT->identity(), P_SLOT);
    }
}

void SignalSlot::closeSignal(Object* OBJ, const String& STR_SIGN) {
    closeSignal(fetchSignal(OBJ, STR_SIGN));
}

void SignalSlot::closeSlot(Object* OBJ, const String& STR_SLOT) {
    closeSlot(fetchSlot(OBJ, STR_SLOT));
}

void SignalSlot::close(Object* OBJ) {
    if (OBJ) {
        Meta* P_META = Meta::Pool.find(OBJ);
        if (P_META) {
            for (Map<String, Signal*>::Iterator ITER = P_META->signalMap.begin(); ITER != P_META->signalMap.end(); ++ITER)
                closeSignal((*ITER).second);
            for (Map<String, Slot*>::Iterator ITER = P_META->slotMap.begin(); ITER != P_META->slotMap.end(); ++ITER)
                closeSlot((*ITER).second);
        }
    }
}

void SignalSlot::closeSignal(Signal* P_SIGN) {
    if (P_SIGN)
        for (Vector<Slot*>::Iterator ITER = P_SIGN->connections().begin(); ITER != P_SIGN->connections().end(); ++ITER)
            (*ITER)->connections().remove(P_SIGN);
}

void SignalSlot::closeSlot(Slot* P_SLOT) {
    if (P_SLOT)
        for (Vector<Signal*>::Iterator ITER = P_SLOT->connections().begin(); ITER != P_SLOT->connections().end(); ++ITER)
            (*ITER)->connections().remove(P_SLOT);
}

END_SOURCECODE
