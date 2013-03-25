/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef METAPOOLIMPLEMENTATION_HEADER
#define	METAPOOLIMPLEMENTATION_HEADER

#include <metapool.hpp>
#include <allocator.hpp>
#include <mutex.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct LOCAL MetaPoolNode {
    MetaPoolNode(Meta*, MetaPoolNode*, MetaPoolNode*);
    MetaPoolNode(const MetaPoolNode&);
    ~MetaPoolNode();

    MetaPoolNode& operator=(const MetaPoolNode&);

    Meta* OBJMeta;
    ubyte Priority;
    MetaPoolNode* Prev;
    MetaPoolNode* Next;
};

class LOCAL MetaPool::MetaPoolImplementation : public Allocator<MetaPoolNode> {
    UNCOPYABLE(MetaPoolImplementation)
public:
    MetaPoolImplementation();
    ~MetaPoolImplementation();

    void Append(Meta*);
    void Remove(Meta*);
    void Clear();

    Meta* Find(Object*);

    Mutex MLock;
    MetaPoolNode* ListB;
};

END_WS_NAMESPACE

END_HEADER

#endif
