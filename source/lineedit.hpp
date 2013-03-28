/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef LINEEDIT_HEADER
#define LINEEDIT_HEADER

#include <widget.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT LineEdit:public Widget
{
	UNCOPYABLE(LineEdit)
	DECLARE_IMPLEMENTATION(LineEdit)
public:
	explicit LineEdit(Widget* PARENT=0);
	virtual ~LineEdit();
};

END_WS_NAMESPACE

END_HEADER

#endif
