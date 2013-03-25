/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef WINDOW_HEADER
#define	WINDOW_HEADER

#include <widget.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class EXPORT Window:public Widget
{
    DECLARE_IMPLEMENTATION(Window)
public:
    explicit Window(Object* OBJ);
    explicit Window(Widget* PARENT=0);
	explicit Window(const String&, Widget* PARENT=0);
    virtual ~Window();
protected:
//    virtual void Render();
//    virtual void ProcessGUIEvent(GUIEvent*);
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
