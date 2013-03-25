/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef QUEUENODE_HEADER
#define	QUEUENODE_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
struct EXPORT QueueNode {
    explicit QueueNode(const TYPE&, QueueNode<TYPE>*);
    QueueNode(const QueueNode<TYPE>&);
    virtual ~QueueNode();

    QueueNode<TYPE>& operator=(const QueueNode<TYPE>&);

    boolean operator==(const QueueNode<TYPE>&) const;
    boolean operator!=(const QueueNode<TYPE>&) const;

    TYPE Object;
    QueueNode<TYPE>* Next;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <queuenode_impl.hpp>

#endif
