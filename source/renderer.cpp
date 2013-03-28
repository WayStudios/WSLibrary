/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <renderer.hpp>
#include <rendererimpl.hpp>
//#include <pixelbuffer.hpp>
#include <graphicsdevice.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE

Renderer::RendererImplementation::RendererImplementation(){}

Renderer::RendererImplementation::~RendererImplementation(){}
        
Renderer::Renderer(GraphicsDevice*, Object* OBJ) : Object(OBJ), implementation(0) {
	implementation=new RendererImplementation;
}

Renderer::~Renderer() {
    if(implementation)
        delete implementation;
}

GraphicsDevice* Renderer::GetGraphicsDevice() const {
	return 0;
}

void Renderer::SetGraphicsDevice(GraphicsDevice* GD) {
}

END_SOURCECODE
