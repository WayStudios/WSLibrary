/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef WINDOWIMPLEMENTATION_HEADER
#define WINDOWIMPLEMENTATION_HEADER

#include <window.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL Window::WindowImplementation
{
public:
	WindowImplementation();
	~WindowImplementation();

	void initialize(Widget*);
private:
	Widget* widget;
	WidgetSpecific* widgetSpecific;
};

END_WS_NAMESPACE

END_HEADER

#endif
