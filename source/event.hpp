/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef EVENT_HEADER
#define	EVENT_HEADER

#include <global.hpp>

BEGIN_HEADER

#ifndef WS_EVENT
#define WS_EVENT 0x10
#endif

BEGIN_WS_NAMESPACE

struct EXPORT Event {
    explicit Event(TYPEID);
    virtual ~Event() = 0;

    const TYPEID type;

    UNCOPYABLE(Event)
};

END_WS_NAMESPACE

END_HEADER

#endif
