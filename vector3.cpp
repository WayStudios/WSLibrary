/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <vector3.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
Vector3::Vector3(VALUE V_X, VALUE V_Y, VALUE V_Z):Capacity(3)
{
    Array[0]=V_X;
    Array[1]=V_Y;
    Array[2]=V_Z;
}

Vector3::Vector3(const Vector3& REF):Capacity(3)
{
    Array[0]=REF.Array[0];
    Array[1]=REF.Array[1];
    Array[2]=REF.Array[2];
}

Vector3::~Vector3(){}

Vector3::VALUE& Vector3::X(){return Array[0];}

Vector3::VALUE& Vector3::Y(){return Array[1];}

Vector3::VALUE& Vector3::Z(){return Array[2];}

const Vector3::VALUE& Vector3::X() const{return Array[0];}

const Vector3::VALUE& Vector3::Y() const{return Array[1];}

const Vector3::VALUE& Vector3::Z() const{return Array[2];}

Vector3& Vector3::Set(VALUE V_X, VALUE V_Y, VALUE V_Z)
{
    X()=V_X;
    Y()=V_Y;
    Z()=V_Z;
    return *this;
}

Vector3::VALUE& Vector3::operator [](size IDX){return Array[IDX];}

const Vector3::VALUE& Vector3::operator [](size IDX) const{return Array[IDX];}

Vector3& Vector3::operator =(const Vector3& REF)
{
    X()=REF.X();
    Y()=REF.Y();
    Z()=REF.Z();
    return *this;
}

boolean Vector3::operator ==(const Vector3& REF) const{return X()==REF.X() && Y()==REF.Y() && Z()==REF.Z();}

boolean Vector3::operator !=(const Vector3& REF) const{return X()!=REF.X() || Y()!=REF.Y() || Z()!=REF.Z();}

boolean Vector3::operator >(const Vector3& REF) const{return X()>REF.X() && Y()>REF.Y() && Z()>REF.Z();}

boolean Vector3::operator <(const Vector3& REF) const{return X()<REF.X() && Y()<REF.Y() && Z()<REF.Z();}

boolean Vector3::operator >=(const Vector3& REF) const{return X()>=REF.X() && Y()>=REF.Y() && Z()>=REF.Z();}

boolean Vector3::operator <=(const Vector3& REF) const{return X()<=REF.X() && Y()<=REF.Y() && Z()<=REF.Z();}
        
END_SOURCECODE
