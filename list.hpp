/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef LIST_HEADER
#define	LIST_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class EXPORT List {
    DECLARE_IMPLEMENTATION(List)
public:
    typedef TYPE VALUE;

    class Iterator;

    List();
    List(const List<TYPE>&);
    ~List();

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

    List<TYPE>& operator=(const List<TYPE>&);

    boolean operator==(const List<TYPE>&) const;
    boolean operator!=(const List<TYPE>&) const;

    TYPE& operator[](size);

    const TYPE& operator[](size) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <list_impl.hpp>

#endif
