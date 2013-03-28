/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef LINEEDITIMPLEMENTATION_HEADER
#define LINEEDITIMPLEMENTATION_HEADER

#include <lineedit.hpp>
#include <widgetimpl.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL LineEdit::LineEditImplementation
{
	UNCOPYABLE(LineEditImplementation)
public:
	explicit LineEditImplementation(Widget*);
	~LineEditImplementation();

	void initialize();
	
	Widget* H_Widget;
};

END_WS_NAMESPACE

END_HEADER

#endif
