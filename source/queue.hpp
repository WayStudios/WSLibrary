/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef QUEUE_HEADER
#define	QUEUE_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
class EXPORT Queue {
    DECLARE_IMPLEMENTATION(Queue)
public:
    typedef T TYPE;

    class Iterator;

    Queue();
    Queue(const Queue<T>&);
    ~Queue();

    SIZE total() const;
    BOOLEAN empty() const;
    void clear();

    BOOLEAN exist(const TYPE&) const;

    TYPE& top();

    const TYPE& top() const;

    void push(const TYPE&);

    void pop();

    void append(const TYPE&);

    Iterator begin();
    Iterator end();

    const Iterator begin() const;
    const Iterator end() const;

    Queue<T>& operator =(const Queue<T>&);

    BOOLEAN operator ==(const Queue<T>&) const;
    BOOLEAN operator !=(const Queue<T>&) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <queue_impl.hpp>

#endif
