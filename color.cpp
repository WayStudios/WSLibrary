/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <color.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
Color::Color(ubyte R, ubyte G, ubyte B, ubyte A):Capacity(4)
{
    Array[0]=A;
    Array[1]=R;
    Array[2]=G;
    Array[3]=B;
}

Color::Color(const Color& REF):Capacity(4)
{
    Array[0]=REF.Array[0];
    Array[1]=REF.Array[1];
    Array[2]=REF.Array[2];
    Array[3]=REF.Array[3];
}

Color::~Color(){}

Color::VALUE& Color::Alpha(){return Array[0];}

Color::VALUE& Color::Red(){return Array[1];}

Color::VALUE& Color::Green(){return Array[2];}

Color::VALUE& Color::Blue(){return Array[3];}

const Color::VALUE& Color::Alpha() const{return Array[0];}

const Color::VALUE& Color::Red() const{return Array[1];}

const Color::VALUE& Color::Green() const{return Array[2];}

const Color::VALUE& Color::Blue() const{return Array[3];}

Color& Color::Set(ubyte R, ubyte G, ubyte B)
{
    Red()=R;
    Green()=G;
    Blue()=B;
    return *this;
}

Color& Color::Set(ubyte A, ubyte R, ubyte G, ubyte B)
{
    Alpha()=A;
    Red()=R;
    Green()=G;
    Blue()=B;
    return *this;
}

Color& Color::operator =(const Color& REF)
{
    Alpha()=REF.Alpha();
    Red()=REF.Red();
    Green()=REF.Green();
    Blue()=REF.Blue();
    return *this;
}

boolean Color::operator ==(const Color& REF) const{return Alpha()==REF.Alpha() && Red()==REF.Red() && Green()==REF.Green() && Blue()==REF.Blue();}

boolean Color::operator !=(const Color& REF) const{return Alpha()!=REF.Alpha() || Red()!=REF.Red() || Green()!=REF.Green() || Blue()!=REF.Blue();}

END_SOURCECODE
