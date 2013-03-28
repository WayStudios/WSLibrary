/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <lineedit.hpp>
#include <lineeditimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

LineEdit::LineEditImplementation::LineEditImplementation(Widget* P):H_Widget(P){}

LineEdit::LineEditImplementation::~LineEditImplementation(){}

void LineEdit::LineEditImplementation::Initial()
{
	WidgetSpecific* H_Specific = WidgetSpecific::Fetch(H_Widget);
#if defined(WS_MSWINDOWS)
	H_Specific->H_Control = CreateWindow("EDIT", "WS_LINEEDIT", WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_LEFT, 0, 0, 100, 20, H_Specific->H_Handle, NULL, NULL, static_cast<LPVOID>(H_Specific));
#endif
}

LineEdit::LineEdit(Widget* P_PARENT):Widget(P_PARENT), Implementation(0)
{
	Implementation=new LineEditImplementation(this);
	if(Implementation)
		Implementation->Initial();
	else
		throw;
}

LineEdit::~LineEdit()
{
	if(Implementation)
		delete Implementation;
}

END_WS_NAMESPACE

END_SOURCECODE
