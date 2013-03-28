/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef GROUPBOX_HEADER
#define GROUPBOX_HEADER

#include <widget.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT GroupBox:public Widget
{
	UNCOPYABLE(GroupBox)
	DECLARE_IMPLEMENTATION(GroupBox)
public:
	explicit GroupBox(Widget* PARENT=0);
	virtual ~GroupBox();
};

END_WS_NAMESPACE

END_HEADER

#endif
