/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef QUEUENODE_IMPLEMENTATION_HEADER
#define	QUEUENODE_IMPLEMENTATION_HEADER

#include <queuenode.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
QueueNode<TYPE>::QueueNode(const TYPE& REF, QueueNode<TYPE>* N) : Object(REF), Next(N) {
}

template <typename TYPE>
QueueNode<TYPE>::QueueNode(const QueueNode<TYPE>& REF) : Object(REF.Object), Next(REF.Next) {
}

template <typename TYPE>
QueueNode<TYPE>::~QueueNode() {
}

template <typename TYPE>
        QueueNode<TYPE>& QueueNode<TYPE>::operator =(const QueueNode<TYPE>& REF) {
    Object = REF.Object;
    Next = REF.Next;
    return *this;
}

template <typename TYPE>
boolean QueueNode<TYPE>::operator ==(const QueueNode<TYPE>& REF) const {
    return Object == REF.Object && Next == REF.Next;
}

template <typename TYPE>
boolean QueueNode<TYPE>::operator !=(const QueueNode<TYPE>& REF) const {
    return Object != REF.Object || Next != REF.Next;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
