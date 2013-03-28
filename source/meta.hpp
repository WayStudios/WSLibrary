/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef META_HEADER
#define	META_HEADER

#include <global.hpp>
#include <metapool.hpp>
#include <string.hpp>
#include <map.hpp>
#include <list.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class Object;
class Thread;
class Signal;
class Slot;

struct EXTERN Meta {
    explicit Meta(Object*);
    ~Meta();

    static MetaPool Pool;

    Object* handle;
    Object* master;
	Thread* thread;
	List<Object*> children;
    String identity;
    Map<String, Signal*> signalMap;
    Map<String, Slot*> slotMap;

    UNCOPYABLE(Meta)
};

END_WS_NAMESPACE

END_HEADER

#endif
