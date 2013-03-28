/*******************************************************************************
 * Way Studios Library
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
	typedef T_FT FIRST;
	typedef T_ST SECOND;

    explicit Pair(const FIRST&, const SECOND&);
    Pair(const Pair<FIRST, SECOND>&);
    ~Pair();

    Pair<FIRST, SECOND>& operator =(const Pair<FIRST, SECOND>&);

    BOOLEAN operator ==(const Pair<FIRST, SECOND>&) const;
    BOOLEAN operator !=(const Pair<FIRST, SECOND>&) const;

    FIRST first;
    SECOND second;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <pair_impl.hpp>

#endif
