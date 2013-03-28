/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <window.hpp>
#include <widgetimpl.hpp>
#include <windowimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

Window::WindowImplementation::WindowImplementation():H_Specific(0){}

Window::WindowImplementation::~WindowImplementation(){}

void Window::WindowImplementation::Initial(Widget* P_WIDGET)
{
	widgetSpecific=WidgetSpecific::Fetch(P_WIDGET);
	if(!H_Specific)
		H_Specific=new WidgetSpecific(P_WIDGET);
	if(H_Specific)
	{
#if defined(WS_X11)
#elif defined(WS_MSWINDOWS)
		WNDCLASS CLASS_WINDOW;
		CLASS_WINDOW.lpszClassName = "WS_WINDOW";
		RegisterClass(&CLASS_WINDOW);
		widgetSpecific->H_Handle=CreateWindow("WS_WINDOW", NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
#endif
	}
}

Window::Window(Widget* P_PARENT):Widget(P_PARENT), Implementation(0)
{
	Implementation = new WindowImplementation;
	if(Implementation)
		Implementation->Initial(this);
}

Window::~Window() {
	if(Implementation)
		delete Implementation;
}

END_WS_NAMESPACE

END_SOURCECODE
