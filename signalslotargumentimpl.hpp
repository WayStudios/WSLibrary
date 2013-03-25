/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SIGNALSLOTARGUMENTIMPLEMENTATION_HEADER
#define	SIGNALSLOTARGUMENTIMPLEMENTATION_HEADER

#include <signalslotargument.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T_ARG>
class LOCAL SignalSlotArgumentImplementation : public SignalSlotArgument {
public:
    SignalSlotArgumentImplementation(const T_ARG&);
    ~SignalSlotArgumentImplementation();

    T_ARG Value;
};

template <typename T_ARG>
SignalSlotArgumentImplementation<T_ARG>::SignalSlotArgumentImplementation(const T_ARG& REF_ARG) : SignalSlotArgument(), Value(REF_ARG) {
}

template <typename T_ARG>
SignalSlotArgumentImplementation<T_ARG>::~SignalSlotArgumentImplementation() {
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
