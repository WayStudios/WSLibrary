/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef RECTANGLE_HEADER
#define	RECTANGLE_HEADER

#include <global.hpp>
#include <vector2.hpp>
//#include <matrix.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE

struct EXPORT Rectangle
{
    typedef variable VALUE;
    typedef Vector2 VECTOR;
//    typedef Matrix<Vector2<T_VALUE>, 2, 2> MATRIX;
    
    explicit Rectangle(const VECTOR& VEC_A=VECTOR(), const VECTOR& VEC_B=VECTOR());
    explicit Rectangle(VALUE V_W, VALUE V_H, const VECTOR& VEC=VECTOR());
    Rectangle(const Rectangle&);
    ~Rectangle();

    VECTOR& Begin();
    VECTOR& End();

    const VECTOR& Begin() const;
    const VECTOR& End() const;
        
    VALUE Width() const;
    VALUE Height() const;
    
    Rectangle& Resize(VALUE, VALUE);

    Rectangle& Set(const VECTOR&, const VECTOR&);
    Rectangle& Set(VALUE, VALUE, const VECTOR& VEC=VECTOR());

    Rectangle& operator=(const Rectangle&);
    
    boolean operator==(const Rectangle&) const;
    boolean operator!=(const Rectangle&) const;

    const size Capacity;
    Vector2 Array[2];
};
        
END_WS_NAMESPACE
                
END_HEADER

#endif
