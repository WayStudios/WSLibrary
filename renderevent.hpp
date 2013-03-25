/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <guievent.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXPORT RenderEvent:public GUIEvent
{
	RenderEvent();
	~RenderEvent();
};

END_WS_NAMESPACE

END_HEADER
