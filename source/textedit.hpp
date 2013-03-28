/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef TEXTEDIT_HEADER
#define TEXTEDIT_HEADER

#include <widget.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT TextEdit:public Widget
{
	UNCOPYABLE(TextEdit)
	DECLARE_IMPLEMENTATION(TextEdit)
public:
	explicit TextEdit(Widget* PARENT=0);
	virtual ~TextEdit();
};

END_WS_NAMESPACE

END_HEADER

#endif
