/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef QUEUENODE_HEADER
#define	QUEUENODE_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
struct EXPORT QueueNode {
	typedef T TYPE;

    explicit QueueNode(const TYPE&, QueueNode<T>*);
    QueueNode(const QueueNode<T>&);
    virtual ~QueueNode();

    QueueNode<T>& operator =(const QueueNode<T>&);

    BOOLEAN operator ==(const QueueNode<T>&) const;
    BOOLEAN operator !=(const QueueNode<T>&) const;

    TYPE object;
    QueueNode<T>* next;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <queuenode_impl.hpp>

#endif
