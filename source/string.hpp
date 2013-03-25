/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef STRING_HEADER
#define	STRING_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT String {
    DECLARE_IMPLEMENTATION(String)
public:
    typedef ws_char VALUE;

    explicit String(const byte* CSTR = 0);
    String(const String&);
    ~String();

    size Length() const;
    boolean Empty() const;
    void Clear();

    const byte* CString();

    String& operator=(const byte*);

    boolean operator==(const byte*) const;
    boolean operator!=(const byte*) const;

    String& operator=(const String&);

    boolean operator==(const String&) const;
    boolean operator!=(const String&) const;
};

END_WS_NAMESPACE

END_HEADER

#endif
