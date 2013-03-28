/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef METAPOOL_HEADER
#define	METAPOOL_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct Meta;
class Object;

class EXPORT MetaPool {
    DECLARE_IMPLEMENTATION(MetaPool)
    UNCOPYABLE(MetaPool)
public:
    typedef Meta* TYPE;

    MetaPool();
    ~MetaPool();

    void append(Meta*);
    void remove(Meta*);
    Meta* find(Object*);
};

END_WS_NAMESPACE

END_HEADER

#endif
