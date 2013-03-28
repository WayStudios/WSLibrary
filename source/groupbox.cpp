/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <groupbox.hpp>
#include <groupboximpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

GroupBox::GroupBoxImplementation::GroupBoxImplementation(Widget* P):H_Widget(P) {}

GroupBox::GroupBoxImplementation::~GroupBoxImplementation() {}

void GroupBox::GroupBoxImplementation::Initial() {
	WidgetSpecific* H_Specific = WidgetSpecific::Fetch(H_Widget);
#if defined(WS_MSWINDOWS)
	H_Specific->H_Control = CreateWindow("BUTTON", "WS_BUTTON", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 0, 0, 100, 20, H_Specific->H_Handle, NULL, NULL, static_cast<LPVOID>(H_Specific));
#endif
}

GroupBox::GroupBox(Widget* P_PARENT):Widget(P_PARENT), Implementation(0)
{
	Implementation=new GroupBoxImplementation(this);
	if(Implementation)
		Implementation->Initial();
	else
		throw;
}

GroupBox::~GroupBox()
{
	if(Implementation)
		delete Implementation;
}

END_WS_NAMESPACE

END_SOURCECODE
