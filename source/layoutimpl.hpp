/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef LAYOUTIMPLEMENTATION_HEADER
#define LAYOUTIMPLEMENTATION_HEADER

#include <layout.hpp>
#include <widget.hpp>
#include <list.hpp>
#include <map.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct LOCAL LayoutSpecific {
	explicit LayoutSpecific(Layout*);
	~LayoutSpecific();

	static Map<Layout*, LayoutSpecific*> specificMap;
	static LayoutSpecific* fetch(Layout*);

	Layout* layout;
	Widget* parent;
	List<Widget*> widgetList;

	UNCOPYABLE(LayoutSpecific)
};

class LOCAL Layout::LayoutImplementation {
	UNCOPYABLE(LayoutImplementation)
public:
	LayoutImplementation();
	~LayoutImplementation();

	void initial(Layout*);
	void cleanup();

	LayoutSpecific* layoutSpecific;
};

END_WS_NAMESPACE

END_HEADER

#endif
