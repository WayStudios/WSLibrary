/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef PAIR_HEADER
#define	PAIR_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T_FT, typename T_ST>
struct EXPORT Pair {
    explicit Pair(const T_FT&, const T_ST&);
    Pair(const Pair<T_FT, T_ST>&);
    ~Pair();

    Pair<T_FT, T_ST>& operator=(const Pair<T_FT, T_ST>&);

    boolean operator==(const Pair<T_FT, T_ST>&) const;
    boolean operator!=(const Pair<T_FT, T_ST>&) const;

    T_FT First;
    T_ST Second;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <pair_impl.hpp>

#endif
