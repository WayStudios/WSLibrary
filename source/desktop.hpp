/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef DESKTOP_HEADER
#define DESKTOP_HEADER

#include <object.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class Desktop:public Object
{
	UNCOPYABLE(Desktop)
	DECLARE_IMPLEMENTATION(Desktop)
public:
	Desktop();
	~Desktop();

	UINTEGER width() const;
	UINTEGER height() const;

	static Desktop* current();
};

END_WS_NAMESPACE

END_HEADER

#endif
