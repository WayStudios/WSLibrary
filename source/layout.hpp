/*******************************************************************************
 * Way Studios GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef LAYOUT_HEADER
#define LAYOUT_HEADER

#include <object.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class Widget;

class EXPORT Layout:public Object {
	UNCOPYABLE(Layout)
	DECLARE_IMPLEMENTATION(Layout)
public:
	explicit Layout(Widget* PARENT=0);
	virtual ~Layout() =0;

	virtual void adjust() =0;

//	virtual void Clear();
//	virtual void Append(Widget*) =0;
//	virtual void Remove(Widget*) =0;
};

END_WS_NAMESPACE

END_HEADER

#endif
