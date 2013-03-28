/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <widget.hpp>
#include <widgetimpl.hpp>
#include <layout.hpp>

#include <guievent.hpp>
#include <renderevent.hpp>
#include <resizeevent.hpp>
#include <moveevent.hpp>
#include <inputevent.hpp>
#include <cursorevent.hpp>
#include <keyevent.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

Map<Widget*, WidgetSpecific*> WidgetSpecific::specificMap;

WidgetSpecific* WidgetSpecific::fetch(Widget* P_WIDGET)
{
	if(P_WIDGET)
	{
		Map<Widget*, WidgetSpecific*>::Iterator ITER(WidgetSpecific::specificMap.find(P_WIDGET));
		if(ITER!=WidgetSpecific::specificMap.end())
			return (*ITER).second;
	}
	return 0;
}

#if defined(WS_X11)

#endif

#if defined(WS_MSWINDOWS)

BOOLEAN WidgetSpecific::registered = false;

Map<HWND, WidgetSpecific*> WidgetSpecific::handleMap;

LRESULT CALLBACK Widget::WidgetImplementation::WindowProc(HWND H_WND, UINT I_MSG, WPARAM W_PARAM, LPARAM L_PARAM)
{
	switch(I_MSG)
	{
	case WM_NCCREATE:
	case WM_NCCALCSIZE:
	case WM_NCDESTROY:
	case WM_NCACTIVATE:
	case WM_GETMINMAXINFO:
		return DefWindowProc(H_WND, I_MSG, W_PARAM, L_PARAM);
		break;
	case WM_CREATE:
		CREATESTRUCT* P_STRUCT = reinterpret_cast<CREATESTRUCT*>(L_PARAM);
		if(P_STRUCT)
			if(P_STRUCT->lpCreateParams)
			{
				WidgetSpecific* widgetSpecific = reinterpret_cast<WidgetSpecific*>(P_STRUCT->lpCreateParams);
				widgetSpecific->hWnd = H_WND;
				WidgetSpecific::handleMap.append(widgetSpecific->hWnd, widgetSpecific);
				if(P_STRUCT->hwndParent)
					widgetSpecific->window=false;
				else
					widgetSpecific->window=true;
				widgetSpecific->width = P_STRUCT->cx;
				widgetSpecific->height = P_STRUCT->cy;
				widgetSpecific->x = P_STRUCT->x;
				widgetSpecific->y = P_STRUCT->y;
//				widgetSpecific->graphicsDeviceSpecific->graphicsContextSpecific->hDC = GetDC(widgetSpecific->hWnd);
				return 0;
			}
		return -1;
		break;
	}
	Map<HWND, WidgetSpecific*>::Iterator ITER = WidgetSpecific::handleMap.find(H_WND);
	if(ITER == WidgetSpecific::handleMap.end())
		return DefWindowProc(H_WND, I_MSG, W_PARAM, L_PARAM);
	else
	{
		WidgetSpecific* H_Specific=(*ITER).second;
		GUIEvent* H_Event = 0;
		Widget* H_Sender = H_Specific->widget;
		Widget* H_Receiver = H_Specific->widget;
		switch(I_MSG)
		{
		case WM_SHOWWINDOW:
			if(W_PARAM)
				H_Specific->visiable=true;
			else
				H_Specific->visiable=false;
		case WM_DESTROY:
			break;
		case WM_CLOSE:
			break;
		case WM_PAINT:
			H_Event = new RenderEvent();
			break;
/*		case WM_WINDOWPOSCHANGED: {
				WINDOWPOS* POS = reinterpret_cast<WINDOWPOS*>(L_PARAM);
				switch(POS->flags) {
				case SWP_NOMOVE:
					H_Specific->I_Width = POS->cx;
					H_Specific->I_Height = POS->cy;
					H_Event = new ResizeEvent(H_Specific->I_Width, H_Specific->I_Height);
					break;
				}
			}
			break;*/
		case WM_SIZE:
			H_Specific->width = LOWORD(L_PARAM);
			H_Specific->height = HIWORD(L_PARAM);
			//if(H_Specific->H_Control)
			//	MoveWindow(H_Specific->H_Control, 0, 0, H_Specific->I_Width, H_Specific->I_Height, true);
			H_Event = new ResizeEvent(H_Specific->width, H_Specific->height);
			break;
		case WM_MOVE:
			H_Specific->x = LOWORD(L_PARAM);
			H_Specific->y = HIWORD(L_PARAM);
			//if(H_Specific->H_Control)
			//	MoveWindow(H_Specific->H_Control, 0, 0, H_Specific->I_Width, H_Specific->I_Height, true);
			H_Event = new MoveEvent(H_Specific->x, H_Specific->y);
			break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_KEYDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_KEYUP:
			H_Event = new KeyEvent(Unknow, false);
			break;
		case WM_MOUSEMOVE:
			{
				CursorEvent E(LOWORD(L_PARAM), HIWORD(L_PARAM));
				H_Specific->widget->sendEvent(&E, H_Receiver, H_Sender);
				return 0;
			}
		default:
			return DefWindowProc(H_WND, I_MSG, W_PARAM, L_PARAM);
		}
		if(H_Event && H_Sender && H_Receiver)
		{
			H_Specific->widget->sendEvent(H_Event, H_Receiver, H_Sender);
			delete H_Event;
		}
	}
	return DefWindowProc(H_WND, I_MSG, W_PARAM, L_PARAM);
}

#endif

WidgetSpecific::WidgetSpecific(Widget* W):widget(W), layout(0), visiable(false), x(0), y(0), height(0), width(0), maximumHeight(0), maximumWidth(0), minimumHeight(0), minimumWidth(0)
#if defined(WS_MSWINDOWS)
										, hWnd(NULL)
										, hCtrl(NULL)
#endif
{
	WidgetSpecific::specificMap.append(widget, this);
}

WidgetSpecific::~WidgetSpecific()
{
	WidgetSpecific::specificMap.remove(widget);
}

Widget::WidgetImplementation::WidgetImplementation():widgetSpecific(0) {}

Widget::WidgetImplementation::~WidgetImplementation() {}

void Widget::WidgetImplementation::initialize(Widget* P_WIDGET)
{
	if(!widgetSpecific) {
		widgetSpecific=new WidgetSpecific(P_WIDGET);
		widgetSpecific->graphicsDeviceSpecific = GraphicsDeviceSpecific::fetch(static_cast<GraphicsDevice*>(P_WIDGET));
//		graphicsContext = new GraphicsContext();
//		widgetSpecific->graphicsDeviceSpecific->graphicsContextSpecific = GraphicsContextSpecific::fetch(graphicsContext);
	}
#if defined(WS_X11)
#elif defined(WS_MSWINDOWS)
	if(!WidgetSpecific::registered)
	{
		WNDCLASS CLASS_WIDGET;
		CLASS_WIDGET.style = CS_HREDRAW | CS_VREDRAW;
		CLASS_WIDGET.lpfnWndProc = &Widget::WidgetImplementation::WindowProc;
	//	CLASS_WIDGET.lpfnWndProc = &DefWindowProc;
		CLASS_WIDGET.cbWndExtra = NULL;
		CLASS_WIDGET.cbClsExtra = NULL;
		CLASS_WIDGET.hInstance = NULL;
		CLASS_WIDGET.hIcon = NULL;
		CLASS_WIDGET.hCursor = LoadCursor(NULL, IDC_ARROW);
		CLASS_WIDGET.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
		CLASS_WIDGET.lpszMenuName = NULL;
		CLASS_WIDGET.lpszClassName  = "WS_WIDGET";
		if(RegisterClass(&CLASS_WIDGET) == 0)
			DWORD ERR=GetLastError();
		WidgetSpecific::registered = true;
	}
	Widget* H_Parent=static_cast<Widget*>(P_WIDGET->getMaster());
	HWND HWND_Parent = 0;
	if(H_Parent)
		HWND_Parent = WidgetSpecific::fetch(H_Parent)->hWnd;
	if(HWND_Parent)
	{
		if(!(widgetSpecific->hWnd))
			widgetSpecific->hWnd=CreateWindowEx(WS_EX_COMPOSITED, "WS_WIDGET", "WS_WIDGET", WS_VISIBLE | WS_OVERLAPPED | WS_CHILD, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, HWND_Parent, NULL, NULL, static_cast<LPVOID>(widgetSpecific));
	}
	else
		if(!(widgetSpecific->hWnd))
			widgetSpecific->hWnd=CreateWindowEx(WS_EX_COMPOSITED, "WS_WIDGET", "WS_WIDGET", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, HWND_DESKTOP, NULL, NULL, static_cast<LPVOID>(widgetSpecific));
	DWORD ErN=GetLastError();
#endif
}

void Widget::WidgetImplementation::destroy()
{
	if(widgetSpecific) {
#if defined(WS_MSWINDOWS)
//		ReleaseDC(widgetSpecific->hWnd, widgetSpecific->graphicsDeviceSpecific->graphicsContextSpecific->hDC);
#endif
		delete widgetSpecific;
	}
	widgetSpecific = 0;
}

void Widget::WidgetImplementation::show()
{
	if(widgetSpecific)
	{
#if defined(WS_X11)
		if(widgetSpecific->xwindow)
		{
			XMapWindow(XOpenDisplay(NULL), widgetSpecific->xwindow);
		}
#elif defined(WS_MSWINDOWS)
		if(widgetSpecific->hWnd)
		{
//			WidgetSpecific::HandleMap.Append(H_Specific->H_Handle, H_Specific);
			ShowWindow(widgetSpecific->hWnd, SW_SHOW);
		}
#endif
	}
}

void Widget::WidgetImplementation::show(INTEGER X, INTEGER Y, UINTEGER W, UINTEGER H)
{
	if(widgetSpecific)
	{
#if defined(WS_X11)
#elif defined(WS_MSWINDOWS)
		if(widgetSpecific->hWnd)
		{
			if(!widgetSpecific->visiable)
				ShowWindow(widgetSpecific->hWnd, SW_SHOW);
			MoveWindow(widgetSpecific->hWnd, X, Y, W, H, TRUE);
			if(widgetSpecific->hCtrl)
				MoveWindow(widgetSpecific->hCtrl, 0, 0, W, H, TRUE);
		}
#endif
	}
}

void Widget::WidgetImplementation::hide()
{
	if(widgetSpecific)
	{
#if defined(WS_X11)
#elif defined(WS_MSWINDOWS)
//		if(!(H_Specific->H_Handle))
//			H_Specific->H_Handle=CreateWindow("WS_WIDGET", NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
		ShowWindow(widgetSpecific->hWnd, SW_HIDE);
#endif
	}
}

Layout* Widget::WidgetImplementation::getLayout() const {
	if(widgetSpecific)
		return widgetSpecific->layout;
	return 0;
}

void Widget::WidgetImplementation::setLayout(Layout* LAYOUT) {
	if(widgetSpecific)
		widgetSpecific->layout = LAYOUT;
}

INTEGER Widget::WidgetImplementation::x() const {
	if(widgetSpecific)
		return widgetSpecific->x;
	return 0;
}

INTEGER Widget::WidgetImplementation::y() const {
	if(widgetSpecific)
		return widgetSpecific->y;
	return 0;
}

UINTEGER Widget::WidgetImplementation::width() const {
	if(widgetSpecific)
		return widgetSpecific->width;
	return 0;
}

UINTEGER Widget::WidgetImplementation::height() const {
	if(widgetSpecific)
		return widgetSpecific->height;
	return 0;
}

void Widget::WidgetImplementation::move(INTEGER X, INTEGER Y) {
	if(widgetSpecific)
	{
#if defined(WS_MSWINDOWS)
		if(widgetSpecific->hWnd)
			MoveWindow(widgetSpecific->hWnd, X, Y, widgetSpecific->width, widgetSpecific->height, true);
#endif
	}
}

void Widget::WidgetImplementation::resize(UINTEGER WIDTH, UINTEGER HEIGHT) {
	if(widgetSpecific)
	{
#if defined(WS_MSWINDOWS)
		if(widgetSpecific->hWnd)
			MoveWindow(widgetSpecific->hWnd, widgetSpecific->x, widgetSpecific->y, WIDTH, HEIGHT, true);
		DWORD ERR=GetLastError();
#endif
	}
}

String Widget::WidgetImplementation::getTitle() const {
	if(widgetSpecific)
		return widgetSpecific->title;
	return String();
}

void Widget::WidgetImplementation::setTitle(const String& REF) {
	if(widgetSpecific)
	{
#if defined(WS_MSWINDOWS)
		widgetSpecific->title = REF;
		if(widgetSpecific->hWnd)
			SetWindowText(widgetSpecific->hWnd, widgetSpecific->title.cstring());
#endif
	}
}

#if defined(WS_MSWINDOWS)

void Widget::WidgetImplementation::renderControl() {
	//if(H_Specific)
	//	if(H_Specific->H_Control)
	//		UpdateWindow(H_Specific->H_Control);
}

#endif

Widget::Widget(Widget* PARENT):Object(static_cast<Object*>(PARENT)), GraphicsDevice(), implementation(0)
{
	implementation=new WidgetImplementation();
	if(implementation)
		implementation->initialize(this);
//	else
//		throw;
}

Widget::~Widget()
{
	if(implementation)
	{
		implementation->destroy();
		delete implementation;
	}
}

Widget* Widget::getParent() const{return static_cast<Widget*>(getMaster());}

BOOLEAN Widget::isVisible() const{return false;}

void Widget::show() {
	if(implementation)
		implementation->show();
}

void Widget::show(INTEGER X, INTEGER Y, UINTEGER W, UINTEGER H) {
	if(implementation)
		implementation->show(X, Y, W, H);
}

void Widget::hide() {
	if(implementation)
		implementation->hide();
}

String Widget::getTitle() const{
	if(implementation)
		return implementation->getTitle();
	return String();
}

void Widget::setTitle(const String& REF) {
	if(implementation)
		implementation->setTitle(REF);
}

Layout* Widget::getLayout() const {
	if(implementation)
		return implementation->getLayout();
	return 0;
}

void Widget::setLayout(Layout* LAYOUT) {
	if(implementation)
		implementation->setLayout(LAYOUT);
}

INTEGER Widget::x() const {
	if(implementation)
		return implementation->x();
	return 0;
}

INTEGER Widget::y() const {
	if(implementation)
		return implementation->y();
	return 0;
}

UINTEGER Widget::width() const {
	if(implementation)
		return implementation->width();
	return 0;
}

UINTEGER Widget::height() const {
	if(implementation)
		return implementation->height();
	return 0;
}

void Widget::move(INTEGER X, INTEGER Y) {
	if(implementation)
		implementation->move(X, Y);
}

void Widget::resize(UINTEGER W, UINTEGER H) {
	if(implementation)
		implementation->resize(W, H);
}

GraphicsContext* Widget::getGraphicsContext() {
	return 0;
}

void Widget::render() {}

void Widget::processEvent(Event* E)
{
	if(E)
	{
		if(E->type==WS_GUIEVENT)
			return processGUIEvent(static_cast<GUIEvent*>(E));
		return Object::processEvent(E);
	}
}

void Widget::processGUIEvent(GUIEvent* E)
{
	if(E)
		switch(E->EventType)
		{
		case GUIEvent::RenderEvent:
			return processRenderEvent(static_cast<RenderEvent*>(E));
			break;
		case GUIEvent::ResizeEvent:
			return processResizeEvent(static_cast<ResizeEvent*>(E));
			break;
		case GUIEvent::MoveEvent:
			return processMoveEvent(static_cast<MoveEvent*>(E));
			break;
		case GUIEvent::InputEvent:
			return processInputEvent(static_cast<InputEvent*>(E));
			break;
		}
}

void Widget::processRenderEvent(RenderEvent* E)
{
	if(E)
	{
#if defined(WS_MSWINDOWS)
		implementation->renderControl();
#endif
		return render();
	}
}

void Widget::processResizeEvent(ResizeEvent* E) {
	Layout* H_Layout = getLayout();
	if(H_Layout)
	{
		H_Layout->adjust();
	}
	else
	{
	}
}

void Widget::processMoveEvent(MoveEvent* E) {}

void Widget::processInputEvent(InputEvent* E)
{
	if(E)
		switch(E->device)
		{
		case InputEvent::Cursor:
			return processCursorEvent(static_cast<CursorEvent*>(E));
			break;
		case InputEvent::Key:
			return processKeyEvent(static_cast<KeyEvent*>(E));
			break;
		}
}

void Widget::processCursorEvent(CursorEvent* E) {}

void Widget::processKeyEvent(KeyEvent* E) {}

END_WS_NAMESPACE

END_SOURCECODE
