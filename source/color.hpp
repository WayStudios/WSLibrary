/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef COLOR_HEADER
#define	COLOR_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
struct EXPORT Color {
    typedef UBYTE TYPE;
    
    Color(UBYTE R=0, UBYTE G=0, UBYTE B=0, UBYTE A=0);
    Color(const Color&);
    ~Color();
    
    TYPE& alpha();
    TYPE& red();
    TYPE& blue();
    TYPE& green();

    const TYPE& alpha() const;
    const TYPE& red() const;
    const TYPE& blue() const;
    const TYPE& green() const;
        
    Color& set(UBYTE, UBYTE, UBYTE);
    Color& set(UBYTE, UBYTE, UBYTE, UBYTE);
    
    Color& operator =(const Color&);
    
    BOOLEAN operator==(const Color&) const;
    BOOLEAN operator!=(const Color&) const;
    
    const SIZE capacity;
    TYPE array[4];
};
        
END_WS_NAMESPACE

END_HEADER

#endif
