/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef GUILAYOUT_HEADER
#define	GUILAYOUT_HEADER

#include <guiwidget.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class EXPORT GUILayout:public GUIWidget
{
    UNCOPYABLE(GUILayout)
    DECLARE_IMPLEMENTATION(GUILayout)
public:
    GUILayout(GUIWidget* PARENT=0);
    virtual ~GUILayout();
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
