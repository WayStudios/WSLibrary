/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef GUIWIDGET_HEADER
#define	GUIWIDGET_HEADER

#include <object.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE

struct GUIEvent;
        
class EXPORT Widget:public Object
{
    DECLARE_IMPLEMENTATION(Widget)
public:
    explicit Widget(Object* OBJ);
    explicit Widget(Widget* PARENT=0);
	explicit Widget(const String&, Widget* PARENT=0);
    virtual ~Widget();
    
    void Show();
    void Hide();
    void Close();

    const String& GetTitle() const;
    void SetTitle(const String&);
    
    Widget* GetChild() const;
    void SetChild(Widget*);
    
    boolean IsWindow() const;
    
    integer Width() const;
    integer Height() const;
    
    void Resize(integer, integer);
protected:
    virtual void Render();
    virtual void ProcessEvent(Event*);
    virtual void ProcessGUIEvent(GUIEvent*);
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
