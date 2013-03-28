/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef PROGRESSBARIMPLEMENTATION_HEADER
#define PROGRESSBARIMPLEMENTATION_HEADER

#include <progressbar.hpp>
#include <widgetimpl.hpp>

BEGIN_HEADER
	
BEGIN_WS_NAMESPACE

class LOCAL ProgressBar::ProgressBarImplementation
{
	UNCOPYABLE(ProgressBarImplementation)
public:
	explicit ProgressBarImplementation(Widget*);
	~ProgressBarImplementation();

	void initialize();

	Widget* H_Widget;
};

END_WS_NAMESPACE

END_HEADER

#endif
