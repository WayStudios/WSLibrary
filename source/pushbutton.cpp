/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <pushbutton.hpp>
#include <pushbuttonimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

PushButton::PushButtonImplementation::PushButtonImplementation(Widget* P):H_Widget(P) {}

PushButton::PushButtonImplementation::~PushButtonImplementation() {}

void PushButton::PushButtonImplementation::Initial() {
	WidgetSpecific* H_Specific = WidgetSpecific::Fetch(H_Widget);
#if defined(WS_MSWINDOWS)
	H_Specific->H_Control = CreateWindow("BUTTON", "WS_BUTTON", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, H_Specific->H_Handle, NULL, NULL, static_cast<LPVOID>(H_Specific));
#endif
}

PushButton::PushButton(Widget* P_PARENT):Widget(P_PARENT), Implementation(0)
{
	Implementation=new PushButtonImplementation(this);
	if(Implementation)
		Implementation->Initial();
	else
		throw;
}

PushButton::~PushButton()
{
	if(Implementation)
		delete Implementation;
}

END_WS_NAMESPACE

END_SOURCECODE
