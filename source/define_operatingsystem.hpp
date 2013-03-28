/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef DEFINE_OPERATINGSYSTEM_HEADER
#define	DEFINE_OPERATINGSYSTEM_HEADER

#if defined(WSOS)
#define OS_WSOS
#elif defined(__FreeBSD__)
#define OS_FREEBSD
#elif defined(__APPLE__)
#define OS_APPLEMACOSX
#elif defined(__linux__)
#define OS_LINUX
#elif defined(_WIN32) || defined(_WIN64)
#define OS_MSWINDOWS
#endif

#endif
