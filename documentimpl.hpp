/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef DOCUMENTIMPLEMENTATION_HEADER
#define	DOCUMENTIMPLEMENTATION_HEADER

#include <document.hpp>
#include <atomicinteger.hpp>
#include <mutex.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL Document::DocumentImplementation {
    UNCOPYABLE(DocumentImplementation)
public:
    DocumentImplementation();
    ~DocumentImplementation();

    AtomicInteger Ref;
    Mutex MLock;
    String Buf;
};

END_WS_NAMESPACE

END_HEADER

#endif
