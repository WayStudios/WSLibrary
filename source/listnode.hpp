/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef LISTNODE_HEADER
#define	LISTNODE_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
struct EXPORT ListNode {
    explicit ListNode(const TYPE&, ListNode<TYPE>*, ListNode<TYPE>*);
    ListNode(const ListNode<TYPE>&);
    virtual ~ListNode();

    ListNode<TYPE>& operator=(const ListNode<TYPE>&);

    boolean operator==(const ListNode<TYPE>&) const;
    boolean operator!=(const ListNode<TYPE>&) const;

    TYPE Object;
    ListNode<TYPE>* Prev;
    ListNode<TYPE>* Next;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <listnode_impl.hpp>

#endif
