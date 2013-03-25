/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef PAIR_IMPLEMENTATION_HEADER
#define	PAIR_IMPLEMENTATION_HEADER

#include <pair.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T_FT, typename T_ST>
Pair<T_FT, T_ST>::Pair(const T_FT& R_F, const T_ST& R_S) : First(R_F), Second(R_S) {
}

template <typename T_FT, typename T_ST>
Pair<T_FT, T_ST>::Pair(const Pair<T_FT, T_ST>& REF) : First(REF.First), Second(REF.Second) {
}

template <typename T_FT, typename T_ST>
Pair<T_FT, T_ST>::~Pair() {
}

template <typename T_FT, typename T_ST>
        Pair<T_FT, T_ST>& Pair<T_FT, T_ST>::operator=(const Pair<T_FT, T_ST>& REF) {
    First = REF.First;
    Second = REF.Second;
    return *this;
}

template <typename T_FT, typename T_ST>
boolean Pair<T_FT, T_ST>::operator==(const Pair<T_FT, T_ST>& REF) const {
    return First == REF.First && Second == REF.Second;
}

template <typename T_FT, typename T_ST>
boolean Pair<T_FT, T_ST>::operator!=(const Pair<T_FT, T_ST>& REF) const {
    return First != REF.First || Second != REF.Second;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
