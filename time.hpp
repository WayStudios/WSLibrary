/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef TIME_HEADER
#define	TIME_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXPORT Time {
    explicit Time(ws_timeval V = 0);
    Time(const Time&);
    ~Time();

    ws_timeval Hour() const;
    ws_timeval Minute() const;
    ws_timeval Second() const;
    ws_timeval MilliSecond() const;

    static Time Now();

    Time& operator=(const Time&);

    boolean operator==(const Time&) const;
    boolean operator!=(const Time&) const;

    Time& operator+=(const Time&);
    Time& operator-=(const Time&);

    Time operator+(const Time&) const;
    Time operator-(const Time&) const;

    ws_timeval Value;
};

END_WS_NAMESPACE

END_HEADER

#endif
