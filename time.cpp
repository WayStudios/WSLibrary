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

Time Time::Now() {
    ws_timeval V = 0;
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

Time::Time(ws_timeval V) : Value(V) {
}

Time::Time(const Time& REF) : Value(REF.Value) {
}

Time::~Time() {
}

ws_timeval Time::Hour() const {
    return Value / 3600000;
}

ws_timeval Time::Minute() const {
    return Value / 60000;
}

ws_timeval Time::Second() const {
    return Value / 1000;
}

ws_timeval Time::MilliSecond() const {
    return Value;
}

Time& Time::operator =(const Time& REF) {
    Value = REF.Value;
    return *this;
}

boolean Time::operator ==(const Time& REF) const {
    return Value == REF.Value;
}

boolean Time::operator !=(const Time& REF) const {
    return Value != REF.Value;
}

Time& Time::operator +=(const Time& REF) {
    Value += REF.Value;
    return *this;
}

Time& Time::operator -=(const Time& REF) {
    Value -= REF.Value;
    return *this;
}

Time Time::operator +(const Time& REF) const {
    return Time(Value + REF.Value);
}

Time Time::operator -(const Time& REF) const {
    return Time(Value - REF.Value);
}

END_WS_NAMESPACE

END_SOURCECODE
