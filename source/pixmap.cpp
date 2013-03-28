/*******************************************************************************
 * Way Studios Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <pixmap.hpp>
#include <pixmapimpl.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE

Pixmap::PixmapImplementation::PixmapImplementation():buffer(0), width(0), height(0), capacity(0){}

Pixmap::PixmapImplementation::~PixmapImplementation(){}

void Pixmap::PixmapImplementation::initialize(SIZE W, SIZE H)
{
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
    width=W;
    height=H;
    capacity=W*H;
    buffer=allocate(capacity);
    for(SIZE ITER=0;ITER<capacity;++ITER)
        construct((buffer+ITER), 0);
}

void Pixmap::PixmapImplementation::destroy()
{
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_MUTEX(&mutex);
#endif
    for(SIZE ITER=0;ITER<capacity;++ITER)
        destruct((buffer+ITER));
    width=height=capacity=0;
}
        
Pixmap::Pixmap(UINTEGER W, UINTEGER H) : implementation(0)
{
    if(W && H)
    {
        implementation=new PixmapImplementation;
        if(implementation)
        {
            ++(implementation->reference);
            implementation->initialize(W, H);
        }
    }
}

Pixmap::Pixmap(const Pixmap& REF) : implementation(REF.implementation)
{
    if(implementation)
        ++(implementation->reference);
}

Pixmap::~Pixmap()
{
    if(implementation)
        if(--(implementation->reference)==0)
            delete implementation;
}

BOOLEAN Pixmap::empty() const
{
    if(implementation)
        return !(implementation->buffer);
    return true;
}

SIZE Pixmap::width() const
{
    if(implementation)
        return implementation->width;
    return 0;
}

SIZE Pixmap::height() const
{
    if(implementation)
        return implementation->height;
    return 0;
}

SIZE Pixmap::capacity() const
{
    if(implementation)
        return implementation->capacity;
    return 0;
}

Pixmap::TYPE& Pixmap::seek(SIZE IDX)
{
    if(implementation)
        return *(implementation->buffer+IDX);
}

Pixmap::TYPE& Pixmap::seek(SIZE IDX_W, SIZE IDX_H)
{
    if(implementation)
        return *(implementation->buffer+IDX_W*IDX_H);
}

const Pixmap::TYPE& Pixmap::seek(SIZE IDX) const
{
    if(implementation)
        return *(implementation->buffer+IDX);
}

const Pixmap::TYPE& Pixmap::seek(SIZE IDX_W, SIZE IDX_H) const
{
    if(implementation)
        return *(implementation->buffer+IDX_W*IDX_H);
}

const Pixmap& Pixmap::operator =(const Pixmap& REF)
{
    if(implementation)
        ++(implementation->reference);
    return *this;
}

BOOLEAN Pixmap::operator ==(const Pixmap& REF) const
{
    if(REF.implementation==implementation)
        return true;
    return false;
}

BOOLEAN Pixmap::operator !=(const Pixmap& REF) const
{
    if(REF.implementation!=implementation)
        return false;
    return true;
}
        
END_WS_NAMESPACE
        
END_HEADER
