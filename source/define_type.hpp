/*******************************************************************************
 * Way Studios Library
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

    typedef bool BOOLEAN;

    typedef int8 BYTE;
    typedef uint8 UBYTE;

    typedef int16 WORD;
    typedef uint16 UWORD;

    typedef int32 INTEGER;
    typedef uint32 UINTEGER;

    typedef float64 VARIABLE;

	typedef uint16 CHAR;
	typedef uint32 TYPEID;
	typedef uint64 TIMEVAL;

#if defined(__GNUC__)
    typedef __PTRDIFF_TYPE__ PTRDIFF;
    typedef __SIZE_TYPE__ SIZE;
#elif defined(_MSC_VER)
    typedef size_t SIZE;
#else
    typedef uint64 PTRDIFF;
    typedef uint64 SIZE;
#endif

};

typedef WS::CHAR ws_char;
typedef WS::TYPEID ws_typeid;
typedef WS::TIMEVAL ws_timeval;
typedef WS::SIZE ws_size;

#endif
