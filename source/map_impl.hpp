/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef MAP_IMPLEMENTATION_HEADER
#define	MAP_IMPLEMENTATION_HEADER

#include <map.hpp>
#include <allocator.hpp>
#include <listnode.hpp>
#include <atomicinteger.hpp>
#include <mutex.hpp>
#include <scopedlock.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T_KEY, typename T_VALUE>
class LOCAL Map<T_KEY, T_VALUE>::MapImplementation : public Allocator< ListNode< Pair<T_KEY, T_VALUE> > > {
    UNCOPYABLE(MapImplementation)
public:
    MapImplementation();
    ~MapImplementation();

    size Total() const;
    boolean Empty() const;
    MapImplementation* Duplicate();
    void Clear();

    boolean Exist(const T_KEY&);

    void Append(const T_KEY&, const T_VALUE&);

    void Remove(ListNode< Pair<T_KEY, T_VALUE> >*);
    void Remove(const T_KEY&);

#if !defined(WITHOUT_THREAD)
    AtomicInteger Ref;
    Mutex MLock;
#endif
    ListNode< Pair<T_KEY, T_VALUE> >* LstB;
    ListNode< Pair<T_KEY, T_VALUE> >* LstE;
    ListNode< Pair<T_KEY, T_VALUE> >* CurBuf;
};

template <typename T_KEY, typename T_VALUE>
class EXPORT Map<T_KEY, T_VALUE>::Iterator {
    ListNode< Pair<T_KEY, T_VALUE> >* Current;
public:
    explicit Iterator(ListNode< Pair<T_KEY, T_VALUE> >*);
    Iterator(const Iterator&);
    ~Iterator();

    Iterator& operator=(const Iterator&);
    Iterator& operator++();
    Iterator& operator--();

    Pair<T_KEY, T_VALUE>& operator*();

    const Pair<T_KEY, T_VALUE>& operator*() const;

    boolean operator==(const Iterator&) const;
    boolean operator!=(const Iterator&) const;
};

template <typename T_KEY, typename T_VALUE>
Map<T_KEY, T_VALUE>::MapImplementation::MapImplementation() : LstB(0), LstE(0), CurBuf(0) {
}

template <typename T_KEY, typename T_VALUE>
Map<T_KEY, T_VALUE>::MapImplementation::~MapImplementation() {
}

template <typename T_KEY, typename T_VALUE>
size Map<T_KEY, T_VALUE>::MapImplementation::Total() const {
    size RET = 0;
    if (!Empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        for (ListNode< Pair<T_KEY, T_VALUE> >* P_ITER = LstB; P_ITER != 0; P_ITER = P_ITER->Next)
            ++RET;
    }
    return RET;
}

template <typename T_KEY, typename T_VALUE>
boolean Map<T_KEY, T_VALUE>::MapImplementation::Empty() const {
    return !LstB;
}

template <typename T_KEY, typename T_VALUE>
typename Map<T_KEY, T_VALUE>::MapImplementation* Map<T_KEY, T_VALUE>::MapImplementation::Duplicate() {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
    MapImplementation* N_IMPL = new MapImplementation;
    if (N_IMPL) {
        if (!Empty()) {
            for (ListNode< Pair<T_KEY, T_VALUE> >* P_ITER = LstB; P_ITER != 0; P_ITER = P_ITER->Next) {
                ListNode< Pair<T_KEY, T_VALUE> >* P_N = Allocator< ListNode< Pair<T_KEY, T_VALUE> > >::Allocate(1);
                new(P_N) ListNode< Pair<T_KEY, T_VALUE> >(P_ITER->Object, 0, 0);
                if (N_IMPL->Empty())
                    N_IMPL->LstE = N_IMPL->LstB = P_N;
                else {
                    P_N->Prev = N_IMPL->LstE;
                    N_IMPL->LstE->Next = P_N;
                    N_IMPL->LstE = P_N;
                }
            }
        }
        return N_IMPL;
    }
    return 0;
}

template <typename T_KEY, typename T_VALUE>
void Map<T_KEY, T_VALUE>::MapImplementation::Clear() {
    if (!Empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        while (!Empty()) {
            ListNode< Pair<T_KEY, T_VALUE> >* P_N = LstB->Next;
            Destruct(LstB);
            Deallocate(LstB);
            LstB = P_N;
            if (Empty())
                CurBuf = LstE = LstB = 0;
        }
    }
}

template <typename T_KEY, typename T_VALUE>
boolean Map<T_KEY, T_VALUE>::MapImplementation::Exist(const T_KEY& REF_KEY) {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
    for (ListNode< Pair<T_KEY, T_VALUE> >* P_ITER = LstB; P_ITER != 0; P_ITER = P_ITER->Next)
        if (P_ITER->Object.First == REF_KEY) {
            CurBuf = P_ITER;
            return true;
        }
    return false;
}

template <typename T_KEY, typename T_VALUE>
void Map<T_KEY, T_VALUE>::MapImplementation::Append(const T_KEY& REF_KEY, const T_VALUE& REF_VALUE) {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
    ListNode< Pair<T_KEY, T_VALUE> >* P_N = Allocator< ListNode< Pair<T_KEY, T_VALUE> > >::Allocate(1);
    new(P_N) ListNode< Pair<T_KEY, T_VALUE> >(Pair<T_KEY, T_VALUE > (REF_KEY, REF_VALUE), 0, 0);
    if (Empty())
        LstE = LstB = P_N;
    else {
        P_N->Prev = LstE;
        LstE->Next = P_N;
        LstE = P_N;
    }
}

template <typename T_KEY, typename T_VALUE>
void Map<T_KEY, T_VALUE>::MapImplementation::Remove(ListNode< Pair<T_KEY, T_VALUE> >* P_N) {
    if (!Empty() && P_N) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        if (P_N == LstB)
            LstB = LstB->Next;
        if (P_N == LstE)
            LstE = LstE->Prev;
        if (P_N->Prev)
            P_N->Prev->Next = P_N->Next;
        if (P_N->Next)
            P_N->Next->Prev = P_N->Prev;
        CurBuf = 0;
        Destruct(P_N);
        Deallocate(P_N);
    }
}

template <typename T_KEY, typename T_VALUE>
void Map<T_KEY, T_VALUE>::MapImplementation::Remove(const T_KEY& REF_KEY) {
    if (!Empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        for (ListNode< Pair<T_KEY, T_VALUE> >* P_ITER = LstB; P_ITER != 0; P_ITER = P_ITER->Next)
            if (P_ITER->Object.First == REF_KEY) {
                if (P_ITER == LstB)
                    LstB = LstB->Next;
                if (P_ITER == LstE)
                    LstE = LstE->Prev;
                if (P_ITER->Prev)
                    P_ITER->Prev->Next = P_ITER->Next;
                if (P_ITER->Next)
                    P_ITER->Next->Prev = P_ITER->Prev;
                CurBuf = 0;
                Destruct(P_ITER);
                Deallocate(P_ITER);
                return;
            }
    }
}

template <typename T_KEY, typename T_VALUE>
Map<T_KEY, T_VALUE>::Iterator::Iterator(ListNode<Pair<T_KEY, T_VALUE> >* P_ITER) : Current(P_ITER) {
}

template <typename T_KEY, typename T_VALUE>
Map<T_KEY, T_VALUE>::Iterator::Iterator(const Iterator& REF) : Current(REF.Current) {
}

template <typename T_KEY, typename T_VALUE>
Map<T_KEY, T_VALUE>::Iterator::~Iterator() {
}

template <typename T_KEY, typename T_VALUE>
        typename Map<T_KEY, T_VALUE>::Iterator& Map<T_KEY, T_VALUE>::Iterator::operator =(const Iterator& REF) {
    Current = REF.Current;
    return *this;
}

template <typename T_KEY, typename T_VALUE>
typename Map<T_KEY, T_VALUE>::Iterator& Map<T_KEY, T_VALUE>::Iterator::operator ++() {
    Current = Current->Next;
    return *this;
}

template <typename T_KEY, typename T_VALUE>
typename Map<T_KEY, T_VALUE>::Iterator& Map<T_KEY, T_VALUE>::Iterator::operator --() {
    Current = Current->Prev;
    return *this;
}

template <typename T_KEY, typename T_VALUE>
Pair<T_KEY, T_VALUE>& Map<T_KEY, T_VALUE>::Iterator::operator *() {
    return Current->Object;
}

template <typename T_KEY, typename T_VALUE>
const Pair<T_KEY, T_VALUE>& Map<T_KEY, T_VALUE>::Iterator::operator *() const {
    return Current->Object;
}

template <typename T_KEY, typename T_VALUE>
boolean Map<T_KEY, T_VALUE>::Iterator::operator ==(const Iterator& REF) const {
    return Current == REF.Current;
}

template <typename T_KEY, typename T_VALUE>
boolean Map<T_KEY, T_VALUE>::Iterator::operator !=(const Iterator& REF) const {
    return Current != REF.Current;
}

template <typename T_KEY, typename T_VALUE>
Map<T_KEY, T_VALUE>::Map() : Implementation(0) {
    Implementation = new MapImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

template <typename T_KEY, typename T_VALUE>
Map<T_KEY, T_VALUE>::Map(const Map<T_KEY, T_VALUE>& REF) : Implementation(REF.Implementation) {
    if (Implementation)
        ++(Implementation->Ref);
}

template <typename T_KEY, typename T_VALUE>
Map<T_KEY, T_VALUE>::~Map() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->Clear();
            delete Implementation;
        }
}

template <typename T_KEY, typename T_VALUE>
size Map<T_KEY, T_VALUE>::Total() const {
    if (Implementation)
        return Implementation->Total();
    return 0;
}

template <typename T_KEY, typename T_VALUE>
boolean Map<T_KEY, T_VALUE>::Empty() const {
    if (Implementation)
        return Implementation->Empty();
    return true;
}

template <typename T_KEY, typename T_VALUE>
void Map<T_KEY, T_VALUE>::Clear() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->Clear();
            delete Implementation;
        }
    Implementation = new MapImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

template <typename T_KEY, typename T_VALUE>
boolean Map<T_KEY, T_VALUE>::Exist(const T_KEY& REF_KEY) {
    if (Implementation)
        return Implementation->Exist(REF_KEY);
}

/*
template <typename T_KEY,typename T_VALUE>
T_VALUE& Map<T_KEY,T_VALUE>::Find(const T_KEY& REF_KEY)
{
    if(Implementation->Ref!=1)
    {
        MapImplementation* N_IMPL=Implementation->Duplicate();
        --(Implementation->Ref);
        Implementation=N_IMPL;
        ++(Implementation->Ref);
    }
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&(Implementation->MLock));
#endif
    if(Implementation->CurBuf)
        if(Implementation->CurBuf->Object.First==REF_KEY)
            return Implementation->CurBuf->Object.Second;
    for(Iterator P_ITER=Begin();P_ITER!=End();++P_ITER)
        if((*P_ITER).First==REF_KEY)
            return (*P_ITER).Second;
}

template <typename T_KEY,typename T_VALUE>
const T_VALUE& Map<T_KEY,T_VALUE>::Find(const T_KEY& REF_KEY) const
{
    if(Implementation->CurBuf)
        if(Implementation->CurBuf->Object.First==REF_KEY)
            return Implementation->CurBuf->Object.Second;
    for(Iterator P_ITER=Begin();P_ITER!=End();++P_ITER)
        if((*P_ITER).First==REF_KEY)
            return (*P_ITER).Second;
}
 */

template <typename T_KEY, typename T_VALUE>
void Map<T_KEY, T_VALUE>::Append(const T_KEY& REF_KEY, const T_VALUE& REF_VALUE) {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            MapImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->Append(REF_KEY, REF_VALUE);
    }
}

template <typename T_KEY, typename T_VALUE>
void Map<T_KEY, T_VALUE>::Remove(const T_KEY& REF_KEY) {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            MapImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->Remove(REF_KEY);
    }
}

template <typename T_KEY, typename T_VALUE>
typename Map<T_KEY, T_VALUE>::Iterator Map<T_KEY, T_VALUE>::Begin() {
    if (Implementation)
        return Iterator(Implementation->LstB);
    return End();
}

template <typename T_KEY, typename T_VALUE>
typename Map<T_KEY, T_VALUE>::Iterator Map<T_KEY, T_VALUE>::End() {
    return Iterator(0);
}

template <typename T_KEY, typename T_VALUE>
typename Map<T_KEY, T_VALUE>::Iterator Map<T_KEY, T_VALUE>::Find(const T_KEY& REF_KEY) {
    if (Implementation->Ref != 1) {
        MapImplementation* N_IMPL = Implementation->Duplicate();
        --(Implementation->Ref);
        Implementation = N_IMPL;
        ++(Implementation->Ref);
    }
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&(Implementation->MLock));
#endif
    if (Implementation->CurBuf)
        if (Implementation->CurBuf->Object.First == REF_KEY)
            return Iterator(Implementation->CurBuf);
    for (Iterator P_ITER = Begin(); P_ITER != End(); ++P_ITER)
        if ((*P_ITER).First == REF_KEY)
            return P_ITER;
    return End();
}

template <typename T_KEY, typename T_VALUE>
const typename Map<T_KEY, T_VALUE>::Iterator Map<T_KEY, T_VALUE>::Begin() const {
    if (Implementation)
        return Iterator(Implementation->LstB);
    return End();
}

template <typename T_KEY, typename T_VALUE>
const typename Map<T_KEY, T_VALUE>::Iterator Map<T_KEY, T_VALUE>::End() const {
    return Iterator(0);
}

template <typename T_KEY, typename T_VALUE>
const typename Map<T_KEY, T_VALUE>::Iterator Map<T_KEY, T_VALUE>::Find(const T_KEY& REF_KEY) const {
    if (Implementation->CurBuf)
        if (Implementation->CurBuf->Object.First == REF_KEY)
            return Iterator(Implementation->CurBuf);
    for (Iterator P_ITER = Begin(); P_ITER != End(); ++P_ITER)
        if ((*P_ITER).First == REF_KEY)
            return (*P_ITER).Second;
    return End();
}

template <typename T_KEY, typename T_VALUE>
        Map<T_KEY, T_VALUE>& Map<T_KEY, T_VALUE>::operator =(const Map<T_KEY, T_VALUE>& REF) {
    if (Implementation && REF.Implementation) {
        ++(REF.Implementation->Ref);
        if (--(Implementation->Ref) == 0) {
            MapImplementation* OLD = Implementation;
            Implementation = REF.Implementation;
            OLD->Clear();
            delete OLD;
        } else
            Implementation = REF.Implementation;
    }
    return *this;
}

template <typename T_KEY, typename T_VALUE>
T_VALUE& Map<T_KEY, T_VALUE>::operator [](const T_KEY& REF_KEY) {
    return Find(REF_KEY);
}

template <typename T_KEY, typename T_VALUE>
const T_VALUE& Map<T_KEY, T_VALUE>::operator [](const T_KEY& REF_KEY) const {
    return Find(REF_KEY);
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
