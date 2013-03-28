/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef PAIR_IMPLEMENTATION_HEADER
#define	PAIR_IMPLEMENTATION_HEADER

#include <pair.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T_FT, typename T_ST>
Pair<T_FT, T_ST>::Pair(const typename Pair<T_FT, T_ST>::FIRST& R_F, const typename Pair<T_FT, T_ST>::SECOND& R_S) : first(R_F), second(R_S) {
}

template <typename T_FT, typename T_ST>
Pair<T_FT, T_ST>::Pair(const Pair<T_FT, T_ST>& REF) : first(REF.first), second(REF.second) {
}

template <typename T_FT, typename T_ST>
Pair<T_FT, T_ST>::~Pair() {
}

template <typename T_FT, typename T_ST>
Pair<T_FT, T_ST>& Pair<T_FT, T_ST>::operator=(const Pair<T_FT, T_ST>& REF) {
    first = REF.first;
    second = REF.second;
    return *this;
}

template <typename T_FT, typename T_ST>
BOOLEAN Pair<T_FT, T_ST>::operator==(const Pair<T_FT, T_ST>& REF) const {
    return first == REF.first && second == REF.second;
}

template <typename T_FT, typename T_ST>
BOOLEAN Pair<T_FT, T_ST>::operator!=(const Pair<T_FT, T_ST>& REF) const {
    return first != REF.first || second != REF.second;
}

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#endif
