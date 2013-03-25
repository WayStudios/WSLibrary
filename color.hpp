/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef COLOR_HEADER
#define	COLOR_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
struct EXPORT Color
{
    typedef ubyte VALUE;
    
    Color(ubyte R=0, ubyte G=0, ubyte B=0, ubyte A=0);
    Color(const Color&);
    ~Color();
    
    VALUE& Alpha();
    VALUE& Red();
    VALUE& Blue();
    VALUE& Green();

    const VALUE& Alpha() const;
    const VALUE& Red() const;
    const VALUE& Blue() const;
    const VALUE& Green() const;
        
    Color& Set(ubyte, ubyte, ubyte);
    Color& Set(ubyte, ubyte, ubyte, ubyte);
    
    Color& operator=(const Color&);
    
    boolean operator==(const Color&) const;
    boolean operator!=(const Color&) const;
    
    const size Capacity;
    VALUE Array[4];
};
        
END_WS_NAMESPACE

END_HEADER

#endif
