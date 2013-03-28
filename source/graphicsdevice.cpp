/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <graphicsdevice.hpp>
#include <graphicsdeviceimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

Map<GraphicsDevice*, GraphicsDeviceSpecific*> GraphicsDeviceSpecific::specificMap;

GraphicsDeviceSpecific* GraphicsDeviceSpecific::fetch(GraphicsDevice* P_GRAPHICSDEVICE)
{
	if(P_GRAPHICSDEVICE)
	{
		Map<GraphicsDevice*, GraphicsDeviceSpecific*>::Iterator ITER(GraphicsDeviceSpecific::specificMap.find(P_GRAPHICSDEVICE));
		if(ITER!=GraphicsDeviceSpecific::specificMap.end())
			return (*ITER).second;
	}
	return 0;
}

GraphicsDeviceSpecific::GraphicsDeviceSpecific(GraphicsDevice* GD):graphicsDevice(GD),
																   //graphicsContextSpecific(0),
																   width(0), height(0) {
	GraphicsDeviceSpecific::specificMap.append(GD, this);
}

GraphicsDeviceSpecific::~GraphicsDeviceSpecific(){}

GraphicsDevice::GraphicsDeviceImplementation::GraphicsDeviceImplementation():graphicsDeviceSpecific(0){}

GraphicsDevice::GraphicsDeviceImplementation::~GraphicsDeviceImplementation(){}

void GraphicsDevice::GraphicsDeviceImplementation::initialize(GraphicsDevice* P) {
	if(P) {
		graphicsDeviceSpecific = new GraphicsDeviceSpecific(P);
	}
}

void GraphicsDevice::GraphicsDeviceImplementation::destroy() {
	if(graphicsDeviceSpecific) {
		delete graphicsDeviceSpecific;
		graphicsDeviceSpecific = 0;
	}
}

GraphicsDevice::GraphicsDevice() : implementation(0)
{
	implementation=new GraphicsDeviceImplementation;
	if(implementation)
		implementation->initialize(this);
}

GraphicsDevice::~GraphicsDevice()
{
	if(implementation) {
		implementation->destroy();
		delete implementation;
	}
}

END_WS_NAMESPACE

END_SOURCECODE
