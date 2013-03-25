/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <metapool.hpp>
#include <metapoolimpl.hpp>
#include <scopedlock.hpp>
#include <meta.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

MetaPoolNode::MetaPoolNode(Meta* P_M, MetaPoolNode* P_PREV, MetaPoolNode* P_NEXT) : OBJMeta(P_M), Priority(0), Prev(P_PREV), Next(P_NEXT) {
}

MetaPoolNode::MetaPoolNode(const MetaPoolNode& REF) : OBJMeta(REF.OBJMeta), Priority(REF.Priority), Prev(REF.Prev), Next(REF.Next) {
}

MetaPoolNode::~MetaPoolNode() {
}

MetaPoolNode& MetaPoolNode::operator =(const MetaPoolNode& REF) {
    OBJMeta = REF.OBJMeta;
    Priority = REF.Priority;
    Prev = REF.Prev;
    Next = REF.Next;
    return *this;
}

MetaPool::MetaPoolImplementation::MetaPoolImplementation() : ListB(0) {
}

MetaPool::MetaPoolImplementation::~MetaPoolImplementation() {
}

void MetaPool::MetaPoolImplementation::Append(Meta* P_M) {
    if (P_M) {
        ScopedLock<Mutex> SL_Mutex(&MLock);
        MetaPoolNode* P_N = Allocate(1);
        new(P_N) MetaPoolNode(P_M, 0, ListB);
        if (ListB)
            ListB->Prev = P_N;
        ListB = P_N;
    }
}

void MetaPool::MetaPoolImplementation::Remove(Meta* P_M) {
    if (P_M) {
        ScopedLock<Mutex> SL_Mutex(&MLock);
        for (MetaPoolNode* P_ITER = ListB; P_ITER != 0; P_ITER = P_ITER->Next)
            if (P_ITER->OBJMeta == P_M) {
                if (P_ITER == ListB)
                    ListB = ListB->Next;
                if (P_ITER->Prev)
                    P_ITER->Prev->Next = P_ITER->Next;
                if (P_ITER->Next)
                    P_ITER->Next->Prev = P_ITER->Prev;
                Destruct(P_ITER);
                Deallocate(P_ITER);
                return;
            }
    }
}

void MetaPool::MetaPoolImplementation::Clear() {
    if (ListB) {
        ScopedLock<Mutex> SL_Mutex(&MLock);
        while (ListB) {
            MetaPoolNode* P_N = ListB->Next;
            Destruct(ListB);
            Deallocate(ListB);
            ListB = P_N;
        }
        ListB = 0;
    }
}

Meta* MetaPool::MetaPoolImplementation::Find(Object* P_OBJ) {
    if (ListB && P_OBJ) {
        ScopedLock<Mutex> SL_Mutex(&MLock);
        for (MetaPoolNode* P_ITER = ListB; P_ITER != 0; P_ITER = P_ITER->Next)
            if (P_ITER->OBJMeta)
                if (P_ITER->OBJMeta->Handle == P_OBJ) {
                    Meta* P_M = P_ITER->OBJMeta;
                    ++P_ITER->Priority;
                    if (P_ITER != ListB)
                        --ListB->Priority;
                    if (P_ITER->Prev)
                        --P_ITER->Prev->Priority;
                    if (P_ITER->Priority > ListB->Priority) {
                        Meta* TMP = ListB->OBJMeta;
                        ListB->OBJMeta = P_ITER->OBJMeta;
                        P_ITER->OBJMeta = TMP;
                    } else
                        if (P_ITER->Prev)
                        if (P_ITER->Priority > P_ITER->Prev->Priority) {
                            Meta* TMP = P_ITER->Prev->OBJMeta;
                            P_ITER->Prev->OBJMeta = P_ITER->OBJMeta;
                            P_ITER->OBJMeta = TMP;
                        }
                    return P_M;
                }
    }
    return 0;
}

MetaPool::MetaPool() : Implementation(0) {
    Implementation = new MetaPoolImplementation;
}

MetaPool::~MetaPool() {
    if (Implementation) {
        Implementation->Clear();
        delete Implementation;
    }
}

void MetaPool::Append(Meta* P_M) {
    if (Implementation && P_M)
        Implementation->Append(P_M);
}

void MetaPool::Remove(Meta* P_M) {
    if (Implementation && P_M)
        Implementation->Remove(P_M);
}

Meta* MetaPool::Find(Object* P_OBJ) {
    if (Implementation && P_OBJ)
        return Implementation->Find(P_OBJ);
    return 0;
}

END_SOURCECODE
