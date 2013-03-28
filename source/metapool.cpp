/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <metapool.hpp>
#include <metapoolimpl.hpp>
#include <scopedlock.hpp>
#include <meta.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

MetaPoolNode::MetaPoolNode(Meta* P_M, MetaPoolNode* P_PREV, MetaPoolNode* P_NEXT) : meta(P_M), priority(0), prev(P_PREV), next(P_NEXT) {
}

MetaPoolNode::MetaPoolNode(const MetaPoolNode& REF) : meta(REF.meta), priority(REF.priority), prev(REF.prev), next(REF.next) {
}

MetaPoolNode::~MetaPoolNode() {
}

MetaPoolNode& MetaPoolNode::operator =(const MetaPoolNode& REF) {
	meta = REF.meta;
    priority = REF.priority;
    prev = REF.prev;
    next = REF.next;
    return *this;
}

//the pointer node is the first node of all nodes
MetaPool::MetaPoolImplementation::MetaPoolImplementation() : node(0) {
}

MetaPool::MetaPoolImplementation::~MetaPoolImplementation() {
}

void MetaPool::MetaPoolImplementation::append(Meta* P_M) {
    if (P_M) {
        ScopedLock<Mutex> SL_MUTEX(&mutex);
        MetaPoolNode* P_N = allocate(1);
        new(P_N) MetaPoolNode(P_M, 0, node);
        if (node)
            node->prev = P_N;
        node = P_N;
    }
}

void MetaPool::MetaPoolImplementation::remove(Meta* P_M) {
    if (P_M) {
        ScopedLock<Mutex> SL_MUTEX(&mutex);
        for (MetaPoolNode* P_ITER = node; P_ITER != 0; P_ITER = P_ITER->next)
            if (P_ITER->meta == P_M) {
                if (P_ITER == node)
                    node = node->next;
                if (P_ITER->prev)
                    P_ITER->prev->next = P_ITER->next;
                if (P_ITER->next)
                    P_ITER->next->prev = P_ITER->prev;
                destruct(P_ITER);
                deallocate(P_ITER);
                return;
            }
    }
}

void MetaPool::MetaPoolImplementation::clear() {
    if (node) {
        ScopedLock<Mutex> SL_MUTEX(&mutex);
        while (node) {
            MetaPoolNode* P_N = node->next;
            destruct(node);
            deallocate(node);
            node = P_N;
        }
        node = 0;
    }
}

Meta* MetaPool::MetaPoolImplementation::find(Object* P_OBJ) {
    if (node && P_OBJ) {
        ScopedLock<Mutex> SL_MUTEX(&mutex);
        for (MetaPoolNode* P_ITER = node; P_ITER != 0; P_ITER = P_ITER->next)
            if (P_ITER->meta)
                if (P_ITER->meta->handle == P_OBJ) {
                    Meta* P_M = P_ITER->meta;
                    ++P_ITER->priority;
                    if (P_ITER != node)
                        --node->priority;
                    if (P_ITER->prev)
                        --P_ITER->prev->priority;
                    if (P_ITER->priority > node->priority) {
                        Meta* TMP = node->meta;
                        node->meta = P_ITER->meta;
                        P_ITER->meta = TMP;
                    } else
                        if (P_ITER->prev)
                        if (P_ITER->priority > P_ITER->prev->priority) {
                            Meta* TMP = P_ITER->prev->meta;
                            P_ITER->prev->meta = P_ITER->meta;
                            P_ITER->meta = TMP;
                        }
                    return P_M;
                }
    }
    return 0;
}

MetaPool::MetaPool() : implementation(0) {
    implementation = new MetaPoolImplementation;
}

MetaPool::~MetaPool() {
    if (implementation) {
        implementation->clear();
        delete implementation;
    }
}

void MetaPool::append(Meta* P_M) {
    if (implementation && P_M)
        implementation->append(P_M);
}

void MetaPool::remove(Meta* P_M) {
    if (implementation && P_M)
        implementation->remove(P_M);
}

Meta* MetaPool::find(Object* P_OBJ) {
    if (implementation && P_OBJ)
        return implementation->find(P_OBJ);
    return 0;
}

END_SOURCECODE
