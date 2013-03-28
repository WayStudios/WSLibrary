/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef RADIOBUTTONIMPLEMENTATION_HEADER
#define RADIOBUTTONIMPLEMENTATION_HEADER

#include <radiobutton.hpp>
#include <widgetimpl.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL RadioButton::RadioButtonImplementation
{
	UNCOPYABLE(RadioButtonImplementation)
public:
	explicit RadioButtonImplementation(Widget*);
	~RadioButtonImplementation();

	void initialize(); //BS_RADIOBUTTON

	Widget* H_Widget;
};

END_WS_NAMESPACE

END_HEADER

#endif
