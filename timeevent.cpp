/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <timeevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

TimeEvent::TimeEvent(ws_timeval V) : Event(WS_TIMEEVENT), Interval(V) {
}

TimeEvent::~TimeEvent() {
}

boolean TimeEvent::operator ==(const TimeEvent& REF) const {
    return Interval == REF.Interval;
}

boolean TimeEvent::operator !=(const TimeEvent& REF) const {
    return Interval != REF.Interval;
}

END_SOURCECODE
