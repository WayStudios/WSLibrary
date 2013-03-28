/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef STATUSBAR_HEADER
#define STATUSBAR_HEADER

#include <widget.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT StatusBar:public Widget
{
	UNCOPYABLE(StatusBar)
	DECLARE_IMPLEMENTATION(StatusBar)
public:
	explicit StatusBar(Widget* PARENT=0);
	virtual ~StatusBar();
};

END_WS_NAMESPACE

END_HEADER

#endif
