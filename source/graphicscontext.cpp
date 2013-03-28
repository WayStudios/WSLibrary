/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <graphicscontext.hpp>
#include <graphicscontextimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

Map<GraphicsContext*, GraphicsContextSpecific*> GraphicsContextSpecific::specificMap;

GraphicsContextSpecific* GraphicsContextSpecific::fetch(GraphicsContext* P) {
	if(P)
	{
		Map<GraphicsContext*, GraphicsContextSpecific*>::Iterator ITER(GraphicsContextSpecific::specificMap.find(P));
		if(ITER!=GraphicsContextSpecific::specificMap.end())
			return (*ITER).second;
	}
	return 0;
}

GraphicsContextSpecific::GraphicsContextSpecific(GraphicsContext* GC) : graphicsContext(GC) {
	GraphicsContextSpecific::specificMap.append(GC, this);
}

GraphicsContextSpecific::~GraphicsContextSpecific() {
	GraphicsContextSpecific::specificMap.remove(graphicsContext);
}

GraphicsContext::GraphicsContextImplementation::GraphicsContextImplementation() : graphicsContextSpecific(0) {
}

GraphicsContext::GraphicsContextImplementation::~GraphicsContextImplementation() {
}

void GraphicsContext::GraphicsContextImplementation::initialize(GraphicsContext* P) {
	graphicsContextSpecific = new GraphicsContextSpecific(P);
}

void GraphicsContext::GraphicsContextImplementation::destroy() {
	if(graphicsContextSpecific)
		delete graphicsContextSpecific;
}

GraphicsContext::GraphicsContext() : implementation(0) {
	implementation = new GraphicsContextImplementation();
	if(implementation)
		implementation->initialize(this);
}

GraphicsContext::~GraphicsContext() {
	if(implementation) {
		implementation->destroy();
		delete implementation;
	}
}

void GraphicsContext::save(){}

void GraphicsContext::restore(){}

//void GraphicsContext::setTransform(const Transformation&){}

END_WS_NAMESPACE

END_SOURCECODE
