/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef HORIZONTALLAYOUT_HEADER
#define HORIZONTALLAYOUT_HEADER

#include <layout.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT HorizontalLayout : public Layout {
	UNCOPYABLE(HorizontalLayout)
	DECLARE_IMPLEMENTATION(HorizontalLayout)
public:
	explicit HorizontalLayout(Widget* PARENT);
	~HorizontalLayout();

	void adjust();

	void append(Widget*);
	void remove(Widget*);
};

END_WS_NAMESPACE

END_HEADER

#endif
