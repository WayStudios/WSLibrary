/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef GRAPHICSCONTEXTIMPLEMENTATION_HEADER
#define GRAPHICSCONTEXTIMPLEMENTATION_HEADER

#include <graphicscontext.hpp>
#include <map.hpp>
#if defined(API_MSWINDOWS)
#include <Windows.h>
#endif

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXTERN GraphicsContextSpecific {

	explicit GraphicsContextSpecific(GraphicsContext*);
	~GraphicsContextSpecific();

	static Map<GraphicsContext*, GraphicsContextSpecific*> specificMap;
	static GraphicsContextSpecific* fetch(GraphicsContext*);

	GraphicsContext* graphicsContext;

#if defined(API_X11)
	DC dc;
#elif defined(API_MSWINDOWS)
	HDC hDC;
#endif

	UNCOPYABLE(GraphicsContextSpecific)
};

class LOCAL GraphicsContext::GraphicsContextImplementation {
public:
	GraphicsContextImplementation();
	~GraphicsContextImplementation();

	void initialize(GraphicsContext*);
	void destroy();
	void save();
	void restore();

	GraphicsContextSpecific* graphicsContextSpecific;
};

END_WS_NAMESPACE

END_HEADER

#endif
