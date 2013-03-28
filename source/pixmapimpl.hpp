/*******************************************************************************
 * Way Studios Graphics Library
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
        
class LOCAL Pixmap::PixmapImplementation:public Allocator<UINTEGER> {
public:
    PixmapImplementation();
    ~PixmapImplementation();
    
    void initialize(SIZE, SIZE);
    void destroy();
    
#if !defined(WITHOUT_THREAD)
    AtomicInteger reference;
    Mutex mutex;
#endif
    UINTEGER* buffer;
    SIZE width;
    SIZE height;
    SIZE capacity;
};
        
END_WS_NAMESPACE
        
END_HEADER

#endif
