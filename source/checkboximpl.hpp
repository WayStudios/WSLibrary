/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef CHECKBOXIMPLEMENTATION_HEADER
#define CHECKBOXIMPLEMENTATION_HEADER

#include <checkbox.hpp>
#include <widgetimpl.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL CheckBox::CheckBoxImplementation
{
	UNCOPYABLE(CheckBoxImplementation)
public:
	explicit CheckBoxImplementation(Widget*);
	~CheckBoxImplementation();

	void initialize(); //BS_CHECKBOX

	Widget* H_Widget;
};

END_WS_NAMESPACE

END_HEADER

#endif
