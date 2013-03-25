/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef OBJECTIMPLEMENTATION_HEADER
#define	OBJECTIMPLEMENTATION_HEADER

#include <object.hpp>
#include <meta.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class LOCAL Object::ObjectImplementation {
    UNCOPYABLE(ObjectImplementation)
public:
    explicit ObjectImplementation(const String&, Object* OBJ);
    ~ObjectImplementation();

    Meta OBJMeta;
};

END_WS_NAMESPACE

END_HEADER

#endif
