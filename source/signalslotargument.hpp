/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef SIGNALSLOTARGUMENT_HEADER
#define SIGNALSLOTARGUMENT_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT SignalSlotArgument {
public:
    SignalSlotArgument();
    virtual ~SignalSlotArgument() = 0;
};

END_WS_NAMESPACE

END_HEADER

#include <signalslotargumentimpl.hpp>

#endif
