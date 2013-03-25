/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <keyevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

KeyEvent::KeyEvent(InputKey K, boolean PRESSED):InputEvent(InputEvent::Key), Key(K), Status(PRESSED){}

KeyEvent::~KeyEvent(){}

boolean KeyEvent::IsPressed() const{return Status;}

boolean KeyEvent::IsReleased() const{return !Status;}

END_SOURCECODE
