/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef LINE_HEADER
#define	LINE_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_VECTOR>
struct EXPORT Line
{
    typedef T_VECTOR VALUE;
    
    explicit Line(const T_VECTOR& VEC_A=T_VECTOR(), const T_VECTOR& VEC_B=T_VECTOR());
    Line(const Line<T_VECTOR>&);
    ~Line();
    
    T_VECTOR& A();
    T_VECTOR& B();

    const T_VECTOR& A() const;
    const T_VECTOR& B() const;
    
    Line<T_VECTOR>& Set(const T_VECTOR&, const T_VECTOR&);
    
    T_VECTOR& operator[](size);
    
    const T_VECTOR& operator[](size) const;
    
    Line<T_VECTOR>& operator=(const Line<T_VECTOR>&);
    
    boolean operator==(const Line<T_VECTOR>&) const;
    boolean operator!=(const Line<T_VECTOR>&) const;

    boolean operator>(const Line<T_VECTOR>&) const;
    boolean operator<(const Line<T_VECTOR>&) const;

    boolean operator>=(const Line<T_VECTOR>&) const;
    boolean operator<=(const Line<T_VECTOR>&) const;

    const size Capacity;
    T_VECTOR Array[2];
};

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER
        
#include <line_impl.hpp>

#endif
