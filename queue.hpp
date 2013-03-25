/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef QUEUE_HEADER
#define	QUEUE_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class EXPORT Queue {
    DECLARE_IMPLEMENTATION(Queue)
public:
    typedef TYPE VALUE;

    class Iterator;

    Queue();
    Queue(const Queue<TYPE>&);
    ~Queue();

    size Total() const;
    boolean Empty() const;
    void Clear();

    boolean Exist(const TYPE&) const;

    TYPE& Top();

    const TYPE& Top() const;

    void Push(const TYPE&);

    void Pop();

    void Append(const TYPE&);

    Iterator Begin();
    Iterator End();

    const Iterator Begin() const;
    const Iterator End() const;

    Queue<TYPE>& operator=(const Queue<TYPE>&);

    boolean operator==(const Queue<TYPE>&) const;
    boolean operator!=(const Queue<TYPE>&) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <queue_impl.hpp>

#endif
