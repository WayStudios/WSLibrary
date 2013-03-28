/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ALLOCATOR_HEADER
#define	ALLOCATOR_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
class EXPORT Allocator {
    UNCOPYABLE(Allocator<T>)
public:
    typedef T TYPE;

    Allocator();
    virtual ~Allocator();

    TYPE* allocate(SIZE);
    void deallocate(TYPE*);

    void construct(TYPE*, const TYPE&);
    void destruct(TYPE*);
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <allocator_impl.hpp>

#endif
