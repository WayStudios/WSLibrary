/*******************************************************************************
 * WayStudio Library
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
    typedef Meta* VALUE;

    MetaPool();
    ~MetaPool();

    void Append(Meta*);
    void Remove(Meta*);
    Meta* Find(Object*);
};

END_WS_NAMESPACE

END_HEADER

#endif
