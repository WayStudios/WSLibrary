/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef RENDERER_HEADER
#define	RENDERER_HEADER

#include <global.hpp>
#include <point.hpp>
#include <line.hpp>
#include <triangle.hpp>
#include <quadrilateral.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class PixelBuffer;
class Pixmap;

class EXPORT Renderer
{    
    UNCOPYABLE(Renderer)
    DECLARE_IMPLEMENTATION(Renderer)
public:
    Renderer(PixelBuffer*);
    ~Renderer();

/*
    void RenderPoint(const Point2V&);
    void RenderLine(const Line2V&);
    void RenderTriangle(const Triangle2V&);
    void RenderQuadrilateral(const Quadrilateral2V&);
    void RenderPixmap(Pixmap*, const Point2V&);
*/
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
