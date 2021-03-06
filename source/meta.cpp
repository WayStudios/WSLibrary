/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <meta.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

MetaPool Meta::Pool;

Meta::Meta(Object* P_OBJ) : handle(P_OBJ), master(0), thread(0){
    Pool.append(this);
}

Meta::~Meta() {
    Pool.remove(this);
}

END_SOURCECODE
