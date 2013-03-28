/*******************************************************************************
 * Way Studios Library
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
    typedef CHAR TYPE;

    explicit String(const BYTE* CSTR = 0);
    String(const String&);
    ~String();

    SIZE length() const;
    BOOLEAN empty() const;
    void clear();

    const BYTE* cstring();

    String& operator =(const BYTE*);

    BOOLEAN operator ==(const BYTE*) const;
    BOOLEAN operator !=(const BYTE*) const;

    String& operator =(const String&);

    BOOLEAN operator ==(const String&) const;
    BOOLEAN operator !=(const String&) const;
};

END_WS_NAMESPACE

END_HEADER

#endif
