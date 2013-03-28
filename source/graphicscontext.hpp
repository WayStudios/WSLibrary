/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef GRAPHICSCONTEXT_HEADER
#define GRAPHICSCONTEXT_HEADER

#include <global.hpp>
//#include <transformation.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT GraphicsContext {
	UNCOPYABLE(GraphicsContext)
	DECLARE_IMPLEMENTATION(GraphicsContext)
public:
	GraphicsContext();
	virtual ~GraphicsContext();

	virtual void save();
	virtual void restore();

//	virtual void setTransform(const Transformation&);
};

END_WS_NAMESPACE

END_HEADER

#endif
