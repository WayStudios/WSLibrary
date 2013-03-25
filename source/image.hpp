/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef IMAGE_HEADER
#define	IMAGE_HEADER

#include <global.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
//Image class is a set of multi image layers
//Image may contain ImageLayer class
        
class EXPORT Image
{
public:
    class Layer;
    
    Image();
    ~Image();
    
    Layer* Create();
    Image& Remove(Layer*);
    Image& Remove(size);
    
    Pixmap Pixmap() const;
    
    //ImageLayer* TopLayer();
    //ImageLayer* BottomLayer();
    //ImageLayer* CreateLayer();
    //Image& RemoveLayer(ImageLayer*);
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
