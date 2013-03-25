/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef DEFINE_TYPE_HEADER
#define	DEFINE_TYPE_HEADER

namespace WS {

    typedef char int8;
    typedef short int16;
    typedef int int32;
    typedef long int int64;

    typedef unsigned char uint8;
    typedef unsigned short uint16;
    typedef unsigned int uint32;
    typedef unsigned long int uint64;

    typedef float float32;
    typedef double float64;

    typedef bool boolean;

    typedef int8 byte;
    typedef uint8 ubyte;

    typedef int16 word;
    typedef uint16 uword;

    typedef int32 integer;
    typedef uint32 uinteger;

    typedef float64 variable;

#if defined(__GNUC__)
    typedef __PTRDIFF_TYPE__ ptrdiff;
    typedef __SIZE_TYPE__ size;
#elif defined(_MSC_VER)
    typedef size_t size;
#else
    typedef uint64 ptrdiff;
    typedef uint64 size;
#endif

};

typedef WS::uint16 ws_char;
typedef WS::uint32 ws_typeid;
typedef WS::uint64 ws_timeval;
typedef WS::size ws_size;

#endif
