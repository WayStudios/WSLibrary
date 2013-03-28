/*******************************************************************************
 * Way Studios Library
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
    ObjectImplementation(Object*);
    ~ObjectImplementation();

	void initialize(const String&, Object* MASTER);
	void destroy();

	Object* getMaster() const;
	void setMaster(Object*);

    Meta meta;
};

END_WS_NAMESPACE

END_HEADER

#endif
