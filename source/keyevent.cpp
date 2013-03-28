/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <keyevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

KeyEvent::KeyEvent(InputKey K, BOOLEAN PRESSED) : InputEvent(InputEvent::Key), key(K), status(PRESSED){}

KeyEvent::~KeyEvent(){}

BOOLEAN KeyEvent::isPressed() const{return status;}

BOOLEAN KeyEvent::isReleased() const{return !status;}

END_SOURCECODE
