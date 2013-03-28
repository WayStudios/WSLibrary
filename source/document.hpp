/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef DOCUMENT_HEADER
#define	DOCUMENT_HEADER

#include <streambuffer.hpp>
#include <string.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT Document : public StreamBuffer {
    DECLARE_IMPLEMENTATION(Document)
public:
    Document();
    explicit Document(const String&);
    Document(const Document&);
    virtual ~Document();

    String data() const;

    String getLineAt(SIZE) const;

    Document& operator =(const Document&);

    BOOLEAN operator ==(const Document&) const;
    BOOLEAN operator !=(const Document&) const;
};

END_WS_NAMESPACE

END_HEADER

#endif
