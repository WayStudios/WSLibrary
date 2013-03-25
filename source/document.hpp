/*******************************************************************************
 * WayStudio Library
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

    String Data() const;

    String GetLineAt(size) const;

    Document& operator=(const Document&);

    boolean operator==(const Document&) const;
    boolean operator!=(const Document&) const;
};

END_WS_NAMESPACE

END_HEADER

#endif
