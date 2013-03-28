/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef PROGRESSBAR_HEADER
#define PROGRESSBAR_HEADER

#include <widget.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT ProgressBar:public Widget
{
	UNCOPYABLE(ProgressBar)
	DECLARE_IMPLEMENTATION(ProgressBar)
public:
	explicit ProgressBar(Widget* PARENT=0);
	virtual ~ProgressBar();
};

END_WS_NAMESPACE

END_HEADER

#endif
