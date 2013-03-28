/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef LISTNODE_IMPLEMENTATION_HEADER
#define	LISTNODE_IMPLEMENTATION_HEADER

#include <listnode.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
ListNode<T>::ListNode(const typename ListNode<T>::TYPE& REF, ListNode<T>* P, ListNode<T>* N) : object(REF), prev(P), next(N) {
}

template <typename T>
ListNode<T>::ListNode(const ListNode<T>& REF) : object(REF.object), prev(REF.prev), next(REF.next) {
}

template <typename T>
ListNode<T>::~ListNode() {
}

template <typename T>
ListNode<T>& ListNode<T>::operator =(const ListNode<T>& REF) {
    object = REF.object;
    prev = REF.prev;
    next = REF.next;
    return *this;
}

template <typename T>
BOOLEAN ListNode<T>::operator ==(const ListNode<T>& REF) const {
    return object == REF.object && prev == REF.prev && next == REF.next;
}

template <typename T>
BOOLEAN ListNode<T>::operator !=(const ListNode<T>& REF) const {
    return object != REF.object || prev != REF.prev || next != REF.next;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
