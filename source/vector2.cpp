/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <vector2.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE

Vector2::Vector2(Vector2::TYPE V_X, Vector2::TYPE V_Y):capacity(2) {
    array[0] = V_X;
    array[1] = V_Y;
}

Vector2::Vector2(const Vector2& REF):capacity(2) {
    array[0] = REF.array[0];
    array[1] = REF.array[1];
}

Vector2::~Vector2() {}

Vector2::TYPE& Vector2::x() {return array[0];}

Vector2::TYPE& Vector2::y() {return array[1];}

const Vector2::TYPE& Vector2::x() const {return array[0];}

const Vector2::TYPE& Vector2::y() const {return array[1];}

Vector2& Vector2::set(Vector2::TYPE V_X, Vector2::TYPE V_Y) {
    x() = V_X;
    y() = V_Y;
    return *this;
}

Vector2::TYPE& Vector2::operator [](SIZE IDX){return array[IDX];}

const Vector2::TYPE& Vector2::operator [](SIZE IDX) const{return array[IDX];}

Vector2& Vector2::operator =(const Vector2& REF) {
    x() = REF.x();
    y() = REF.y();
    return *this;
}

BOOLEAN Vector2::operator ==(const Vector2& REF) const {return x() == REF.x() && y() == REF.y();}

BOOLEAN Vector2::operator !=(const Vector2& REF) const {return x() != REF.x() || y() != REF.y();}

BOOLEAN Vector2::operator >(const Vector2& REF) const {return x() > REF.x() && y() > REF.y();}

BOOLEAN Vector2::operator <(const Vector2& REF) const {return x() < REF.x() && y() < REF.y();}

BOOLEAN Vector2::operator >=(const Vector2& REF) const {return x() >= REF.x() && y() >= REF.y();}

BOOLEAN Vector2::operator <=(const Vector2& REF) const {return x() <= REF.x() && y() <= REF.y();}

END_SOURCECODE
