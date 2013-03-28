/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef LIST_HEADER
#define	LIST_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
class EXPORT List {
    DECLARE_IMPLEMENTATION(List)
public:
    typedef T TYPE;

    class Iterator;

    List();
    List(const List<T>&);
    ~List();

    SIZE total() const;
    BOOLEAN empty() const;
    void clear();

    BOOLEAN exist(const TYPE&) const;

    TYPE& first();
    TYPE& last();
    TYPE& at(SIZE);

    const TYPE& first() const;
    const TYPE& last() const;
    const TYPE& at(SIZE) const;

    void pushFront(const TYPE&);
    void popFront();

    void pushBack(const TYPE&);
    void popBack();

    void append(const TYPE&);
    void remove(const TYPE&);

    Iterator begin();
    Iterator end();

    const Iterator begin() const;
    const Iterator end() const;

    List<T>& operator =(const List<T>&);

    BOOLEAN operator ==(const List<T>&) const;
    BOOLEAN operator !=(const List<T>&) const;

    TYPE& operator[](SIZE);

    const TYPE& operator[](SIZE) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <list_impl.hpp>

#endif
