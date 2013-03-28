/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <horizontallayout.hpp>
#include <horizontallayoutimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

HorizontalLayout::HorizontalLayoutImplementation::HorizontalLayoutImplementation():layoutSpecific(0) {}

HorizontalLayout::HorizontalLayoutImplementation::~HorizontalLayoutImplementation() {}

void HorizontalLayout::HorizontalLayoutImplementation::initialize(Layout* P_LAYOUT) {
	layoutSpecific = LayoutSpecific::fetch(P_LAYOUT);
}

void HorizontalLayout::HorizontalLayoutImplementation::destroy() {
	layoutSpecific = 0;
}

void HorizontalLayout::HorizontalLayoutImplementation::adjust() {
	if(layoutSpecific)
		if(!layoutSpecific->widgetList.empty() && layoutSpecific->parent)
		{
			UINTEGER W=layoutSpecific->parent->width() / layoutSpecific->widgetList.total();
			UINTEGER H=layoutSpecific->parent->height();
			UINTEGER X=0;
			for(List<Widget*>::Iterator ITER = layoutSpecific->widgetList.begin(); ITER != layoutSpecific->widgetList.end(); ++ITER)
			{
				(*ITER)->show(X, 0, W, H);
				X+=W;
			}
		}
}

void HorizontalLayout::HorizontalLayoutImplementation::append(Widget* P) {
	if(layoutSpecific)
		layoutSpecific->widgetList.append(P);
}

void HorizontalLayout::HorizontalLayoutImplementation::remove(Widget* P) {
	if(layoutSpecific)
		layoutSpecific->widgetList.remove(P);
}

HorizontalLayout::HorizontalLayout(Widget* PARENT) : Layout(PARENT), implementation(0) {
	implementation = new HorizontalLayoutImplementation();
	if(implementation)
		implementation->initialize(this);
}

HorizontalLayout::~HorizontalLayout() {
	if(implementation)
	{
		implementation->destroy();
		delete implementation;
	}
}

void HorizontalLayout::adjust() {
	if(implementation)
		implementation->adjust();
}

void HorizontalLayout::append(Widget* P) {
	if(implementation)
		implementation->append(P);
}

void HorizontalLayout::remove(Widget* P) {
	if(implementation)
		implementation->remove(P);
}

END_WS_NAMESPACE

END_SOURCECODE
