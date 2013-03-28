/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <document.hpp>
#include <documentimpl.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

Document::DocumentImplementation::DocumentImplementation() : buffer(0) {
}

Document::DocumentImplementation::~DocumentImplementation() {
}

Document::Document() : implementation(0) {
    implementation = new DocumentImplementation;
    if (implementation)
        ++(implementation->reference);
}

Document::Document(const String& STR) : implementation(0) {
    implementation = new DocumentImplementation;
    if (implementation) {
        ++(implementation->reference);
        implementation->buffer = STR;
    }
}

Document::Document(const Document& REF) : implementation(REF.implementation) {
    if (implementation)
        ++(implementation->reference);
}

Document::~Document() {
    if (implementation)
        if (--(implementation->reference) == 0)
            delete implementation;
}

String Document::data() const {
    if (implementation)
        return implementation->buffer;
    return String();
}

String Document::getLineAt(SIZE) const {
    return String();
}

Document& Document::operator =(const Document& REF) {
    if (implementation && REF.implementation) {
        ++(REF.implementation->reference);
        if (--(implementation->reference) == 0)
            delete implementation;
        else
            implementation = REF.implementation;
    }
    return *this;
}

BOOLEAN Document::operator ==(const Document& REF) const {
    if (implementation && REF.implementation)
        if (implementation != REF.implementation)
            return implementation->buffer == REF.implementation->buffer;
        else
            return true;
    return false;
}

BOOLEAN Document::operator !=(const Document& REF) const {
    if (implementation && REF.implementation)
        if (implementation != REF.implementation)
            return implementation->buffer != REF.implementation->buffer;
        else
            return false;
    return true;
}

END_SOURCECODE
