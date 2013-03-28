/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef DEFINE_API_HEADER
#define	DEFINE_API_HEADER

#if defined(__unix__) || defined(USING_API_POSIX)
#define API_POSIX
#if defined(BSD) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__APPLE__) || defined(USING_API_BSD)
#define API_BSD
#endif
#if defined(__MACH__) || defined(USING_API_MACH)
#define API_MACH
#endif
#if defined(__APPLE__)
#define API_APPLEMACOSX
#endif
#elif defined(_WIN32) || defined(_WIN64) || defined(USING_API_WINDOWS)
#define API_MSWINDOWS
#endif

#endif
