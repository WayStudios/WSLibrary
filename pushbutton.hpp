/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef GUIPUSHBUTTON_HEADER
#define	GUIPUSHBUTTON_HEADER

#include <guiwidget.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class EXPORT GUIPushButton:public GUIWidget
{
    UNCOPYABLE(GUIPushButton)
public:
    explicit GUIPushButton(GUIWidget* PARENT=0);
    virtual ~GUIPushButton();
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
