/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef MATRIX_HEADER
#define	MATRIX_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE
        
template <typename T_VALUE, size R_SIZE, size C_SIZE>
struct EXPORT Matrix
{
    typedef T_VALUE VALUE;
    
    explicit Matrix(const T_VALUE& V=T_VALUE());
    explicit Matrix(const T_VALUE*);
    Matrix(const Matrix<T_VALUE, R_SIZE, C_SIZE>&);
    ~Matrix();
    
    size Row() const;
    size Column() const;
    
    T_VALUE& At(size, size);

    const T_VALUE& At(size, size) const;
    
    Matrix<T_VALUE, R_SIZE, C_SIZE>& Set(const T_VALUE*);

    T_VALUE& operator()(size, size);
    
    const T_VALUE& operator()(size, size) const;
    
    Matrix<T_VALUE, R_SIZE, C_SIZE>& operator=(const Matrix<T_VALUE, R_SIZE, C_SIZE>&);
    
    boolean operator==(const Matrix<T_VALUE, R_SIZE, C_SIZE>&) const;
    boolean operator!=(const Matrix<T_VALUE, R_SIZE, C_SIZE>&) const;
    
    const size Capacity;
    T_VALUE Array[R_SIZE][C_SIZE];
};

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER
        
#include <matrix_impl.hpp>

#endif
