/*******************************************************************************
 * WayStudio Graphics Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef PIXMAPIMPLEMENTATION_HEADER
#define	PIXMAPIMPLEMENTATION_HEADER

#include <pixmap.hpp>
#include <allocator.hpp>
#include <atomicinteger.hpp>
#include <mutex.hpp>
#include <scopedlock.hpp>

BEGIN_HEADER
        
BEGIN_WS_NAMESPACE
        
class LOCAL Pixmap::PixmapImplementation:public Allocator<uinteger>
{
public:
    PixmapImplementation();
    ~PixmapImplementation();
    
    void Initial(size, size);
    void Cleanup();
    
#if !defined(WITHOUT_THREAD)
    AtomicInteger Ref;
    Mutex MLock;
#endif
    uinteger* Buf;
    size Width;
    size Height;
    size Capacity;
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
