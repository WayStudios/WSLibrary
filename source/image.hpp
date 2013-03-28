/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef IMAGE_HEADER
#define	IMAGE_HEADER

#include <graphicsdevice.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
//Image class is a set of multi image layers
//Image may contain ImageLayer class
        
class EXPORT Image : public GraphicsDevice
{
public:
    class Layer;
    
    Image();
    ~Image();
    
    Layer* create();
    Image& remove(Layer*);
    Image& remove(SIZE);
    
    Pixmap pixmap() const;
    
    //ImageLayer* TopLayer();
    //ImageLayer* BottomLayer();
    //ImageLayer* CreateLayer();
    //Image& RemoveLayer(ImageLayer*);
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
