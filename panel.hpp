/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef PANEL_HEADER
#define	PANEL_HEADER

#include <widget.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class EXPORT Panel:public Widget
{
public:
    Panel(Object* OBJ=0);
    Panel(Widget* PARENT=0);
    virtual ~Panel();
protected:
    virtual void Render();
    virtual void ProcessGUIEvent(GUIEvent*);
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
