/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef VERTICALLAYOUTIMPLEMENTATION_HEADER
#define VERTICALLAYOUTIMPLEMENTATION_HEADER

#include <verticallayout.hpp>
#include <layoutimpl.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL VerticalLayout::VerticalLayoutImplementation {
public:
	VerticalLayoutImplementation();
	~VerticalLayoutImplementation();

	void initialize(Layout*);
	void destroy();

	void adjust();

	void append(Widget*);
	void remove(Widget*);

	LayoutSpecific* layoutSpecific;
};

END_WS_NAMESPACE

END_HEADER

#endif
