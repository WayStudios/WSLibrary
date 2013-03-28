/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef HORIZONTALLAYOUTIMPLEMENTATION_HEADER
#define HORIZONTALLAYOUTIMPLEMENTATION_HEADER

#include <horizontallayout.hpp>
#include <layoutimpl.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL HorizontalLayout::HorizontalLayoutImplementation {
	UNCOPYABLE(HorizontalLayoutImplementation)
public:
	HorizontalLayoutImplementation();
	~HorizontalLayoutImplementation();

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
