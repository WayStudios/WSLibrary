/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <label.hpp>
#include <labelimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

Label::LabelImplementation::LabelImplementation():H_Specific(0) {}

Label::LabelImplementation::~LabelImplementation() {}

void Label::LabelImplementation::Initial(Widget* P_WIDGET) {
	H_Specific = WidgetSpecific::Fetch(P_WIDGET);
#if defined(WS_MSWINDOWS)
	H_Specific->H_Control = CreateWindow("STATIC", "WS_LABEL", WS_VISIBLE | WS_CHILD | SS_LEFT, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, H_Specific->H_Handle, NULL, NULL, static_cast<LPVOID>(H_Specific));
#endif
}

String Label::LabelImplementation::Content() const{return STR_Content;}

void Label::LabelImplementation::SetContent(const String& REF) {
	STR_Content = REF;
#if defined(WS_MSWINDOWS)
	SetWindowText(H_Specific->H_Control, STR_Content.CString());
#endif
}

Label::Label(Widget* P_PARENT):Widget(P_PARENT), Implementation(0)
{
	Implementation=new LabelImplementation();
	if(Implementation)
		Implementation->Initial(static_cast<Widget*>(this));
	else
		throw;
}

Label::~Label()
{
	if(Implementation)
		delete Implementation;
}

String Label::Content() const{return Implementation->Content();}

void Label::SetContent(const String& REF){Implementation->SetContent(REF);}

END_WS_NAMESPACE

END_SOURCECODE
