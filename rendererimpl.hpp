/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef RENDERERIMPLEMENTATION_HEADER
#define	RENDERERIMPLEMENTATION_HEADER

#include <renderer.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE

struct LOCAL RendererSpecific
{
    RendererSpecific(Renderer*);
    
    Renderer* H_Renderer;
};
        
class LOCAL Renderer::RendererImplementation
{
    UNCOPYABLE(RendererImplementation)
public:
    RendererImplementation();
    ~RendererImplementation();
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
