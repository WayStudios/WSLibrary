/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <desktop.hpp>
#include <desktopimpl.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

DesktopSpecific::DesktopSpecific(Desktop* D) : desktop(D), height(0), width(0){}

DesktopSpecific::~DesktopSpecific(){}

Desktop::DesktopImplementation::DesktopImplementation() : desktopSpecific(0){}

Desktop::DesktopImplementation::~DesktopImplementation(){}

UINTEGER Desktop::DesktopImplementation::width() const
{
	if(desktopSpecific)
		return desktopSpecific->width;
	return 0;
}

UINTEGER Desktop::DesktopImplementation::height() const
{
	if(desktopSpecific)
		return desktopSpecific->height;
	return 0;
}

Desktop* Desktop::current()
{
	return 0;
}

Desktop::Desktop() : implementation(0){
	implementation = new DesktopImplementation();
}

Desktop::~Desktop()
{
	if(implementation)
		delete implementation;
}

UINTEGER Desktop::width() const
{
	if(implementation)
		return implementation->width();
	return 0;
}

UINTEGER Desktop::height() const
{
	if(implementation)
		return implementation->height();
	return 0;
}

END_WS_NAMESPACE

END_SOURCECODE
