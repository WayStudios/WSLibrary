/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef GRAPHICSDEVICE_HEADER
#define GRAPHICSDEVICE_HEADER

#include <global.hpp>
#include <graphicscontext.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT GraphicsDevice
{
	UNCOPYABLE(GraphicsDevice)
	DECLARE_IMPLEMENTATION(GraphicsDevice)
public:
	GraphicsDevice();
	virtual ~GraphicsDevice();

	virtual GraphicsContext* getGraphicsContext() = 0;
};

END_WS_NAMESPACE

END_HEADER

#endif
