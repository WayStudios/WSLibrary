/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <renderer.hpp>
#include <rendererimpl.hpp>
#include <pixelbuffer.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE

Renderer::RendererImplementation::RendererImplementation(){}

Renderer::RendererImplementation::~RendererImplementation(){}
        
Renderer::Renderer(PixelBuffer*):Implementation(0){}

Renderer::~Renderer()
{
    if(Implementation)
        delete Implementation;
}

END_SOURCECODE
