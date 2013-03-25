/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <rectangle.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE

Rectangle::Rectangle(const VECTOR& VEC_A, const VECTOR& VEC_B):Capacity(2)
{
    Array[0]=VEC_A;
    Array[1]=VEC_B;
}

Rectangle::Rectangle(VALUE V_W, VALUE V_H, const VECTOR& VEC):Capacity(2)
{
    Array[0]=VEC;
    Array[1]=VECTOR(VEC.X()+V_W, VEC.Y()+V_H);
}

Rectangle::Rectangle(const Rectangle& REF):Capacity(2)
{
    Array[0]=REF.Array[0];
    Array[1]=REF.Array[1];
}

Rectangle::~Rectangle(){}

Rectangle::VECTOR& Rectangle::Begin(){return Array[0];}

Rectangle::VECTOR& Rectangle::End(){return Array[1];}

const Rectangle::VECTOR& Rectangle::Begin() const{return Array[0];}

const Rectangle::VECTOR& Rectangle::End() const{return Array[1];}

Rectangle::VALUE Rectangle::Width() const
{
    VALUE RET_W=0;
    if(Begin().X() > End().X())
        RET_W=Begin().X() - End().X();
    else
        RET_W=End().X() - Begin().X();
    return RET_W;
}

Rectangle::VALUE Rectangle::Height() const
{
    VALUE RET_H=0;
    if(Begin().Y() > End().Y())
        RET_H=Begin().Y() - End().Y();
    else
        RET_H=End().Y() - Begin().Y();
    return RET_H;
}

Rectangle& Rectangle::Resize(VALUE V_W, VALUE V_H)
{
    End().Set(Begin().X()+V_W, Begin().Y()+V_H);
    return *this;
}

Rectangle& Rectangle::Set(const VECTOR& VEC_B, const VECTOR& VEC_E)
{
    Begin()=VEC_B;
    End()=VEC_E;
    return *this;
}

Rectangle& Rectangle::Set(VALUE V_W, VALUE V_H, const VECTOR& VEC)
{
    Begin()=VEC;
    End().Set(Begin().X()+V_W, Begin().Y()+V_H);
    return *this;
}

Rectangle& Rectangle::operator =(const Rectangle& REF)
{
    Begin()=REF.Begin();
    End()=REF.End();
    return *this;
}

boolean Rectangle::operator ==(const Rectangle& REF) const{return Begin()==REF.Begin() && End()==REF.End();}

boolean Rectangle::operator !=(const Rectangle& REF) const{return Begin()!=REF.Begin() || End()!=REF.End();}

END_SOURCECODE
