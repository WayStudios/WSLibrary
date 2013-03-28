/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef GRIDLAYOUT_HEADER
#define GRIDLAYOUT_HEADER

#include <layout.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT GridLayout:public Layout {
	UNCOPYABLE(GridLayout)
	DECLARE_IMPLEMENTATION(GridLayout)
public:
	explicit GridLayout(Widget* PARENT=0);
	~GridLayout();

	void Clear();
	void Append(Widget*);
	void Remove(Widget*);
};

END_WS_NAMESPACE

END_HEADER

#endif
