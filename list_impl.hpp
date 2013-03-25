/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef LIST_IMPLEMENTATION_HEADER
#define	LIST_IMPLEMENTATION_HEADER

#include <list.hpp>
#include <allocator.hpp>
#include <listnode.hpp>
#include <atomicinteger.hpp>
#include <mutex.hpp>
#include <scopedlock.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class LOCAL List<TYPE>::ListImplementation : public Allocator< ListNode<TYPE> > {
    UNCOPYABLE(ListImplementation)
public:
    ListImplementation();
    ~ListImplementation();

    size Total() const;
    boolean Empty() const;
    ListImplementation* Duplicate();
    void Clear();

    void PushFront(const TYPE&);
    void PopFront();

    void PushBack(const TYPE&);
    void PopBack();

    void Remove(ListNode<TYPE>*);
    void Remove(const TYPE&);

#if !defined(WITHOUT_THREAD)
    AtomicInteger Ref;
    Mutex MLock;
#endif
    ListNode<TYPE>* LstB;
    ListNode<TYPE>* LstE;
};

template <typename TYPE>
class EXPORT List<TYPE>::Iterator {
    ListNode<TYPE>* Current;
public:
    explicit Iterator(ListNode<TYPE>*);
    Iterator(const Iterator&);
    ~Iterator();

    Iterator& operator=(const Iterator&);
    Iterator& operator++();
    Iterator& operator--();

    TYPE& operator*();

    const TYPE& operator*() const;

    boolean operator==(const Iterator&) const;
    boolean operator!=(const Iterator&) const;
};

template <typename TYPE>
List<TYPE>::ListImplementation::ListImplementation() : LstB(0), LstE(0) {
}

template <typename TYPE>
List<TYPE>::ListImplementation::~ListImplementation() {
}

template <typename TYPE>
size List<TYPE>::ListImplementation::Total() const {
    size RET = 0;
    if (!Empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        for (ListNode<TYPE>* P_ITER = LstB; P_ITER != 0; P_ITER = P_ITER->Next)
            ++RET;
    }
    return RET;
}

template <typename TYPE>
boolean List<TYPE>::ListImplementation::Empty() const {
    return !LstB;
}

template <typename TYPE>
typename List<TYPE>::ListImplementation* List<TYPE>::ListImplementation::Duplicate() {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
    ListImplementation* N_IMPL = new ListImplementation;
    if (N_IMPL) {
        if (!Empty()) {
            for (ListNode<TYPE>* P_ITER = LstB; P_ITER != 0; P_ITER = P_ITER->Next) {
                ListNode<TYPE>* P_N = Allocator< ListNode<TYPE> >::Allocate(1);
                new(P_N) ListNode<TYPE > (P_ITER->Object, 0, 0);
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

template <typename TYPE>
void List<TYPE>::ListImplementation::Clear() {
    if (!Empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        while (!Empty()) {
            ListNode<TYPE>* P_N = LstB->Next;
            Destruct(LstB);
            Deallocate(LstB);
            LstB = P_N;
            if (Empty())
                LstE = LstB = 0;
        }
    }
}

template <typename TYPE>
void List<TYPE>::ListImplementation::PushFront(const TYPE& REF) {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
    ListNode<TYPE>* P_N = Allocator< ListNode<TYPE> >::Allocate(1);
    new(P_N) ListNode<TYPE > (REF, 0, 0);
    if (Empty())
        LstE = LstB = P_N;
    else {
        P_N->Next = LstB;
        LstB->Prev = P_N;
        LstB = P_N;
    }
}

template <typename TYPE>
void List<TYPE>::ListImplementation::PopFront() {
    if (!Empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        ListNode<TYPE>* P_N = LstB->Next;
        if (P_N)
            P_N->Prev = 0;
        Destruct(LstB);
        Deallocate(LstB);
        LstB = P_N;
        if (Empty())
            LstE = LstB = 0;
    }
}

template <typename TYPE>
void List<TYPE>::ListImplementation::PushBack(const TYPE& REF) {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
    ListNode<TYPE>* P_N = Allocator< ListNode<TYPE> >::Allocate(1);
    new(P_N) ListNode<TYPE > (REF, 0, 0);
    if (Empty())
        LstE = LstB = P_N;
    else {
        P_N->Prev = LstE;
        LstE->Next = P_N;
        LstE = P_N;
    }
}

template <typename TYPE>
void List<TYPE>::ListImplementation::PopBack() {
    if (!Empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        ListNode<TYPE>* P_N = LstE->Prev;
        if (P_N)
            P_N->Next = 0;
        Destruct(LstE);
        Deallocate(LstE);
        LstE = P_N;
        if (Empty())
            LstE = LstB = 0;
    }
}

template <typename TYPE>
void List<TYPE>::ListImplementation::Remove(ListNode<TYPE>* P_N) {
    if (!Empty() && P_N) {
        if (P_N == LstB)
            return PopFront();
        if (P_N == LstE)
            return PopBack();
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        P_N->Prev->Next = P_N->Next;
        P_N->Next->Prev = P_N->Prev;
        Destruct(P_N);
        Deallocate(P_N);
    }
}

template <typename TYPE>
void List<TYPE>::ListImplementation::Remove(const TYPE& REF) {
    if (!Empty()) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        for (ListNode<TYPE>* P_ITER = LstB; P_ITER != 0; P_ITER = P_ITER->Next)
            if (P_ITER->Object == REF) {
                if (P_ITER == LstB)
                    LstB = LstB->Next;
                if (P_ITER == LstE)
                    LstE = LstE->Prev;
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

template <typename TYPE>
List<TYPE>::Iterator::Iterator(ListNode<TYPE>* P_ITER) : Current(P_ITER) {
}

template <typename TYPE>
List<TYPE>::Iterator::Iterator(const Iterator& REF) : Current(REF.Current) {
}

template <typename TYPE>
List<TYPE>::Iterator::~Iterator() {
}

template <typename TYPE>
        typename List<TYPE>::Iterator& List<TYPE>::Iterator::operator =(const Iterator& REF) {
    Current = REF.Current;
    return *this;
}

template <typename TYPE>
typename List<TYPE>::Iterator& List<TYPE>::Iterator::operator ++() {
    Current = Current->Next;
    return *this;
}

template <typename TYPE>
typename List<TYPE>::Iterator& List<TYPE>::Iterator::operator --() {
    Current = Current->Prev;
    return *this;
}

template <typename TYPE>
TYPE& List<TYPE>::Iterator::operator *() {
    return Current->Object;
}

template <typename TYPE>
const TYPE& List<TYPE>::Iterator::operator *() const {
    return Current->Object;
}

template <typename TYPE>
boolean List<TYPE>::Iterator::operator ==(const Iterator& REF) const {
    return Current == REF.Current;
}

template <typename TYPE>
boolean List<TYPE>::Iterator::operator !=(const Iterator& REF) const {
    return Current != REF.Current;
}

template <typename TYPE>
List<TYPE>::List() : Implementation(0) {
    Implementation = new ListImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

template <typename TYPE>
List<TYPE>::List(const List<TYPE>& REF) : Implementation(REF.Implementation) {
    if (Implementation)
        ++(Implementation->Ref);
}

template <typename TYPE>
List<TYPE>::~List() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->Clear();
            delete Implementation;
        }
}

template <typename TYPE>
size List<TYPE>::Total() const {
    if (Implementation)
        return Implementation->Total();
    return 0;
}

template <typename TYPE>
boolean List<TYPE>::Empty() const {
    if (Implementation)
        return Implementation->Empty();
    return true;
}

template <typename TYPE>
void List<TYPE>::Clear() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->Clear();
            delete Implementation;
        }
    Implementation = new ListImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

template <typename TYPE>
boolean List<TYPE>::Exist(const TYPE& REF) const {
    if (Implementation) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&(Implementation->MLock));
#endif
        for (Iterator P_ITER = Begin(); P_ITER != End(); ++P_ITER)
            if (*P_ITER == REF)
                return true;
    }
    return false;
}

template <typename TYPE>
TYPE& List<TYPE>::First() {
    if (Implementation->Ref != 1) {
        ListImplementation* N_IMPL = Implementation->Duplicate();
        --(Implementation->Ref);
        Implementation = N_IMPL;
        ++(Implementation->Ref);
    }
    return Implementation->LstB->Object;
}

template <typename TYPE>
TYPE& List<TYPE>::Last() {
    if (Implementation->Ref != 1) {
        ListImplementation* N_IMPL = Implementation->Duplicate();
        --(Implementation->Ref);
        Implementation = N_IMPL;
        ++(Implementation->Ref);
    }
    return Implementation->LstE->Object;
}

template <typename TYPE>
TYPE& List<TYPE>::At(size IDX) {
    if (Implementation->Ref != 1) {
        ListImplementation* N_IMPL = Implementation->Duplicate();
        --(Implementation->Ref);
        Implementation = N_IMPL;
        ++(Implementation->Ref);
    }
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&(Implementation->MLock));
#endif
    Iterator ITER = Implementation->LstB;
    for (size i = 0; i <= IDX; ++i)
        ++ITER;
    return *ITER;
}

template <typename TYPE>
const TYPE& List<TYPE>::First() const {
    return Implementation->LstB->Object;
}

template <typename TYPE>
const TYPE& List<TYPE>::Last() const {
    return Implementation->LstE->Object;
}

template <typename TYPE>
const TYPE& List<TYPE>::At(size IDX) const {
    Iterator ITER = Implementation->LstB;
    for (size i = 0; i <= IDX; ++i)
        ++ITER;
    return *ITER;
}

template <typename TYPE>
void List<TYPE>::PushFront(const TYPE& REF) {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            ListImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->PushFront(REF);
    }
}

template <typename TYPE>
void List<TYPE>::PopFront() {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            ListImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->PopFront();
    }
}

template <typename TYPE>
void List<TYPE>::PushBack(const TYPE& REF) {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            ListImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->PushBack(REF);
    }
}

template <typename TYPE>
void List<TYPE>::PopBack() {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            ListImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->PopBack();
    }
}

template <typename TYPE>
void List<TYPE>::Append(const TYPE& REF) {
    PushBack(REF);
}

template <typename TYPE>
void List<TYPE>::Remove(const TYPE& REF) {
    if (Implementation) {
        if (Implementation->Ref != 1) {
            ListImplementation* N_IMPL = Implementation->Duplicate();
            --(Implementation->Ref);
            Implementation = N_IMPL;
            ++(Implementation->Ref);
        }
        Implementation->Remove(REF);
    }
}

template <typename TYPE>
typename List<TYPE>::Iterator List<TYPE>::Begin() {
    if (Implementation)
        return Iterator(Implementation->LstB);
    return Iterator(0);
}

template <typename TYPE>
typename List<TYPE>::Iterator List<TYPE>::End() {
    return Iterator(0);
}

template <typename TYPE>
const typename List<TYPE>::Iterator List<TYPE>::Begin() const {
    if (Implementation)
        return Iterator(Implementation->LstB);
    return Iterator(0);
}

template <typename TYPE>
const typename List<TYPE>::Iterator List<TYPE>::End() const {
    return Iterator(0);
}

template <typename TYPE>
        List<TYPE>& List<TYPE>::operator =(const List<TYPE>& REF) {
    if (Implementation && REF.Implementation) {
        ++(REF.Implementation->Ref);
        if (--(Implementation->Ref) == 0) {
            ListImplementation* OLD = Implementation;
            Implementation = REF.Implementation;
            OLD->Clear();
            delete OLD;
        } else
            Implementation = REF.Implementation;
    }
    return *this;
}

template <typename TYPE>
boolean List<TYPE>::operator ==(const List<TYPE>& REF) const {
    if (Implementation && REF.Implementation) {
        if (Implementation != REF.Implementation) {
#if !defined(WITHOUT_THREAD)
            ScopedLock<Mutex> SL_Mutex_F(&(REF.Implementation->MLock));
            ScopedLock<Mutex> SL_Mutex_S(&(Implementation->MLock));
#endif
            ListNode<TYPE>* P_ITER_F = REF.Implementation->LstB;
            ListNode<TYPE>* P_ITER_S = Implementation->LstB;
            while (P_ITER_F && P_ITER_S) {
                if (P_ITER_F->Object != P_ITER_S->Object)
                    return false;
                P_ITER_F = P_ITER_F->Next;
                P_ITER_S = P_ITER_S->Next;
            }
        }
        return true;
    }
    return false;
}

template <typename TYPE>
boolean List<TYPE>::operator !=(const List<TYPE>& REF) const {
    if (Implementation && REF.Implementation) {
        if (Implementation != REF.Implementation) {
#if !defined(WITHOUT_THREAD)
            ScopedLock<Mutex> SL_Mutex_F(&(REF.Implementation->MLock));
            ScopedLock<Mutex> SL_Mutex_S(&(Implementation->MLock));
#endif
            ListNode<TYPE>* P_ITER_F = REF.Implementation->LstB;
            ListNode<TYPE>* P_ITER_S = Implementation->LstB;
            while (P_ITER_F && P_ITER_S) {
                if (P_ITER_F->Object != P_ITER_S->Object)
                    return true;
                P_ITER_F = P_ITER_F->Next;
                P_ITER_S = P_ITER_S->Next;
            }
        }
        return false;
    }
    return true;
}

template <typename TYPE>
TYPE& List<TYPE>::operator [](size IDX) {
    return At(IDX);
}

template <typename TYPE>
const TYPE& List<TYPE>::operator [](size IDX) const {
    return At(IDX);
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
