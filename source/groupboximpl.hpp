/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef GROUPBOXIMPLEMENTATION_HEADER
#define GROUPBOXIMPLEMENTATION_HEADER

#include <groupbox.hpp>
#include <widgetimpl.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL GroupBox::GroupBoxImplementation
{
	UNCOPYABLE(GroupBoxImplementation)
public:
	explicit GroupBoxImplementation(Widget*);
	~GroupBoxImplementation();

	void initialize();

	Widget* H_Widget;
};

END_WS_NAMESPACE

END_HEADER

#endif
