/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef RADIOBUTTON_HEADER
#define RADIOBUTTON_HEADER

#include <widget.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT RadioButton:public Widget
{
	UNCOPYABLE(RadioButton)
	DECLARE_IMPLEMENTATION(RadioButton)
public:
	explicit RadioButton(Widget* PARENT=0);
	virtual ~RadioButton();
};

END_WS_NAMESPACE

END_HEADER

#endif
