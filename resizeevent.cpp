/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <resizeevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

ResizeEvent::ResizeEvent(integer W, integer H):GUIEvent(GUIEvent::ResizeEvent), Size(W, H){}

ResizeEvent::ResizeEvent(const Rectangle& RECT):GUIEvent(GUIEvent::ResizeEvent), Size(RECT){}

ResizeEvent::~ResizeEvent(){}

END_SOURCECODE
