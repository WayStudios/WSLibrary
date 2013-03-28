/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef PUSHBUTTONIMPLEMENTATION_HEADER
#define PUSHBUTTONIMPLEMENTATION_HEADER

#include <pushbutton.hpp>
#include <widgetimpl.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL PushButton::PushButtonImplementation
{
	UNCOPYABLE(PushButtonImplementation)
public:
	explicit PushButtonImplementation(Widget*);
	~PushButtonImplementation();

	void initialize();
	
	Widget* H_Widget;
};

END_WS_NAMESPACE

END_HEADER

#endif
