/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <widget.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT Window:public Widget
{
	UNCOPYABLE(Window)
	DECLARE_IMPLEMENTATION(Window);
public:
	explicit Window(Widget* PARENT=0);
	virtual ~Window();
};

END_WS_NAMESPACE

END_HEADER

#endif
