/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <document.hpp>
#include <documentimpl.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

Document::DocumentImplementation::DocumentImplementation() : Buf(0) {
}

Document::DocumentImplementation::~DocumentImplementation() {
}

Document::Document() : Implementation(0) {
    Implementation = new DocumentImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

Document::Document(const String& STR) : Implementation(0) {
    Implementation = new DocumentImplementation;
    if (Implementation) {
        ++(Implementation->Ref);
        Implementation->Buf = STR;
    }
}

Document::Document(const Document& REF) : Implementation(REF.Implementation) {
    if (Implementation)
        ++(Implementation->Ref);
}

Document::~Document() {
    if (Implementation)
        if (--(Implementation->Ref) == 0)
            delete Implementation;
}

String Document::Data() const {
    if (Implementation)
        return Implementation->Buf;
    return String();
}

String Document::GetLineAt(size) const {
    return String();
}

Document& Document::operator =(const Document& REF) {
    if (Implementation && REF.Implementation) {
        ++(REF.Implementation->Ref);
        if (--(Implementation->Ref) == 0)
            delete Implementation;
        else
            Implementation = REF.Implementation;
    }
    return *this;
}

boolean Document::operator ==(const Document& REF) const {
    if (Implementation && REF.Implementation)
        if (Implementation != REF.Implementation)
            return Implementation->Buf == REF.Implementation->Buf;
        else
            return true;
    return false;
}

boolean Document::operator !=(const Document& REF) const {
    if (Implementation && REF.Implementation)
        if (Implementation != REF.Implementation)
            return Implementation->Buf != REF.Implementation->Buf;
        else
            return false;
    return true;
}

END_SOURCECODE
