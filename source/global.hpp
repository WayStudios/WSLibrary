/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef GLOBAL_HEADER
#define	GLOBAL_HEADER

#include <define_architecture.hpp>
#include <define_operatingsystem.hpp>
#include <define_compiler.hpp>
#include <define_api.hpp>
#include <define_type.hpp>
#include <define_macro.hpp>
#if defined(GUI)
#include <define_windowsystem.hpp>
#include <define_inputkey.hpp>
#endif

BEGIN_HEADER

BEGIN_WS_NAMESPACE

enum AccessMode {
    UNDEFINED_MODE      = 0x00,
    READ_ONLY           = 0x01,
    WRITE_ONLY          = 0x02,
    READ_WRITE          = 0x03
};

enum SeekPosition {
    UNDEFINED_POSITION  = 0x00,
    BEGINNING           = 0x01,
    CURRENT             = 0x02,
    END                 = 0x03
};

END_WS_NAMESPACE

END_HEADER

#endif
