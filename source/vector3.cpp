/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <vector3.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
Vector3::Vector3(Vector3::TYPE V_X, Vector3::TYPE V_Y, Vector3::TYPE V_Z) : capacity(3)
{
    array[0] = V_X;
    array[1] = V_Y;
    array[2] = V_Z;
}

Vector3::Vector3(const Vector3& REF) : capacity(3)
{
    array[0] = REF.array[0];
    array[1] = REF.array[1];
    array[2] = REF.array[2];
}

Vector3::~Vector3(){}

Vector3::TYPE& Vector3::x(){return array[0];}

Vector3::TYPE& Vector3::y(){return array[1];}

Vector3::TYPE& Vector3::z(){return array[2];}

const Vector3::TYPE& Vector3::x() const{return array[0];}

const Vector3::TYPE& Vector3::y() const{return array[1];}

const Vector3::TYPE& Vector3::z() const{return array[2];}

Vector3& Vector3::set(Vector3::TYPE V_X, Vector3::TYPE V_Y, Vector3::TYPE V_Z) {
    x() = V_X;
    y() = V_Y;
    z() = V_Z;
    return *this;
}

Vector3::TYPE& Vector3::operator [](SIZE IDX) {return array[IDX];}

const Vector3::TYPE& Vector3::operator [](SIZE IDX) const {return array[IDX];}

Vector3& Vector3::operator =(const Vector3& REF) {
    x() = REF.x();
    y() = REF.y();
    z() = REF.z();
    return *this;
}

BOOLEAN Vector3::operator ==(const Vector3& REF) const{return x() == REF.x() && y() == REF.y() && z() == REF.z();}

BOOLEAN Vector3::operator !=(const Vector3& REF) const{return x() != REF.x() || y() != REF.y() || z() != REF.z();}

BOOLEAN Vector3::operator >(const Vector3& REF) const{return x() > REF.x() && y() > REF.y() && z() > REF.z();}

BOOLEAN Vector3::operator <(const Vector3& REF) const{return x() < REF.x() && y() < REF.y() && z() < REF.z();}

BOOLEAN Vector3::operator >=(const Vector3& REF) const{return x() >= REF.x() && y() >= REF.y() && z() >= REF.z();}

BOOLEAN Vector3::operator <=(const Vector3& REF) const{return x() <= REF.x() && y() <= REF.y() && z() <= REF.z();}

END_SOURCECODE
