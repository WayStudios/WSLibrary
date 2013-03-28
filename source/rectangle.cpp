/*******************************************************************************
 * Way Studios Graphics Library
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

Rectangle::Rectangle(const VECTOR& VEC, VALUE V_W, VALUE V_H):Capacity(2)
{
    Array[0]=VEC;
    Array[1]=VECTOR(VEC.x()+V_W, VEC.y()+V_H);
}

Rectangle::Rectangle(VALUE V_W, VALUE V_H):Capacity(2)
{
	Array[0]=VECTOR();
	Array[1]=VECTOR(V_W, V_H);
}

Rectangle::Rectangle(const Rectangle& REF):Capacity(2)
{
    Array[0]=REF.Array[0];
    Array[1]=REF.Array[1];
}

Rectangle::~Rectangle(){}

BOOLEAN Rectangle::Contain(VALUE V_X, VALUE V_Y) const{return Contain(VECTOR(V_X, V_Y));}

BOOLEAN Rectangle::Contain(const VECTOR& VEC) const{return VEC >= Begin() && VEC <= End();}

Rectangle::VECTOR Rectangle::Begin() const
{
	VECTOR RET;
	if(Array[0]==Array[1])
		RET=Array[0];
	else
	{
		if(Array[0].x() < Array[1].x())
			RET.x()=Array[0].x();
		else
			RET.x()=Array[1].x();		
		if(Array[0].y() < Array[1].y())
			RET.y()=Array[0].y();
		else
			RET.y()=Array[1].y();
	}
	return RET;
}

Rectangle::VECTOR Rectangle::End() const
{
	VECTOR RET;
	if(Array[0]==Array[1])
		RET=Array[0];
	else
	{
		if(Array[0].x() > Array[1].x())
			RET.x()=Array[0].x();
		else
			RET.x()=Array[1].x();		
		if(Array[0].y() > Array[1].y())
			RET.y()=Array[0].y();
		else
			RET.y()=Array[1].y();
	}
	return RET;
}

Rectangle::VALUE Rectangle::Width() const
{
    VALUE RET_W=0;
    if(Begin().x() > End().x())
        RET_W=Begin().x() - End().x();
    else
        RET_W=End().x() - Begin().x();
    return RET_W;
}

Rectangle::VALUE Rectangle::Height() const
{
    VALUE RET_H=0;
    if(Begin().y() > End().y())
        RET_H=Begin().y() - End().y();
    else
        RET_H=End().y() - Begin().y();
    return RET_H;
}

Rectangle& Rectangle::Set(const VECTOR& VEC_B, const VECTOR& VEC_E)
{
	Array[0]=VEC_B;
	Array[1]=VEC_E;
    return *this;
}

Rectangle& Rectangle::Set(const VECTOR& VEC, VALUE V_W, VALUE V_H)
{
    Begin()=VEC;
    End().set(Begin().x()+V_W, Begin().y()+V_H);
    return *this;
}

Rectangle& Rectangle::Set(VALUE V_W, VALUE V_H)
{
	Array[0]=Begin();
	Array[1].set(Array[0].x()+V_W, Array[0].y()+V_H);
	return *this;
}

Rectangle& Rectangle::operator =(const Rectangle& REF)
{
	Array[0]=REF.Array[0];
	Array[1]=REF.Array[1];
    return *this;
}

/*
boolean Rectangle::operator ==(const Rectangle& REF) const{return Begin()==REF.Begin() && End()==REF.End();}

boolean Rectangle::operator !=(const Rectangle& REF) const{return Begin()!=REF.Begin() || End()!=REF.End();}
*/

END_SOURCECODE
