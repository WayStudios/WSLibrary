/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef LINE_HEADER
#define	LINE_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T>
struct EXPORT Line
{
    typedef T TYPE;
    
    explicit Line(const TYPE& VEC_A = TYPE(), const TYPE& VEC_B = TYPE());
    Line(const Line<T>&);
    ~Line();
    
    TYPE& a();
    TYPE& b();

    const TYPE& a() const;
    const TYPE& b() const;
    
    Line<TYPE>& set(const TYPE&, const TYPE&);
    
    TYPE& operator [](SIZE);
    
    const TYPE& operator [](SIZE) const;
    
    Line<T>& operator =(const Line<T>&);
    
    BOOLEAN operator ==(const Line<T>&) const;
    BOOLEAN operator !=(const Line<T>&) const;

    BOOLEAN operator >(const Line<T>&) const;
    BOOLEAN operator <(const Line<T>&) const;

    BOOLEAN operator >=(const Line<T>&) const;
    BOOLEAN operator <=(const Line<T>&) const;

    const SIZE capacity;
    TYPE array[2];
};

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER
        
#include <line_impl.hpp>

#endif
