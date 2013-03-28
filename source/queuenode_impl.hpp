/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef QUEUENODE_IMPLEMENTATION_HEADER
#define	QUEUENODE_IMPLEMENTATION_HEADER

#include <queuenode.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
QueueNode<T>::QueueNode(const typename QueueNode<T>::TYPE& REF, QueueNode<T>* N) : object(REF), next(N) {
}

template <typename T>
QueueNode<T>::QueueNode(const QueueNode<T>& REF) : object(REF.object), next(REF.next) {
}

template <typename T>
QueueNode<T>::~QueueNode() {
}

template <typename T>
QueueNode<T>& QueueNode<T>::operator =(const QueueNode<T>& REF) {
    object = REF.object;
    next = REF.next;
    return *this;
}

template <typename T>
BOOLEAN QueueNode<T>::operator ==(const QueueNode<T>& REF) const {
    return object == REF.object && next == REF.next;
}

template <typename T>
BOOLEAN QueueNode<T>::operator !=(const QueueNode<T>& REF) const {
    return object != REF.object || next != REF.next;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
