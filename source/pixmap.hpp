/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef PIXMAP_HEADER
#define	PIXMAP_HEADER

#include <pixelbuffer.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class EXPORT Pixmap:public PixelBuffer
{
    DECLARE_IMPLEMENTATION(Pixmap)
public:
    typedef UINTEGER TYPE;
    
    explicit Pixmap(UINTEGER W = 0, UINTEGER H = 0);
    Pixmap(const Pixmap&);
    ~Pixmap();
    
    BOOLEAN empty() const;
    
    SIZE width() const;
    SIZE height() const;
    
    SIZE capacity() const;
    
    TYPE& seek(SIZE);
    TYPE& seek(SIZE, SIZE);
    
    const TYPE& seek(SIZE) const;
    const TYPE& seek(SIZE, SIZE) const;
    
    const Pixmap& operator =(const Pixmap&);
    
    BOOLEAN operator ==(const Pixmap&) const;
    BOOLEAN operator !=(const Pixmap&) const;
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
