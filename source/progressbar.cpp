/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <progressbar.hpp>
#include <progressbarimpl.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

ProgressBar::ProgressBarImplementation::ProgressBarImplementation(Widget* P):H_Widget(P){}

ProgressBar::ProgressBarImplementation::~ProgressBarImplementation(){}

void ProgressBar::ProgressBarImplementation::Initial()
{
	WidgetSpecific* H_Specific = WidgetSpecific::Fetch(H_Widget);
#if defined(WS_MSWINDOWS)
	H_Specific->H_Control = CreateWindowEx(NULL, PROGRESS_CLASS, "WS_PROGRESSBAR", WS_VISIBLE | WS_CHILD | PBS_SMOOTH | PBS_MARQUEE, 0, 0, 100, 20, H_Specific->H_Handle, NULL, NULL, static_cast<LPVOID>(H_Specific));
	SendMessage(H_Specific->H_Control, PBM_SETMARQUEE, true, 0);
#endif
}

ProgressBar::ProgressBar(Widget* PARENT):Widget(PARENT), Implementation(0) 
{
	Implementation=new ProgressBarImplementation(this);
	if(Implementation)
		Implementation->Initial();
	else
		throw;
}

ProgressBar::~ProgressBar()
{
	if(Implementation)
		delete Implementation;
}

END_WS_NAMESPACE

END_HEADER
