/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef VECTOR_HEADER
#define	VECTOR_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class EXPORT Vector {
    DECLARE_IMPLEMENTATION(Vector)
public:
    typedef TYPE VALUE;

    class Iterator;

    Vector();
    Vector(const Vector<TYPE>&);
    ~Vector();

    size Total() const;
    boolean Empty() const;
    void Clear();

    boolean Exist(const TYPE&) const;

    TYPE& First();
    TYPE& Last();
    TYPE& At(size);

    const TYPE& First() const;
    const TYPE& Last() const;
    const TYPE& At(size) const;

    void PushFront(const TYPE&);
    void PopFront();

    void PushBack(const TYPE&);
    void PopBack();

    void Append(const TYPE&);
    void Remove(const TYPE&);

    Iterator Begin();
    Iterator End();

    const Iterator Begin() const;
    const Iterator End() const;

    Vector<TYPE>& operator=(const Vector<TYPE>&);

    boolean operator==(const Vector<TYPE>&) const;
    boolean operator!=(const Vector<TYPE>&) const;

    TYPE& operator[](size);

    const TYPE& operator[](size) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <vector_impl.hpp>

#endif
