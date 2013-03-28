/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <string.hpp>
#include <stringimpl.hpp>
#include <scopedlock.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

String::StringImplementation::StringImplementation() : string(0), cstring(0), length(0) {
}

String::StringImplementation::~StringImplementation() {
}

void String::StringImplementation::constructString(const BYTE* CSTR) {
    if (CSTR) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        SIZE L_CSTR = 0;
        while (CSTR[L_CSTR] != '\0')
            ++L_CSTR;
        if (L_CSTR != 0) {
            String::TYPE* N_STR = allocate(L_CSTR);
            for (SIZE i = 0; i < L_CSTR; ++i)
				construct(N_STR + i, static_cast<String::TYPE> (CSTR[i]));
            string = N_STR;
            length = L_CSTR;
        }
    }
}

void String::StringImplementation::constructString(const String::TYPE* P_STR, SIZE L_STR) {
    if (P_STR && L_STR != 0) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
		String::TYPE* N_STR = allocate(L_STR);
        for (SIZE i = 0; i < L_STR; ++i)
            construct(N_STR + i, *(P_STR + i));
        string = N_STR;
        length = L_STR;
    }
}

void String::StringImplementation::constructCString(const String::TYPE* P_STR, SIZE L_STR) {
    if (P_STR && L_STR != 0) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        BYTE* N_CSTR = reinterpret_cast<BYTE*> (::operator new(L_STR + 1));
        for (SIZE i = 0; i < L_STR; ++i)
            N_CSTR[i] = static_cast<BYTE> (*(P_STR + i));
        N_CSTR[L_STR] = '\0';
        cstring = N_CSTR;
    }
}

String::StringImplementation* String::StringImplementation::duplicate() {
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
    StringImplementation* N_IMPL = new StringImplementation;
    if (N_IMPL) {
        if (string && length != 0) {
            N_IMPL->string = allocate(length);
            N_IMPL->length = length;
            for (SIZE i = 0; i < length; ++i)
                construct(N_IMPL->string + i, *(string + i));
        }
    }
    return N_IMPL;
}

void String::StringImplementation::destructString() {
    if (string) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
        for (SIZE i = 0; i < length; ++i)
            destruct(string + i);
        deallocate(string);
        ::operator delete(cstring);
        string = 0;
        cstring = 0;
        length = 0;
    }
}

String::String(const BYTE* CSTR) : implementation(0) {
    implementation = new StringImplementation;
    if (implementation) {
        ++(implementation->ref);
        implementation->constructString(CSTR);
    }
}

String::String(const String& REF) : implementation(REF.implementation) {
    if (implementation)
        ++(implementation->ref);
}

String::~String() {
    if (implementation)
        if (--(implementation->ref) == 0) {
            implementation->destructString();
            delete implementation;
        }
}

SIZE String::length() const {
    if (implementation)
        return implementation->length;
    return 0;
}

BOOLEAN String::empty() const {
    if (implementation)
        return !(implementation->string);
    return true;
}

void String::clear() {
    if (implementation)
        if (--(implementation->ref) == 0) {
            implementation->destructString();
            delete implementation;
        }
    implementation = new StringImplementation;
    if (implementation)
        ++(implementation->ref);
}

const BYTE* String::cstring() {
    if (implementation) {
        if (!empty() && !(implementation->cstring))
            implementation->constructCString(implementation->string, implementation->length);
        return implementation->cstring;
    }
    return 0;
}

String& String::operator =(const BYTE* CSTR) {
    clear();
    if (implementation && CSTR)
        implementation->constructString(CSTR);
    return *this;
}

BOOLEAN String::operator ==(const BYTE* CSTR) const {
    if (implementation && CSTR) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&(implementation->mutex));
#endif
        SIZE L_CSTR = 0;
        while (CSTR[L_CSTR] != '\0')
            ++L_CSTR;
        if (implementation->length != L_CSTR)
            return false;
        for (SIZE i = 0; i < L_CSTR; ++i)
            if (*(implementation->string + i) != CSTR[i])
                return false;
        return true;
    }
    return false;
}

BOOLEAN String::operator !=(const BYTE* CSTR) const {
    if (implementation && CSTR) {
#if !defined(WITHOUT_THREAD)
        ScopedLock<Mutex> SL_MUTEX(&(implementation->mutex));
#endif
        SIZE L_CSTR = 0;
        while (CSTR[L_CSTR] != '\0')
            ++L_CSTR;
        if (implementation->length != L_CSTR)
            return true;
        for (SIZE i = 0; i < L_CSTR; ++i)
            if (*(implementation->string + i) != CSTR[i])
                return true;
        return false;
    }
    return true;
}

String& String::operator =(const String& REF) {
    if (implementation && REF.implementation) {
        ++(REF.implementation->ref);
        if (--(implementation->ref) == 0) {
            StringImplementation* OLD = implementation;
            implementation = REF.implementation;
            OLD->destructString();
            delete OLD;
        } else
            implementation = REF.implementation;
    }
    return *this;
}

BOOLEAN String::operator ==(const String& REF) const {
    if (implementation && REF.implementation) {
        if (implementation != REF.implementation) {
#if !defined(WITHOUT_THREAD)
            ScopedLock<Mutex> SL_MUTEX_F(&(REF.implementation->mutex));
            ScopedLock<Mutex> SL_MUTEX_S(&(implementation->mutex));
#endif
            if (implementation->length != REF.implementation->length)
                return false;
            for (SIZE i = 0; i < implementation->length; ++i)
                if (*(implementation->string + i) != *(REF.implementation->string + i))
                    return false;
        }
        return true;
    }
    return false;
}

BOOLEAN String::operator !=(const String& REF) const {
    if (implementation && REF.implementation) {
        if (implementation != REF.implementation) {
#if !defined(WITHOUT_THREAD)
            ScopedLock<Mutex> SL_MUTEX_F(&(REF.implementation->mutex));
            ScopedLock<Mutex> SL_MUTEX_S(&(implementation->mutex));
#endif
            if (implementation->length != REF.implementation->length)
                return true;
            for (SIZE i = 0; i < implementation->length; ++i)
                if (*(implementation->string + i) != *(REF.implementation->string + i))
                    return true;
        }
        return false;
    }
    return true;
}

END_SOURCECODE
