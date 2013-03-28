/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef RENDERER_HEADER
#define	RENDERER_HEADER

#include <object.hpp>
#include <graphicsdevice.hpp>
#include <point.hpp>
#include <line.hpp>
#include <triangle.hpp>
#include <quadrilateral.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class Pixmap;

class EXPORT Renderer:public Object
{    
    UNCOPYABLE(Renderer)
    DECLARE_IMPLEMENTATION(Renderer)
public:
    explicit Renderer(GraphicsDevice*, Object* OBJ = 0);
    ~Renderer();

	GraphicsDevice* GetGraphicsDevice() const;
	void SetGraphicsDevice(GraphicsDevice*);

/*
	boolean Begin();
	boolean End();

	void Point();
	void Line();
	void Triangle();
	void Quadrilateral();
	void Pixmap();

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
