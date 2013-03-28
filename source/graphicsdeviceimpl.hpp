/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef GRAPHICSDEVICEIMPLEMENTATION_HEADER
#define GRAPHICSDEVICEIMPLEMENTATION_HEADER

#include <graphicsdevice.hpp>
#include <graphicscontextimpl.hpp>
#include <map.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXTERN GraphicsDeviceSpecific {
	explicit GraphicsDeviceSpecific(GraphicsDevice*);
	~GraphicsDeviceSpecific();

	static Map<GraphicsDevice*, GraphicsDeviceSpecific*> specificMap;
	static GraphicsDeviceSpecific* fetch(GraphicsDevice*);

	GraphicsDevice* graphicsDevice;
	UINTEGER height;
	UINTEGER width;

	UNCOPYABLE(GraphicsDeviceSpecific)
};

class LOCAL GraphicsDevice::GraphicsDeviceImplementation {
	UNCOPYABLE(GraphicsDeviceImplementation)
public:
	GraphicsDeviceImplementation();
	~GraphicsDeviceImplementation();

	void initialize(GraphicsDevice*);
	void destroy();

	GraphicsDeviceSpecific* graphicsDeviceSpecific;
};

END_WS_NAMESPACE

END_HEADER

#endif
