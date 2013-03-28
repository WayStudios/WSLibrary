/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef DEFINE_ARCHITECTURE_HEADER
#define	DEFINE_ARCHITECTURE_HEADER

#if defined(__i386__) || defined(_M_IX86)
#define ARCHITECTURE_X86
#elif defined(__x86_64__) || defined(_M_X64)
#define ARCHITECTURE_X64
#elif defined(__ia64__) || defined(_M_IA64)
#define ARCHITECTURE_IA64
#elif defined(__ppc__) || defined(_M_PPC)
#define ARCHITECTURE_PPC
#elif defined(__arm__)
#define ARCHITECTURE_ARM
#endif

#endif
