/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef TIME_HEADER
#define	TIME_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXPORT Time {
    explicit Time(TIMEVAL V = 0);
    Time(const Time&);
    ~Time();

    TIMEVAL hours() const;
    TIMEVAL minutes() const;
    TIMEVAL seconds() const;
    TIMEVAL milliseconds() const;

    static Time now();

    Time& operator =(const Time&);

    BOOLEAN operator ==(const Time&) const;
    BOOLEAN operator !=(const Time&) const;

    Time& operator +=(const Time&);
    Time& operator -=(const Time&);

    Time operator +(const Time&) const;
    Time operator -(const Time&) const;

    TIMEVAL value;
};

END_WS_NAMESPACE

END_HEADER

#endif
