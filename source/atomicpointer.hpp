/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef ATOMICPOINTER_HEADER
#define	ATOMICPOINTER_HEADER

#include <global.hpp>

BEGIN_HEADER

BEGIN_TEMPLATE

BEGIN_WS_NAMESPACE

template <typename T>
class EXPORT AtomicPointer {
public:
    typedef T TYPE;

	explicit AtomicPointer(TYPE* V = 0);
    AtomicPointer(const AtomicPointer<T>&);
    ~AtomicPointer();

    TYPE* load() const;

    AtomicPointer<T>& store(TYPE*);

    BOOLEAN compare(TYPE*) const;

    TYPE* swap(TYPE*);

    BOOLEAN compareAndSwap(TYPE*, TYPE*);

    TYPE* operator ->() const;

    TYPE& operator *() const;

    AtomicPointer<T>& operator =(TYPE*);

    AtomicPointer<T>& operator +=(PTRDIFF);
    AtomicPointer<T>& operator -=(PTRDIFF);

    BOOLEAN operator ==(TYPE*) const;
    BOOLEAN operator !=(TYPE*) const;

    AtomicPointer<T>& operator =(const AtomicPointer<T>&);

    AtomicPointer<T>& operator ++();
    AtomicPointer<T>& operator --();

    BOOLEAN operator ==(const AtomicPointer<T>&) const;
    BOOLEAN operator !=(const AtomicPointer<T>&) const;
private:
	TYPE * volatile value;
};

END_WS_NAMESPACE

END_TEMPLATE

END_HEADER

#include <atomicpointer_impl.hpp>

#endif
