/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <vector2.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE

Vector2::Vector2(VALUE V_X, VALUE V_Y):Capacity(2)
{
    Array[0]=V_X;
    Array[1]=V_Y;
}

Vector2::Vector2(const Vector2& REF):Capacity(2)
{
    Array[0]=REF.Array[0];
    Array[1]=REF.Array[1];
}

Vector2::~Vector2(){}

Vector2::VALUE& Vector2::X(){return Array[0];}

Vector2::VALUE& Vector2::Y(){return Array[1];}

const Vector2::VALUE& Vector2::X() const{return Array[0];}

const Vector2::VALUE& Vector2::Y() const{return Array[1];}

Vector2& Vector2::Set(VALUE V_X, VALUE V_Y)
{
    X()=V_X;
    Y()=V_Y;
    return *this;
}

Vector2::VALUE& Vector2::operator [](size IDX){return Array[IDX];}

const Vector2::VALUE& Vector2::operator [](size IDX) const{return Array[IDX];}

Vector2& Vector2::operator =(const Vector2& REF)
{
    X()=REF.X();
    Y()=REF.Y();
    return *this;
}

boolean Vector2::operator ==(const Vector2& REF) const{return X()==REF.X() && Y()==REF.Y();}

boolean Vector2::operator !=(const Vector2& REF) const{return X()!=REF.X() || Y()!=REF.Y();}

boolean Vector2::operator >(const Vector2& REF) const{return X()>REF.X() && Y()>REF.Y();}

boolean Vector2::operator <(const Vector2& REF) const{return X()<REF.X() && Y()<REF.Y();}

boolean Vector2::operator >=(const Vector2& REF) const{return X()>=REF.X() && Y()>=REF.Y();}

boolean Vector2::operator <=(const Vector2& REF) const{return X()<=REF.X() && Y()<=REF.Y();}
        
END_SOURCECODE
