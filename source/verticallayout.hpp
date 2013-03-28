/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef VERTICALLAYOUT_HEADER
#define VERTICALLAYOUT_HEADER

#include <layout.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT VerticalLayout:public Layout {
	UNCOPYABLE(VerticalLayout)
	DECLARE_IMPLEMENTATION(VerticalLayout)
public:
	explicit VerticalLayout(Widget* PARENT=0);
	~VerticalLayout();

	void adjust();

	void append(Widget*);
	void remove(Widget*);
};

END_WS_NAMESPACE

END_HEADER

#endif
