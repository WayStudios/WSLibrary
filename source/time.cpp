/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <time.hpp>
#if defined(API_POSIX)
#include <sys/time.h>
#include <sys/types.h>
#elif defined(API_MSWINDOWS)
#include <windows.h>
#endif

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

Time Time::now() {
    TIMEVAL V = 0;
#if defined(API_POSIX)
    timeval tm_v;
    gettimeofday(&tm_v, 0);
    time_t t = tm_v.tv_sec;
    tm* ptr_tm = localtime(&t);
    V = ptr_tm->tm_hour * 3600000 + ptr_tm->tm_min * 60000 + ptr_tm->tm_sec * 1000 + tm_v.tv_usec / 1000;
#elif defined(API_MSWINDOWS)
    SYSTEMTIME lt;
    GetLocalTime(&lt);
    V = lt.wHour * 3600000 + lt.wMinute * 60000 + lt.wSecond * 1000 + lt.wMilliseconds;
#endif
    return Time(V);
}

Time::Time(TIMEVAL V) : value(V) {
}

Time::Time(const Time& REF) : value(REF.value) {
}

Time::~Time() {
}

TIMEVAL Time::hours() const {
    return value / 3600000;
}

TIMEVAL Time::minutes() const {
    return value / 60000;
}

TIMEVAL Time::seconds() const {
    return value / 1000;
}

TIMEVAL Time::milliseconds() const {
    return value;
}

Time& Time::operator =(const Time& REF) {
    value = REF.value;
    return *this;
}

BOOLEAN Time::operator ==(const Time& REF) const {
    return value == REF.value;
}

BOOLEAN Time::operator !=(const Time& REF) const {
    return value != REF.value;
}

Time& Time::operator +=(const Time& REF) {
    value += REF.value;
    return *this;
}

Time& Time::operator -=(const Time& REF) {
    value -= REF.value;
    return *this;
}

Time Time::operator +(const Time& REF) const {
    return Time(value + REF.value);
}

Time Time::operator -(const Time& REF) const {
    return Time(value - REF.value);
}

END_WS_NAMESPACE

END_SOURCECODE
