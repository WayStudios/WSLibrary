/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <inputevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

InputEvent::InputEvent(InputEvent::InputDevice T) : GUIEvent(GUIEvent::InputEvent), device(T){}

InputEvent::~InputEvent(){}

END_SOURCECODE
