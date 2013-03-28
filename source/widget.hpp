/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef WIDGET_HEADER
#define WIDGET_HEADER

#include <object.hpp>
#include <graphicsdevice.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class Layout;
class Desktop;

struct GUIEvent;
struct RenderEvent;
struct ResizeEvent;
struct MoveEvent;
struct InputEvent;
struct CursorEvent;
struct KeyEvent;

class EXPORT Widget : public Object, public GraphicsDevice
{
	UNCOPYABLE(Widget)
	DECLARE_IMPLEMENTATION(Widget)
public:
	explicit Widget(Widget* PARENT=0);
	virtual ~Widget();

	Desktop* getDesktop() const;

	Widget* getWindow() const;
	Widget* getParent() const;

	BOOLEAN isVisible() const;

	void show();
	void show(INTEGER x, INTEGER Y, UINTEGER W, UINTEGER H);
	void hide();

	UINTEGER getMaximumHeight() const;
	UINTEGER getMaximumWidth() const;

	void setMaximumSize(UINTEGER, UINTEGER);

	UINTEGER getMinimumHeight() const;
	UINTEGER getMinimumWidth() const;

	void setMinimumSize(UINTEGER, UINTEGER);

	String getTitle() const;
	void setTitle(const String&);

	Layout* getLayout() const;
	void setLayout(Layout*);

	INTEGER x() const;
	INTEGER y() const;

	UINTEGER width() const;
	UINTEGER height() const;

	void move(INTEGER, INTEGER);
	void resize(UINTEGER, UINTEGER);

	GraphicsContext* getGraphicsContext();

	virtual void render();
protected:
	virtual void processEvent(Event*);
	virtual void processGUIEvent(GUIEvent*);
	virtual void processRenderEvent(RenderEvent*);
	virtual void processResizeEvent(ResizeEvent*);
	virtual void processMoveEvent(MoveEvent*);
	virtual void processInputEvent(InputEvent*);
	virtual void processCursorEvent(CursorEvent*);
	virtual void processKeyEvent(KeyEvent*);
};

END_WS_NAMESPACE

END_HEADER

#endif
