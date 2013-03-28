/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef WIDGETIMPLEMENTATION_HEADER
#define WIDGETIMPLEMENTATION_HEADER

#include <widget.hpp>
#include <graphicsdeviceimpl.hpp>
#include <map.hpp>
#if defined(WS_X11)
#elif defined(WS_MSWINDOWS)
#include <Windows.h>
#include <CommCtrl.h>
#endif

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXTERN WidgetSpecific
{
	explicit WidgetSpecific(Widget*);
	~WidgetSpecific();

	static Map<Widget*, WidgetSpecific*> specificMap;
	static WidgetSpecific* fetch(Widget*);

	Widget* widget;
//	Widget* H_Parent;
	Layout* layout;
	GraphicsDeviceSpecific* graphicsDeviceSpecific;
	BOOLEAN visiable;
	BOOLEAN window;
	INTEGER x;
	INTEGER y;
	UINTEGER height;
	UINTEGER width;
	UINTEGER maximumHeight;
	UINTEGER maximumWidth;
	UINTEGER minimumHeight;
	UINTEGER minimumWidth;
	String title;
#if defined(WS_X11)
	Window xwindow;
#elif defined(WS_MSWINDOWS)
	static BOOLEAN registered;
	HWND hWnd;
	HWND hCtrl;
	static Map<HWND, WidgetSpecific*> handleMap;
#endif
};

class LOCAL Widget::WidgetImplementation
{
public:
	WidgetImplementation();
	~WidgetImplementation();

	void initialize(Widget*);
	void destroy();

	void show();
	void show(INTEGER X, INTEGER Y, UINTEGER W, UINTEGER H);
	void hide();

	Layout* getLayout() const;
	void setLayout(Layout*);

	INTEGER x() const;
	INTEGER y() const;

	UINTEGER width() const;
	UINTEGER height() const;

	void move(INTEGER, INTEGER);
	void resize(UINTEGER, UINTEGER);

	String getTitle() const;
	void setTitle(const String&);

#if defined(WS_MSWINDOWS)
	static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
	void renderControl();
#endif

	WidgetSpecific* widgetSpecific;
	GraphicsContext* graphicsContext;
};

END_WS_NAMESPACE

END_HEADER

#endif
