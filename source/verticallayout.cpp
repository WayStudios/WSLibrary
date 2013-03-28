/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <verticallayout.hpp>
#include <verticallayoutimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

VerticalLayout::VerticalLayoutImplementation::VerticalLayoutImplementation() : layoutSpecific(0) {}

VerticalLayout::VerticalLayoutImplementation::~VerticalLayoutImplementation() {}

void VerticalLayout::VerticalLayoutImplementation::initialize(Layout* P_LAYOUT) {
	layoutSpecific = LayoutSpecific::fetch(P_LAYOUT);
}

void VerticalLayout::VerticalLayoutImplementation::destroy() {
	layoutSpecific = 0;
}

void VerticalLayout::VerticalLayoutImplementation::adjust() {
	if(layoutSpecific)
		if(!layoutSpecific->widgetList.empty() && layoutSpecific->parent)
		{
			UINTEGER W=layoutSpecific->parent->width();
			UINTEGER H=layoutSpecific->parent->height() / layoutSpecific->widgetList.total();
			UINTEGER Y=0;
			for(List<Widget*>::Iterator ITER = layoutSpecific->widgetList.begin(); ITER != layoutSpecific->widgetList.end(); ++ITER)
			{
				(*ITER)->show(0, Y, W, H);
				Y+=H;
			}
		}
}

void VerticalLayout::VerticalLayoutImplementation::append(Widget* P) {
	if(layoutSpecific)
		layoutSpecific->widgetList.append(P);
}

void VerticalLayout::VerticalLayoutImplementation::remove(Widget* P) {
	if(layoutSpecific)
		layoutSpecific->widgetList.remove(P);
}

VerticalLayout::VerticalLayout(Widget* PARENT):Layout(PARENT), implementation(0) {
	implementation = new VerticalLayoutImplementation;
	if(implementation)
		implementation->initialize(this);
}

VerticalLayout::~VerticalLayout() {
	if(implementation)
	{
		implementation->destroy();
		delete implementation;
	}
}

void VerticalLayout::adjust() {
	if(implementation)
		implementation->adjust();
}

void VerticalLayout::append(Widget* P) {
	if(implementation)
		implementation->append(P);
}

void VerticalLayout::remove(Widget* P) {
	if(implementation)
		implementation->remove(P);
}

END_WS_NAMESPACE

END_SOURCECODE
