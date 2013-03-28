/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef LISTNODE_HEADER
#define	LISTNODE_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
struct EXPORT ListNode {
	typedef T TYPE;

    explicit ListNode(const TYPE&, ListNode<T>*, ListNode<T>*);
    ListNode(const ListNode<T>&);
    virtual ~ListNode();

    ListNode<T>& operator =(const ListNode<T>&);

    BOOLEAN operator ==(const ListNode<T>&) const;
    BOOLEAN operator !=(const ListNode<T>&) const;

    TYPE object;
    ListNode<T>* prev;
    ListNode<T>* next;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <listnode_impl.hpp>

#endif
