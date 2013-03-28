/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef VECTOR_HEADER
#define	VECTOR_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
class EXPORT Vector {
    DECLARE_IMPLEMENTATION(Vector)
public:
    typedef T TYPE;

    class Iterator;

    Vector();
    Vector(const Vector<T>&);
    ~Vector();

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

    Vector<T>& operator =(const Vector<T>&);

    BOOLEAN operator ==(const Vector<T>&) const;
    BOOLEAN operator !=(const Vector<T>&) const;

    TYPE& operator [](SIZE);

    const TYPE& operator [](SIZE) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <vector_impl.hpp>

#endif
