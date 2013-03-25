/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef WIDGETIMPLEMENTATION_HEADER
#define	WIDGETIMPLEMENTATION_HEADER
#include <widget.hpp>
#include <map.hpp>
#include <rectangle.hpp>
#include <pixmap.hpp>
#if defined(WS_X11)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#elif defined(API_MSWINDOWS) && defined(WS_MSWINDOWS)
#include <windows.h>
#endif

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
struct LOCAL WidgetSpecific
{
    explicit WidgetSpecific(Widget*);
    ~WidgetSpecific();

	static Map<Widget*, WidgetSpecific*> SpecificMap;
    
    Widget* H_Widget;
    Pixmap* H_Pixmap;
    String STR_Title;
    boolean B_Window;
    boolean B_Visible;
    Rectangle W_Rect;
    WidgetSpecific* H_Root;
    WidgetSpecific* H_Child;
	//List<WidgetSpecific*> LST_Children;
#if defined(WS_X11)
	Window H_Window;
	integer H_Screen;
#elif defined(WS_MSWINDOWS)
	HWND H_Window;
	static Map<HWND, WidgetSpecific*> WindowMap;
#endif
};

class LOCAL Widget::WidgetImplementation
{
    UNCOPYABLE(WidgetImplementation)
public:
    WidgetImplementation();
    ~WidgetImplementation();

	void Show();
	void Hide();
	void Close();

	void Resize(integer, integer);

#if defined(WS_X11)
#elif defined(WS_MSWINDOWS)
	static LRESULT CALLBACK ProcessWindowEvent(HWND, UINT, WPARAM, LPARAM);
#endif
    
    WidgetSpecific* Specific;
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
