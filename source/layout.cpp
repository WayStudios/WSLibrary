/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <layout.hpp>
#include <layoutimpl.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

Map<Layout*, LayoutSpecific*> LayoutSpecific::specificMap;

LayoutSpecific* LayoutSpecific::fetch(Layout* P_LAYOUT){
	if(P_LAYOUT)
	{
		Map<Layout*, LayoutSpecific*>::Iterator ITER(LayoutSpecific::specificMap.find(P_LAYOUT));
		if(ITER!=LayoutSpecific::specificMap.end())
			return (*ITER).second;
	}
	return 0;
}

LayoutSpecific::LayoutSpecific(Layout* H_LAYOUT) : layout(H_LAYOUT), parent(0) {
	LayoutSpecific::specificMap.append(H_LAYOUT, this);
}

LayoutSpecific::~LayoutSpecific() {
	LayoutSpecific::specificMap.remove(layout);
}

Layout::LayoutImplementation::LayoutImplementation() : layoutSpecific(0) {}

Layout::LayoutImplementation::~LayoutImplementation() {}

void Layout::LayoutImplementation::initial(Layout* LAYOUT) {
	layoutSpecific = new LayoutSpecific(LAYOUT);
}

void Layout::LayoutImplementation::cleanup() {
	if(layoutSpecific)
	{
		delete layoutSpecific;
		layoutSpecific=0;
	}
}

Layout::Layout(Widget* PARENT) : implementation(0) {
	implementation = new LayoutImplementation;
	if(implementation)
	{
		implementation->initial(this);
		implementation->layoutSpecific->parent=PARENT;
	}
	else
		throw;
}

Layout::~Layout() {
	if(implementation)
	{
		implementation->cleanup();
		delete implementation;

	}
}

void Layout::adjust() {}

END_SOURCECODE
