/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef MAP_HEADER
#define	MAP_HEADER

#include <global.hpp>
#include <pair.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T_KEY, typename T_VALUE>
class EXPORT Map {
    DECLARE_IMPLEMENTATION(Map)
public:
    typedef T_VALUE VALUE;
    typedef T_KEY KEY;
    typedef Pair<T_KEY, T_VALUE> PAIR;

    class Iterator;

    Map();
    Map(const Map<T_KEY, T_VALUE>&);
    ~Map();

    size Total() const;
    boolean Empty() const;
    void Clear();

    boolean Exist(const T_KEY&);

    //    T_VALUE& Find(const T_KEY&);

    //    const T_VALUE& Find(const T_KEY&) const;

    void Append(const T_KEY&, const T_VALUE&);

    void Remove(const T_KEY&);

    Iterator Begin();
    Iterator End();
    Iterator Find(const T_KEY&);

    const Iterator Begin() const;
    const Iterator End() const;
    const Iterator Find(const T_KEY&) const;

    Map<T_KEY, T_VALUE>& operator=(const Map<T_KEY, T_VALUE>&);

    T_VALUE& operator[](const T_KEY&);

    const T_VALUE& operator[](const T_KEY&) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <map_impl.hpp>

#endif
