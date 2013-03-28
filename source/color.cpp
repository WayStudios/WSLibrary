/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <color.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
Color::Color(UBYTE R, UBYTE G, UBYTE B, UBYTE A):capacity(4)
{
    array[0]=A;
    array[1]=R;
    array[2]=G;
    array[3]=B;
}

Color::Color(const Color& REF):capacity(4)
{
    array[0]=REF.array[0];
    array[1]=REF.array[1];
    array[2]=REF.array[2];
    array[3]=REF.array[3];
}

Color::~Color(){}

Color::TYPE& Color::alpha(){return array[0];}

Color::TYPE& Color::red(){return array[1];}

Color::TYPE& Color::green(){return array[2];}

Color::TYPE& Color::blue(){return array[3];}

const Color::TYPE& Color::alpha() const{return array[0];}

const Color::TYPE& Color::red() const{return array[1];}

const Color::TYPE& Color::green() const{return array[2];}

const Color::TYPE& Color::blue() const{return array[3];}

Color& Color::set(UBYTE R, UBYTE G, UBYTE B)
{
    red()=R;
    green()=G;
    blue()=B;
    return *this;
}

Color& Color::set(UBYTE A, UBYTE R, UBYTE G, UBYTE B)
{
    alpha()=A;
    red()=R;
    green()=G;
    blue()=B;
    return *this;
}

Color& Color::operator =(const Color& REF)
{
    alpha()=REF.alpha();
    red()=REF.red();
    green()=REF.green();
    blue()=REF.blue();
    return *this;
}

BOOLEAN Color::operator ==(const Color& REF) const{return alpha()==REF.alpha() && red()==REF.red() && green()==REF.green() && blue()==REF.blue();}

BOOLEAN Color::operator !=(const Color& REF) const{return alpha()!=REF.alpha() || red()!=REF.red() || green()!=REF.green() || blue()!=REF.blue();}

END_SOURCECODE
