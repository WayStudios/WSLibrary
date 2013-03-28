/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef DEFINE_COMPILER_HEADER
#define	DEFINE_COMPILER_HEADER

#if defined(WSC)
#define COMPILER_WSC
#elif defined(__GNUC__)
#define COMPILER_GNUC
#elif defined(_MSC_VER)
#define COMPILER_MSC
#endif

#endif
