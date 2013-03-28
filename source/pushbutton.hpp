/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef PUSHBUTTON_HEADER
#define PUSHBUTTON_HEADER

#include <widget.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT PushButton:public Widget
{
	UNCOPYABLE(PushButton)
	DECLARE_IMPLEMENTATION(PushButton)
public:
	explicit PushButton(Widget* PARENT=0);
	virtual ~PushButton();
};

END_WS_NAMESPACE

END_HEADER

#endif
