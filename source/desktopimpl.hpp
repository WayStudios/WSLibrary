/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef DESKTOPIMPLEMENTATION_HEADER
#define DESKTOPIMPLEMENTATION_HEADER

#include <desktop.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct EXTERN DesktopSpecific
{
	explicit DesktopSpecific(Desktop*);
	~DesktopSpecific();

	Desktop* desktop;
	UINTEGER height;
	UINTEGER width;
#if defined(WS_X11)
	int xscreen;
#elif defined(WS_MSWINDOWS)
#endif
};

class LOCAL Desktop::DesktopImplementation
{
public:
	DesktopImplementation();
	~DesktopImplementation();

	UINTEGER width() const;
	UINTEGER height() const;

	DesktopSpecific* desktopSpecific;
};

END_WS_NAMESPACE

END_HEADER

#endif
