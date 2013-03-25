/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef MATRIX_IMPLEMENTATION_HEADER
#define	MATRIX_IMPLEMENTATION_HEADER

#include <matrix.hpp>

BEGIN_HEADER
        
BEGIN_TEMPLATE
        
BEGIN_WS_NAMESPACE

template <typename T_VALUE, size R_SIZE, size C_SIZE>
Matrix<T_VALUE, R_SIZE, C_SIZE>::Matrix(const T_VALUE& V):Capacity(R_SIZE*C_SIZE)
{
    for(size R_ITER=0;R_ITER!=R_SIZE;++R_ITER)
        for(size C_ITER=0;C_ITER!=C_SIZE;++C_ITER)
            Array[R_ITER][C_ITER]=V;
}

template <typename T_VALUE, size R_SIZE, size C_SIZE>
Matrix<T_VALUE, R_SIZE, C_SIZE>::Matrix(const T_VALUE* P_ARRAY):Capacity(R_SIZE*C_SIZE)
{
    size ITER=0;
    for(size R_ITER=0;R_ITER!=R_SIZE;++R_ITER)
        for(size C_ITER=0;C_ITER!=C_SIZE;++C_ITER)
            Array[R_ITER][C_ITER]=P_ARRAY[ITER++];
}

template <typename T_VALUE, size R_SIZE, size C_SIZE>
Matrix<T_VALUE, R_SIZE, C_SIZE>::Matrix(const Matrix<T_VALUE,R_SIZE,C_SIZE>& REF):Capacity(R_SIZE*C_SIZE)
{
    for(size R_ITER=0;R_ITER!=R_SIZE;++R_ITER)
        for(size C_ITER=0;C_ITER!=C_SIZE;++C_ITER)
            Array[R_ITER][C_ITER]=REF.Array[R_ITER][C_ITER];
}

template <typename T_VALUE, size R_SIZE, size C_SIZE>
Matrix<T_VALUE, R_SIZE, C_SIZE>::~Matrix(){}

template <typename T_VALUE, size R_SIZE, size C_SIZE>
size Matrix<T_VALUE, R_SIZE, C_SIZE>::Row() const{return R_SIZE;}
        
template <typename T_VALUE, size R_SIZE, size C_SIZE>
size Matrix<T_VALUE, R_SIZE, C_SIZE>::Column() const{return C_SIZE;}

template <typename T_VALUE, size R_SIZE, size C_SIZE>
T_VALUE& Matrix<T_VALUE, R_SIZE, C_SIZE>::At(size R_IDX, size C_IDX){return Array[R_IDX][C_IDX];}

template <typename T_VALUE, size R_SIZE, size C_SIZE>
const T_VALUE& Matrix<T_VALUE, R_SIZE, C_SIZE>::At(size R_IDX, size C_IDX) const{return Array[R_IDX][C_IDX];}

template <typename T_VALUE, size R_SIZE, size C_SIZE>
Matrix<T_VALUE, R_SIZE, C_SIZE>& Matrix<T_VALUE, R_SIZE, C_SIZE>::Set(const T_VALUE* P_ARRAY)
{    
    size ITER=0;
    for(size R_ITER=0;R_ITER!=R_SIZE;++R_ITER)
        for(size C_ITER=0;C_ITER!=C_SIZE;++C_ITER)
            At(R_ITER, C_ITER)=P_ARRAY[ITER++];
    return *this;
}

template <typename T_VALUE, size R_SIZE, size C_SIZE>
T_VALUE& Matrix<T_VALUE, R_SIZE, C_SIZE>::operator ()(size R_IDX, size C_IDX){return Array[R_IDX][C_IDX];}

template <typename T_VALUE, size R_SIZE, size C_SIZE>
const T_VALUE& Matrix<T_VALUE, R_SIZE, C_SIZE>::operator ()(size R_IDX, size C_IDX) const{return Array[R_IDX][C_IDX];}

template <typename T_VALUE, size R_SIZE, size C_SIZE>
Matrix<T_VALUE, R_SIZE, C_SIZE>& Matrix<T_VALUE, R_SIZE, C_SIZE>::operator =(const Matrix<T_VALUE,R_SIZE,C_SIZE>& REF)
{
    for(size R_ITER=0;R_ITER!=R_SIZE;++R_ITER)
        for(size C_ITER=0;C_ITER!=C_SIZE;++C_ITER)
            At(R_ITER, C_ITER)=REF.At(R_ITER, C_ITER);
    return *this;
}

template <typename T_VALUE, size R_SIZE, size C_SIZE>
boolean Matrix<T_VALUE, R_SIZE, C_SIZE>::operator ==(const Matrix<T_VALUE,R_SIZE,C_SIZE>& REF) const
{    
    for(size R_ITER=0;R_ITER!=R_SIZE;++R_ITER)
        for(size C_ITER=0;C_ITER!=C_SIZE;++C_ITER)
            if(At(R_ITER, C_ITER)!=REF.At(R_ITER, C_ITER))
                return false;
}

template <typename T_VALUE, size R_SIZE, size C_SIZE>
boolean Matrix<T_VALUE, R_SIZE, C_SIZE>::operator !=(const Matrix<T_VALUE,R_SIZE,C_SIZE>& REF) const
{    
    for(size R_ITER=0;R_ITER!=R_SIZE;++R_ITER)
        for(size C_ITER=0;C_ITER!=C_SIZE;++C_ITER)
            if(At(R_ITER, C_ITER)!=REF.At(R_ITER, C_ITER))
                return true;
}

END_WS_NAMESPACE
        
END_TEMPLATE
        
END_HEADER

#endif
