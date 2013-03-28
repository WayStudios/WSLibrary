/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef LABEL_HEADER
#define LABEL_HEADER
#include <widget.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT Label:public Widget
{
	UNCOPYABLE(Label)
	DECLARE_IMPLEMENTATION(Label)
public:
	explicit Label(Widget* PARENT=0);
	virtual ~Label();

	String Content() const;
	void SetContent(const String&);
};

END_WS_NAMESPACE

END_HEADER

#endif
