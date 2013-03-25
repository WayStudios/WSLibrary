/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef LISTNODE_IMPLEMENTATION_HEADER
#define	LISTNODE_IMPLEMENTATION_HEADER

#include <listnode.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
ListNode<TYPE>::ListNode(const TYPE& REF, ListNode<TYPE>* P, ListNode<TYPE>* N) : Object(REF), Prev(P), Next(N) {
}

template <typename TYPE>
ListNode<TYPE>::ListNode(const ListNode<TYPE>& REF) : Object(REF.Object), Prev(REF.Prev), Next(REF.Next) {
}

template <typename TYPE>
ListNode<TYPE>::~ListNode() {
}

template <typename TYPE>
        ListNode<TYPE>& ListNode<TYPE>::operator =(const ListNode<TYPE>& REF) {
    Object = REF.Object;
    Prev = REF.Prev;
    Next = REF.Next;
    return *this;
}

template <typename TYPE>
boolean ListNode<TYPE>::operator ==(const ListNode<TYPE>& REF) const {
    return Object == REF.Object && Prev == REF.Prev && Next == REF.Next;
}

template <typename TYPE>
boolean ListNode<TYPE>::operator !=(const ListNode<TYPE>& REF) const {
    return Object != REF.Object || Prev != REF.Prev || Next != REF.Next;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
