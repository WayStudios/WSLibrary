/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <string.hpp>
#include <stringimpl.hpp>
#include <scopedlock.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

String::StringImplementation::StringImplementation() : StringB(0), CStringB(0), Length(0) {
}

String::StringImplementation::~StringImplementation() {
}

void String::StringImplementation::ConstructString(const byte* CSTR) {
    if (CSTR) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        size L_CSTR = 0;
        while (CSTR[L_CSTR] != '\0')
            ++L_CSTR;
        if (L_CSTR != 0) {
            ws_char* N_STR = Allocate(L_CSTR);
            for (size i = 0; i < L_CSTR; ++i)
                Construct(N_STR + i, static_cast<ws_char> (CSTR[i]));
            StringB = N_STR;
            Length = L_CSTR;
        }
    }
}

void String::StringImplementation::ConstructString(const ws_char* P_STR, size L_STR) {
    if (P_STR && L_STR != 0) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        ws_char* N_STR = Allocate(L_STR);
        for (size i = 0; i < L_STR; ++i)
            Construct(N_STR + i, *(P_STR + i));
        StringB = N_STR;
        Length = L_STR;
    }
}

void String::StringImplementation::ConstructCString(const ws_char* P_STR, size L_STR) {
    if (P_STR && L_STR != 0) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        byte* N_CSTR = reinterpret_cast<byte*> (::operator new(L_STR + 1));
        for (size i = 0; i < L_STR; ++i)
            N_CSTR[i] = static_cast<byte> (*(P_STR + i));
        N_CSTR[L_STR] = '\0';
        CStringB = N_CSTR;
    }
}

String::StringImplementation* String::StringImplementation::Duplicate() {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
    StringImplementation* N_IMPL = new StringImplementation;
    if (N_IMPL) {
        if (StringB && Length != 0) {
            N_IMPL->StringB = Allocate(Length);
            N_IMPL->Length = Length;
            for (size i = 0; i < Length; ++i)
                Construct(N_IMPL->StringB + i, *(StringB + i));
        }
    }
    return N_IMPL;
}

void String::StringImplementation::DestructString() {
    if (StringB) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
        for (size i = 0; i < Length; ++i)
            Destruct(StringB + i);
        Deallocate(StringB);
        ::operator delete(CStringB);
        StringB = 0;
        CStringB = 0;
        Length = 0;
    }
}

String::String(const byte* CSTR) : Implementation(0) {
    Implementation = new StringImplementation;
    if (Implementation) {
        ++(Implementation->Ref);
        Implementation->ConstructString(CSTR);
    }
}

String::String(const String& REF) : Implementation(REF.Implementation) {
    if (Implementation)
        ++(Implementation->Ref);
}

String::~String() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->DestructString();
            delete Implementation;
        }
}

size String::Length() const {
    if (Implementation)
        return Implementation->Length;
    return 0;
}

boolean String::Empty() const {
    if (Implementation)
        return !(Implementation->StringB);
    return true;
}

void String::Clear() {
    if (Implementation)
        if (--(Implementation->Ref) == 0) {
            Implementation->DestructString();
            delete Implementation;
        }
    Implementation = new StringImplementation;
    if (Implementation)
        ++(Implementation->Ref);
}

const byte* String::CString() {
    if (Implementation) {
        if (!Empty() && !(Implementation->CStringB))
            Implementation->ConstructCString(Implementation->StringB, Implementation->Length);
        return Implementation->CStringB;
    }
    return 0;
}

String& String::operator =(const byte* CSTR) {
    Clear();
    if (Implementation && CSTR)
        Implementation->ConstructString(CSTR);
    return *this;
}

boolean String::operator ==(const byte* CSTR) const {
    if (Implementation && CSTR) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&(Implementation->MLock));
#endif
        size L_CSTR = 0;
        while (CSTR[L_CSTR] != '\0')
            ++L_CSTR;
        if (Implementation->Length != L_CSTR)
            return false;
        for (size i = 0; i < L_CSTR; ++i)
            if (*(Implementation->StringB + i) != CSTR[i])
                return false;
        return true;
    }
    return false;
}

boolean String::operator !=(const byte* CSTR) const {
    if (Implementation && CSTR) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_Mutex(&(Implementation->MLock));
#endif
        size L_CSTR = 0;
        while (CSTR[L_CSTR] != '\0')
            ++L_CSTR;
        if (Implementation->Length != L_CSTR)
            return true;
        for (size i = 0; i < L_CSTR; ++i)
            if (*(Implementation->StringB + i) != CSTR[i])
                return true;
        return false;
    }
    return true;
}

String& String::operator =(const String& REF) {
    if (Implementation && REF.Implementation) {
        ++(REF.Implementation->Ref);
        if (--(Implementation->Ref) == 0) {
            StringImplementation* OLD = Implementation;
            Implementation = REF.Implementation;
            OLD->DestructString();
            delete OLD;
        } else
            Implementation = REF.Implementation;
    }
    return *this;
}

boolean String::operator ==(const String& REF) const {
    if (Implementation && REF.Implementation) {
        if (Implementation != REF.Implementation) {
#if !defined(WITHOUT_THREAD)
            ScopedLock<Mutex> SL_Mutex_F(&(REF.Implementation->MLock));
            ScopedLock<Mutex> SL_Mutex_S(&(Implementation->MLock));
#endif
            if (Implementation->Length != REF.Implementation->Length)
                return false;
            for (size i = 0; i < Implementation->Length; ++i)
                if (*(Implementation->StringB + i) != *(REF.Implementation->StringB + i))
                    return false;
        }
        return true;
    }
    return false;
}

boolean String::operator !=(const String& REF) const {
    if (Implementation && REF.Implementation) {
        if (Implementation != REF.Implementation) {
#if !defined(WITHOUT_THREAD)
            ScopedLock<Mutex> SL_Mutex_F(&(REF.Implementation->MLock));
            ScopedLock<Mutex> SL_Mutex_S(&(Implementation->MLock));
#endif
            if (Implementation->Length != REF.Implementation->Length)
                return true;
            for (size i = 0; i < Implementation->Length; ++i)
                if (*(Implementation->StringB + i) != *(REF.Implementation->StringB + i))
                    return true;
        }
        return false;
    }
    return true;
}

END_SOURCECODE
