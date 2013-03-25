/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <vector4.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
Vector4::Vector4(VALUE V_X, VALUE V_Y, VALUE V_Z, VALUE V_W):Capacity(4)
{
    Array[0]=V_X;
    Array[1]=V_Y;
    Array[2]=V_Z;
    Array[3]=V_W;
}

Vector4::Vector4(const Vector4& REF):Capacity(4)
{
    Array[0]=REF.Array[0];
    Array[1]=REF.Array[1];
    Array[2]=REF.Array[2];
    Array[3]=REF.Array[3];
}

Vector4::~Vector4(){}

Vector4::VALUE& Vector4::X(){return Array[0];}

Vector4::VALUE& Vector4::Y(){return Array[1];}

Vector4::VALUE& Vector4::Z(){return Array[2];}

Vector4::VALUE& Vector4::W(){return Array[3];}

const Vector4::VALUE& Vector4::X() const{return Array[0];}

const Vector4::VALUE& Vector4::Y() const{return Array[1];}

const Vector4::VALUE& Vector4::Z() const{return Array[2];}

const Vector4::VALUE& Vector4::W() const{return Array[3];}

Vector4& Vector4::Set(VALUE V_X, VALUE V_Y, VALUE V_Z, VALUE V_W)
{
    X()=V_X;
    Y()=V_Y;
    Z()=V_Z;
    W()=V_W;
    return *this;
}

Vector4::VALUE& Vector4::operator [](size IDX){return Array[IDX];}

const Vector4::VALUE& Vector4::operator [](size IDX) const{return Array[IDX];}

Vector4& Vector4::operator =(const Vector4& REF)
{
    X()=REF.X();
    Y()=REF.Y();
    Z()=REF.Z();
    W()=REF.W();
    return *this;
}

boolean Vector4::operator ==(const Vector4& REF) const{return X()==REF.X() && Y()==REF.Y() && Z()==REF.Z() && W()==REF.W();}

boolean Vector4::operator !=(const Vector4& REF) const{return X()!=REF.X() || Y()!=REF.Y() || Z()!=REF.Z() || W()!=REF.W();}

boolean Vector4::operator >(const Vector4& REF) const{return X()>REF.X() && Y()>REF.Y() && Z()>REF.Z() && W()>REF.W();}

boolean Vector4::operator <(const Vector4& REF) const{return X()<REF.X() && Y()<REF.Y() && Z()<REF.Z() && W()<REF.W();}

boolean Vector4::operator >=(const Vector4& REF) const{return X()>=REF.X() && Y()>=REF.Y() && Z()>=REF.Z() && W()>=REF.W();}

boolean Vector4::operator <=(const Vector4& REF) const{return X()<=REF.X() && Y()<=REF.Y() && Z()<=REF.Z() && W()<=REF.W();}

END_SOURCECODE
