/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <signalslot.hpp>
#include <string.hpp>
#include <signal.hpp>
#include <slot.hpp>
#include <meta.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

boolean SignalSlot::Connect(Object* OBJ_SIGN, const String& STR_SIGN, Object* OBJ_SLOT, const String& STR_SLOT) {
    if (OBJ_SIGN && !STR_SIGN.Empty() && OBJ_SLOT && !STR_SLOT.Empty())
        return Connect(FetchSignal(OBJ_SIGN, STR_SIGN), FetchSlot(OBJ_SLOT, STR_SLOT));
    return false;
}

boolean SignalSlot::Disconnect(Object* OBJ_SIGN, const String& STR_SIGN, Object* OBJ_SLOT, const String& STR_SLOT) {
    if (OBJ_SIGN && !STR_SIGN.Empty() && OBJ_SLOT && !STR_SLOT.Empty())
        return Disconnect(FetchSignal(OBJ_SIGN, STR_SIGN), FetchSlot(OBJ_SLOT, STR_SLOT));
    return false;
}

boolean SignalSlot::Connect(Signal* P_SIGN, Slot* P_SLOT) {
    if (P_SIGN && P_SLOT)
        if (!P_SIGN->Connections().Exist(P_SLOT) && !P_SLOT->Connections().Exist(P_SIGN)) {
            P_SIGN->Connections().Append(P_SLOT);
            P_SLOT->Connections().Append(P_SIGN);
            return true;
        }
    return false;
}

boolean SignalSlot::Disconnect(Signal* P_SIGN, Slot* P_SLOT) {
    if (P_SIGN && P_SLOT)
        if (P_SIGN->Connections().Exist(P_SLOT) && P_SLOT->Connections().Exist(P_SIGN)) {
            P_SIGN->Connections().Remove(P_SLOT);
            P_SLOT->Connections().Remove(P_SIGN);
            return true;
        }
    return false;
}

Signal* SignalSlot::FetchSignal(Object* OBJ, const String& STR_SIGN) {
    if (OBJ && !STR_SIGN.Empty()) {
        Meta* P_META = Meta::Pool.Find(OBJ);
        if (P_META) {
            Map<String, Signal*>::Iterator ITER_SIGN = P_META->SignalMap.Find(STR_SIGN);
            if (ITER_SIGN != P_META->SignalMap.End())
                return (*ITER_SIGN).Second;
        }
    }
    return 0;
}

Slot* SignalSlot::FetchSlot(Object* OBJ, const String& STR_SLOT) {
    if (OBJ && !STR_SLOT.Empty()) {
        Meta* P_META = Meta::Pool.Find(OBJ);
        if (P_META) {
            Map<String, Slot*>::Iterator ITER_SLOT = P_META->SlotMap.Find(STR_SLOT);
            if (ITER_SLOT != P_META->SlotMap.End())
                return (*ITER_SLOT).Second;
        }
    }
    return 0;
}

void SignalSlot::Emit(Object* OBJ, const String& STR_SIGN, const SharedPointer<SignalSlotArgument>& SP_ARG) {
    if (OBJ && !STR_SIGN.Empty() && SP_ARG) {
        Signal* P_SIGN = FetchSignal(OBJ, STR_SIGN);
        if (P_SIGN)
            P_SIGN->Emit(SP_ARG);
    }
}

void SignalSlot::Call(Object* OBJ, const String& STR_SLOT, const SharedPointer<SignalSlotArgument>& SP_ARG) {
    if (OBJ && !STR_SLOT.Empty() && SP_ARG) {
        Slot* P_SLOT = FetchSlot(OBJ, STR_SLOT);
        if (P_SLOT)
            P_SLOT->Call(SP_ARG);
    }
}

void SignalSlot::OpenSignal(Object* OBJ, Signal* P_SIGN) {
    if (OBJ && P_SIGN) {
        Meta* P_META = Meta::Pool.Find(OBJ);
        if (P_META)
            P_META->SignalMap.Append(P_SIGN->Name(), P_SIGN);
    }
}

void SignalSlot::OpenSlot(Object* OBJ, Slot* P_SLOT) {
    if (OBJ && P_SLOT) {
        Meta* P_META = Meta::Pool.Find(OBJ);
        if (P_META)
            P_META->SlotMap.Append(P_SLOT->Name(), P_SLOT);
    }
}

void SignalSlot::CloseSignal(Object* OBJ, const String& STR_SIGN) {
    CloseSignal(FetchSignal(OBJ, STR_SIGN));
}

void SignalSlot::CloseSlot(Object* OBJ, const String& STR_SLOT) {
    CloseSlot(FetchSlot(OBJ, STR_SLOT));
}

void SignalSlot::Close(Object* OBJ) {
    if (OBJ) {
        Meta* P_META = Meta::Pool.Find(OBJ);
        if (P_META) {
            for (Map<String, Signal*>::Iterator ITER = P_META->SignalMap.Begin(); ITER != P_META->SignalMap.End(); ++ITER)
                CloseSignal((*ITER).Second);
            for (Map<String, Slot*>::Iterator ITER = P_META->SlotMap.Begin(); ITER != P_META->SlotMap.End(); ++ITER)
                CloseSlot((*ITER).Second);
        }
    }
}

void SignalSlot::CloseSignal(Signal* P_SIGN) {
    if (P_SIGN)
        for (Vector<Slot*>::Iterator ITER = P_SIGN->Connections().Begin(); ITER != P_SIGN->Connections().End(); ++ITER)
            (*ITER)->Connections().Remove(P_SIGN);
}

void SignalSlot::CloseSlot(Slot* P_SLOT) {
    if (P_SLOT)
        for (Vector<Signal*>::Iterator ITER = P_SLOT->Connections().Begin(); ITER != P_SLOT->Connections().End(); ++ITER)
            (*ITER)->Connections().Remove(P_SLOT);
}

END_SOURCECODE
