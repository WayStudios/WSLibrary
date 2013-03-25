/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ARRAY_HEADER
#define	ARRAY_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class EXPORT Array {
    DECLARE_IMPLEMENTATION(Array)
public:
    typedef TYPE VALUE;

    explicit Array(const TYPE&, size);
    explicit Array(TYPE*, size);
    Array(const Array<TYPE>&);
    ~Array();

    size Size() const;

    TYPE& At(size);

    const TYPE& At(size) const;

    Array<TYPE>& operator=(const Array<TYPE>&);

    boolean operator==(const Array<TYPE>&) const;
    boolean operator!=(const Array<TYPE>&) const;

    TYPE& operator[](size);

    const TYPE& operator[](size) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <array_impl.hpp>

#endif
