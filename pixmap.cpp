/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#include <pixmap.hpp>
#include <pixmapimpl.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE

Pixmap::PixmapImplementation::PixmapImplementation():Buf(0), Width(0), Height(0), Capacity(0){}

Pixmap::PixmapImplementation::~PixmapImplementation(){}

void Pixmap::PixmapImplementation::Initial(size W, size H)
{
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
    Width=W;
    Height=H;
    Capacity=W*H;
    Buf=Allocate(Capacity);
    for(size ITER=0;ITER<Capacity;++ITER)
        Construct((Buf+ITER), 0);
}

void Pixmap::PixmapImplementation::Cleanup()
{
#if !defined(WITHOUT_THREAD)
    ScopedLock<Mutex> SL_Mutex(&MLock);
#endif
    for(size ITER=0;ITER<Capacity;++ITER)
        Destruct((Buf+ITER));
    Width=Height=Capacity=0;
}
        
Pixmap::Pixmap(uinteger W, uinteger H):Implementation(0)
{
    if(W && H)
    {
        Implementation=new PixmapImplementation;
        if(Implementation)
        {
            ++(Implementation->Ref);
            Implementation->Initial(W, H);
        }
    }
}

Pixmap::Pixmap(const Pixmap& REF):Implementation(REF.Implementation)
{
    if(Implementation)
        ++(Implementation->Ref);
}

Pixmap::~Pixmap()
{
    if(Implementation)
        if(--(Implementation->Ref)==0)
            delete Implementation;
}

boolean Pixmap::Empty() const
{
    if(Implementation)
        return !(Implementation->Buf);
    return true;
}

size Pixmap::Width() const
{
    if(Implementation)
        return Implementation->Width;
    return 0;
}

size Pixmap::Height() const
{
    if(Implementation)
        return Implementation->Height;
    return 0;
}

size Pixmap::Capacity() const
{
    if(Implementation)
        return Implementation->Capacity;
    return 0;
}

Pixmap::VALUE& Pixmap::Seek(size IDX)
{
    if(Implementation)
        return *(Implementation->Buf+IDX);
}

Pixmap::VALUE& Pixmap::Seek(size IDX_W, size IDX_H)
{
    if(Implementation)
        return *(Implementation->Buf+IDX_W*IDX_H);
}

const Pixmap::VALUE& Pixmap::Seek(size IDX) const
{
    if(Implementation)
        return *(Implementation->Buf+IDX);
}

const Pixmap::VALUE& Pixmap::Seek(size IDX_W, size IDX_H) const
{
    if(Implementation)
        return *(Implementation->Buf+IDX_W*IDX_H);
}

const Pixmap& Pixmap::operator =(const Pixmap& REF)
{
    if(Implementation)
        ++(Implementation->Ref);
    return *this;
}

boolean Pixmap::operator ==(const Pixmap& REF) const
{
    if(REF.Implementation==Implementation)
        return true;
    return false;
}

boolean Pixmap::operator !=(const Pixmap& REF) const
{
    if(REF.Implementation!=Implementation)
        return false;
    return true;
}
        
END_WS_NAMESPACE
        
END_HEADER
