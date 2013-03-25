/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <window.hpp>
#include <windowimpl.hpp>

BEGIN_SOURCECODE
        
USING_WS_NAMESPACE
        
Window::Window(Object* OBJ):Widget(OBJ)
{
	Map<Widget*, WidgetSpecific*>::Iterator ITER=WidgetSpecific::SpecificMap.Find(static_cast<Widget*>(this));
	if(ITER!=WidgetSpecific::SpecificMap.End())
		((*ITER).Second)->B_Window=true;
}

Window::Window(Widget* PARENT):Widget(PARENT)
{
	Map<Widget*, WidgetSpecific*>::Iterator ITER=WidgetSpecific::SpecificMap.Find(static_cast<Widget*>(this));
	if(ITER!=WidgetSpecific::SpecificMap.End())
		((*ITER).Second)->B_Window=true;
}

Window::Window(const String& STR, Widget* PARENT):Widget(STR, PARENT)
{
	Map<Widget*, WidgetSpecific*>::Iterator ITER=WidgetSpecific::SpecificMap.Find(static_cast<Widget*>(this));
	if(ITER!=WidgetSpecific::SpecificMap.End())
		((*ITER).Second)->B_Window=true;
}

Window::~Window(){}
        
END_SOURCECODE
