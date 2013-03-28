/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <textedit.hpp>
#include <texteditimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

TextEdit::TextEditImplementation::TextEditImplementation(Widget* P):H_Widget(P){}

TextEdit::TextEditImplementation::~TextEditImplementation(){}

void TextEdit::TextEditImplementation::Initial()
{
	WidgetSpecific* H_Specific = WidgetSpecific::Fetch(H_Widget);
#if defined(WS_MSWINDOWS)
	H_Specific->H_Control = CreateWindow("EDIT", "WS_TEXTEDIT", WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE, 0, 0, 100, 20, H_Specific->H_Handle, NULL, NULL, static_cast<LPVOID>(H_Specific));
#endif
}

TextEdit::TextEdit(Widget* P_PARENT):Widget(P_PARENT), Implementation(0)
{
	Implementation=new TextEditImplementation(this);
	if(Implementation)
		Implementation->Initial();
	else
		throw;
}

TextEdit::~TextEdit()
{
	if(Implementation)
		delete Implementation;
}

END_WS_NAMESPACE

END_SOURCECODE
