/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SLOTIMPLEMENTATION_HEADER
#define	SLOTIMPLEMENTATION_HEADER

#include <slot.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T_OBJ, typename T_SLOT, typename T_ARG>
class LOCAL SlotImplementation : public Slot {
    UNCOPYABLE(SlotImplementation)

    T_SLOT Function;
public:
    explicit SlotImplementation(const T_SLOT&, const String&, T_OBJ*);
    ~SlotImplementation();

    void Call(const SharedPointer<SignalSlotArgument>&);
};

template <typename T_OBJ, typename T_SLOT, typename T_ARG>
SlotImplementation<T_OBJ, T_SLOT, T_ARG>::SlotImplementation(const T_SLOT& REF_SLOT, const String& REF_STR, T_OBJ* P_OBJ) : Slot(REF_STR, static_cast<Object*> (P_OBJ)), Function(REF_SLOT) {
}

template <typename T_OBJ, typename T_SLOT, typename T_ARG>
SlotImplementation<T_OBJ, T_SLOT, T_ARG>::~SlotImplementation() {
}

template <typename T_OBJ, typename T_SLOT, typename T_ARG>
void SlotImplementation<T_OBJ, T_SLOT, T_ARG>::Call(const SharedPointer<SignalSlotArgument>& SP_ARG) {
    if (Host() && SP_ARG)
        (static_cast<T_OBJ*> (Host())->*Function)((static_cast<SignalSlotArgumentImplementation<T_ARG>*> (SP_ARG.Address()))->Value);
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
