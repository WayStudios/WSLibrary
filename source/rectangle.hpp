/*******************************************************************************
 * Way Studios Graphics Library
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
    typedef VARIABLE VALUE;
    typedef Vector2 VECTOR;
//    typedef Matrix<Vector2<T_VALUE>, 2, 2> MATRIX;
    
    explicit Rectangle(const VECTOR& VEC_A=VECTOR(), const VECTOR& VEC_B=VECTOR());
    explicit Rectangle(const VECTOR&, VALUE, VALUE);
	explicit Rectangle(VALUE, VALUE);
    Rectangle(const Rectangle&);
    ~Rectangle();

	BOOLEAN Contain(VALUE, VALUE) const;
	BOOLEAN Contain(const VECTOR&) const;

    VECTOR Begin() const;
    VECTOR End() const;
        
    VALUE Width() const;
    VALUE Height() const;

    Rectangle& Set(const VECTOR&, const VECTOR&);
    Rectangle& Set(const VECTOR&, VALUE, VALUE);
	Rectangle& Set(VALUE, VALUE);

    Rectangle& operator=(const Rectangle&);

	/*    
    BOOLEAN operator==(const Rectangle&) const;
    BOOLEAN operator!=(const Rectangle&) const;
	*/

    const SIZE Capacity;
    Vector2 Array[2];
};
        
END_WS_NAMESPACE
                
END_HEADER

#endif
