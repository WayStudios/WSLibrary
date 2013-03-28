/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <vector4.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
Vector4::Vector4(Vector4::TYPE V_X, Vector4::TYPE V_Y, Vector4::TYPE V_Z, Vector4::TYPE V_W):capacity(4)
{
    array[0]=V_X;
    array[1]=V_Y;
    array[2]=V_Z;
    array[3]=V_W;
}

Vector4::Vector4(const Vector4& REF):capacity(4)
{
    array[0]=REF.array[0];
    array[1]=REF.array[1];
    array[2]=REF.array[2];
    array[3]=REF.array[3];
}

Vector4::~Vector4(){}

Vector4::TYPE& Vector4::x(){return array[0];}

Vector4::TYPE& Vector4::y(){return array[1];}

Vector4::TYPE& Vector4::z(){return array[2];}

Vector4::TYPE& Vector4::w(){return array[3];}

const Vector4::TYPE& Vector4::x() const{return array[0];}

const Vector4::TYPE& Vector4::y() const{return array[1];}

const Vector4::TYPE& Vector4::z() const{return array[2];}

const Vector4::TYPE& Vector4::w() const{return array[3];}

Vector4& Vector4::set(Vector4::TYPE V_X, Vector4::TYPE V_Y, Vector4::TYPE V_Z, Vector4::TYPE V_W)
{
    x() = V_X;
    y() = V_Y;
    z() = V_Z;
    w() = V_W;
    return *this;
}

Vector4::TYPE& Vector4::operator [](SIZE IDX){return array[IDX];}

const Vector4::TYPE& Vector4::operator [](SIZE IDX) const{return array[IDX];}

Vector4& Vector4::operator =(const Vector4& REF)
{
    x() = REF.x();
    y() = REF.y();
    z() = REF.z();
    w() = REF.w();
    return *this;
}

BOOLEAN Vector4::operator ==(const Vector4& REF) const{return x() == REF.x() && y() == REF.y() && z() == REF.z() && w() == REF.w();}

BOOLEAN Vector4::operator !=(const Vector4& REF) const{return x() != REF.x() || y() != REF.y() || z() != REF.z() || w() != REF.w();}

BOOLEAN Vector4::operator >(const Vector4& REF) const{return x() > REF.x() && y() > REF.y() && z() > REF.z() && w() > REF.w();}

BOOLEAN Vector4::operator <(const Vector4& REF) const{return x() < REF.x() && y() < REF.y() && z() < REF.z() && w() < REF.w();}

BOOLEAN Vector4::operator >=(const Vector4& REF) const{return x() >= REF.x() && y() >= REF.y() && z() >= REF.z() && w() >= REF.w();}

BOOLEAN Vector4::operator <=(const Vector4& REF) const{return x() <= REF.x() && y() <= REF.y() && z() <= REF.z() && w() <= REF.w();}

END_SOURCECODE
