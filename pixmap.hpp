/*******************************************************************************
 * WayStudio Graphics Library
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
    typedef uinteger VALUE;
    
    explicit Pixmap(uinteger W=0, uinteger H=0);
    Pixmap(const Pixmap&);
    ~Pixmap();
    
    boolean Empty() const;
    
    size Width() const;
    size Height() const;
    
    size Capacity() const;
    
    VALUE& Seek(size);
    VALUE& Seek(size, size);
    
    const VALUE& Seek(size) const;
    const VALUE& Seek(size, size) const;
    
    const Pixmap& operator=(const Pixmap&);
    
    boolean operator==(const Pixmap&) const;
    boolean operator!=(const Pixmap&) const;
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
