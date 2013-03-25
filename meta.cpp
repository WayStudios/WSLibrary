/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <meta.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

MetaPool Meta::Pool;

Meta::Meta(const String& STR, Object* P_OBJ) : Handle(P_OBJ), Master(0), Name(STR) {
    Pool.Append(this);
}

Meta::~Meta() {
    Pool.Remove(this);
}

END_SOURCECODE
