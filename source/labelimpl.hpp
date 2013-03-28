/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef LABELIMPLEMENTATION_HEADER
#define LABELIMPLEMENTATION_HEADER

#include <label.hpp>
#include <widgetimpl.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL Label::LabelImplementation
{
	UNCOPYABLE(LabelImplementation)
public:
	LabelImplementation();
	~LabelImplementation();

	void initialize(Widget*);
	
	String getContent() const;
	void setContent(const String&);

	WidgetSpecific* widgetSpecific;
	String content;
};

END_WS_NAMESPACE

END_HEADER

#endif
