/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef META_HEADER
#define	META_HEADER

#include <global.hpp>
#include <metapool.hpp>
#include <string.hpp>
#include <map.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class Object;
class Signal;
class Slot;

struct EXTERN Meta {
    explicit Meta(const String&, Object*);
    ~Meta();

    static MetaPool Pool;

    Object* Handle;
    Object* Master;
    String Name;
    Map<String, Signal*> SignalMap;
    Map<String, Slot*> SlotMap;

    UNCOPYABLE(Meta)
};

END_WS_NAMESPACE

END_HEADER

#endif
