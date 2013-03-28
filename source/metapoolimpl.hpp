/*******************************************************************************
 * Way Studios Library
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

    MetaPoolNode& operator =(const MetaPoolNode&);

    Meta* meta;
    UBYTE priority;
    MetaPoolNode* prev;
    MetaPoolNode* next;
};

class LOCAL MetaPool::MetaPoolImplementation : public Allocator<MetaPoolNode> {
    UNCOPYABLE(MetaPoolImplementation)
public:
    MetaPoolImplementation();
    ~MetaPoolImplementation();

    void append(Meta*);
    void remove(Meta*);
    void clear();

    Meta* find(Object*);

    Mutex mutex;
    MetaPoolNode* node; //beginning of all nodes
};

END_WS_NAMESPACE

END_HEADER

#endif
