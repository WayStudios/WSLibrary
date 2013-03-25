/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef DEFINE_ARCHITECTURE_HEADER
#define	DEFINE_ARCHITECTURE_HEADER

#if defined(__i386__) || defined(_M_IX86)
#define ARCH_X86
#elif defined(__x86_64__) || defined(_M_X64)
#define ARCH_X64
#elif defined(__ia64__) || defined(_M_IA64)
#define ARCH_IA64
#elif defined(__ppc__) || defined(_M_PPC)
#define ARCH_PPC
#elif defined(__arm__)
#define ARCH_ARM
#endif

#endif
