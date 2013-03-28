/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef TEXTEDITIMPLEMENTATION_HEADER
#define TEXTEDITIMPLEMENTATION_HEADER

#include <textedit.hpp>
#include <widgetimpl.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL TextEdit::TextEditImplementation
{
	UNCOPYABLE(TextEditImplementation)
public:
	explicit TextEditImplementation(Widget*);
	~TextEditImplementation();

	void Initial();
	
	Widget* H_Widget;
};

END_WS_NAMESPACE

END_HEADER

#endif
