/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <widget.hpp>
#include <widgetimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

Map<Widget*, WidgetSpecific*> WidgetSpecific::SpecificMap;

#if defined(WS_X11)
#elif defined(WS_MSWINDOWS)
Map<HWND, WidgetSpecific*> WidgetSpecific::WindowMap;

LRESULT CALLBACK Widget::WidgetImplementation::ProcessWindowEvent(HWND H_WND, UINT N_MSG, WPARAM W_PARAM, LPARAM L_PARAM)
{
//	Map<HWND, WidgetSpecific*>::Iterator ITER=WidgetSpecific::WindowMap.Find(H_WND);
//	if(ITER!=WidgetSpecific::WindowMap.End())
//	{
		switch(N_MSG)
		{
//window re-render require
//		case WM_PAINT:
//			break;
//destroyed window notification
//		case WM_DESTROY:
//			break;
//move window require
//		case WM_MOVING:
//			break;
//moved window notification:
//		case WM_MOVE:
//			break;
//resize window require:
//		case WM_SIZING:
//			break;
//resized window notification:
//		case WM_SIZE:
//			break;
//mouse moves
//		case WM_MOUSEMOVE:
//			break;
//mouse leaves
//		case WM_MOUSELEAVE:
//			break;
//close window require
//		case WM_CLOSE:
//			break;
		default:
			return DefWindowProc(H_WND, N_MSG, W_PARAM, L_PARAM);
		}
//	}
	return 0;
}
#endif

WidgetSpecific::WidgetSpecific(Widget* H_SELF):H_Widget(0), H_Pixmap(0), B_Window(false), B_Visible(false), W_Rect(0, 0), H_Root(0), H_Child(0){SpecificMap.Append(H_SELF, this);}

WidgetSpecific::~WidgetSpecific(){SpecificMap.Remove(H_Widget);}

Widget::WidgetImplementation::WidgetImplementation():Specific(0){}

Widget::WidgetImplementation::~WidgetImplementation(){}

void Widget::WidgetImplementation::Show()
{
	if(Specific)
	{
		if(!Specific->B_Visible)
		{
//			if(!Specific->H_Root && !Specific->B_Window)
//			{
				Specific->B_Window=true;
#if defined(WS_MSWINDOWS)
				WNDCLASS CLS_WND;
				CLS_WND.style		= CS_HREDRAW | CS_VREDRAW;
				CLS_WND.lpfnWndProc	= &Widget::WidgetImplementation::ProcessWindowEvent;
				CLS_WND.cbClsExtra	= NULL;
				CLS_WND.cbWndExtra	= NULL;
				CLS_WND.hInstance	= NULL;
				CLS_WND.hIcon		= NULL;
				CLS_WND.hCursor		= LoadCursor(NULL, IDC_ARROW);
				CLS_WND.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
				CLS_WND.lpszMenuName = NULL;
				CLS_WND.lpszClassName = "WSGUIWINDOW";
				RegisterClass(&CLS_WND);
				Specific->H_Window=CreateWindowEx(WS_EX_COMPOSITED,
												  "WSGUIWINDOW",
												  Specific->STR_Title.CString(),
												  WS_OVERLAPPEDWINDOW,
												  CW_USEDEFAULT, 0,
												  CW_USEDEFAULT, 0,
												  NULL, NULL, NULL, NULL);
				WidgetSpecific::WindowMap.Append(Specific->H_Window, Specific);
#endif
//			}
			if(Specific->B_Window)
			{
#if defined(WS_MSWINDOWS)
				ShowWindow(Specific->H_Window, SW_SHOWNORMAL);
				UpdateWindow(Specific->H_Window);
#endif
			}
			Specific->B_Visible=true;
		}
	}
}

void Widget::WidgetImplementation::Hide()
{
	if(Specific)
	{
		if(Specific->B_Visible)
		{
			if(Specific->B_Window)
			{
#if defined(WS_MSWINDOWS)
				CloseWindow(Specific->H_Window);
#endif
			}
			Specific->B_Visible=false;
		}
	}
}

void Widget::WidgetImplementation::Close()
{
	if(Specific)
	{
		if(Specific->B_Visible)
		{
//			Hide();
#if defined(WS_MSWINDOWS)
			CloseWindow(Specific->H_Window);
#endif
			Specific->B_Visible=false;
		}
	}
}

void Widget::WidgetImplementation::Resize(integer W, integer H)
{
	if(Specific)
	{
	}
}
        
Widget::Widget(Object* OBJ):Object(OBJ), Implementation(0)
{
	Implementation=new WidgetImplementation;
	if(Implementation)
	{
		Implementation->Specific=new WidgetSpecific(this);
		if(Implementation->Specific)
			Implementation->Specific->STR_Title=String("Untitle");
	}
}

Widget::Widget(Widget* PARENT):Object(static_cast<Object*>(PARENT)), Implementation(0)
{
	Implementation=new WidgetImplementation;
	if(Implementation)
	{
		Implementation->Specific=new WidgetSpecific(this);
		if(Implementation->Specific)
			Implementation->Specific->STR_Title=String("Untitle");
	}
}

Widget::Widget(const String& STR, Widget* PARENT):Object(static_cast<Object*>(PARENT)), Implementation(0)
{
	Implementation=new WidgetImplementation;
	if(Implementation)
	{
		Implementation->Specific=new WidgetSpecific(this);
		if(Implementation->Specific)
			Implementation->Specific->STR_Title=STR;
	}
}

Widget::~Widget()
{
	Close();
	if(Implementation)
	{
		if(Implementation->Specific)
			delete Implementation->Specific;
		delete Implementation;
	}
}

void Widget::Show()
{
	if(Implementation)
		Implementation->Show();
}

void Widget::Hide()
{
	if(Implementation)
		Implementation->Hide();
}

void Widget::Close()
{
	if(Implementation)
		Implementation->Close();
}

void Widget::Render(){}

void Widget::ProcessEvent(Event*){}

void Widget::ProcessGUIEvent(GUIEvent*){}

END_WS_NAMESPACE

END_SOURCECODE
