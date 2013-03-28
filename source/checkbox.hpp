/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef CHECKBOX_HEADER
#define CHECKBOX_HEADER

#include <widget.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT CheckBox:public Widget
{
	UNCOPYABLE(CheckBox)
	DECLARE_IMPLEMENTATION(CheckBox)
public:
	explicit CheckBox(Widget* PARENT=0);
	virtual ~CheckBox();
};

END_WS_NAMESPACE

END_HEADER

#endif
