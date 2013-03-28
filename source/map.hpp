/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef MAP_HEADER
#define	MAP_HEADER

#include <global.hpp>
#include <pair.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T_KEY, typename T>
class EXPORT Map {
    DECLARE_IMPLEMENTATION(Map)
public:
    typedef T TYPE;
    typedef T_KEY KEY;
	typedef Pair<KEY, TYPE> PAIR;

    class Iterator;

    Map();
    Map(const Map<KEY, TYPE>&);
    ~Map();

    SIZE total() const;
    BOOLEAN empty() const;
    void clear();

    BOOLEAN exist(const KEY&);

    void append(const KEY&, const TYPE&);
    void remove(const KEY&);

    Iterator begin();
    Iterator end();
    Iterator find(const KEY&);

    const Iterator begin() const;
    const Iterator end() const;
    const Iterator find(const KEY&) const;

    Map<KEY, TYPE>& operator=(const Map<KEY, TYPE>&);

    TYPE& operator[](const KEY&);

    const TYPE& operator[](const KEY&) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <map_impl.hpp>

#endif
