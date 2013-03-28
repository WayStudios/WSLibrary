/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ARRAY_HEADER
#define	ARRAY_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
class EXPORT Array {
    DECLARE_IMPLEMENTATION(Array)
public:
    typedef T TYPE;

    explicit Array(const TYPE&, SIZE);
    explicit Array(TYPE*, SIZE);
    Array(const Array<T>&);
    ~Array();

    SIZE size() const;

    TYPE& at(SIZE);

    const TYPE& at(SIZE) const;

    Array<T>& operator=(const Array<T>&);

    BOOLEAN operator==(const Array<T>&) const;
    BOOLEAN operator!=(const Array<T>&) const;

    TYPE& operator[](SIZE);

    const TYPE& operator[](SIZE) const;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <array_impl.hpp>

#endif
