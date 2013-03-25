/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef CURSOR_HEADER
#define	CURSOR_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class EXPORT Cursor
{
public:
    Cursor();
    ~Cursor();
    
    const Pixmap& Pixmap() const;
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
