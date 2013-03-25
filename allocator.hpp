/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ALLOCATOR_HEADER
#define	ALLOCATOR_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename TYPE>
class EXPORT Allocator {
    UNCOPYABLE(Allocator<TYPE>)
public:
    typedef TYPE VALUE;

    Allocator();
    virtual ~Allocator();

    TYPE* Allocate(size);
    void Deallocate(TYPE*);

    void Construct(TYPE*, const TYPE&);
    void Destruct(TYPE*);
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <allocator_impl.hpp>

#endif
