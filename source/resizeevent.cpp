/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <resizeevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

ResizeEvent::ResizeEvent(INTEGER W, INTEGER H):GUIEvent(GUIEvent::ResizeEvent), width(W), height(H){}

ResizeEvent::~ResizeEvent(){}

END_SOURCECODE
