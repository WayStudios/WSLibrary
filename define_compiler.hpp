/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef DEFINE_COMPILER_HEADER
#define	DEFINE_COMPILER_HEADER

#if defined(WSC)
#define C_WSC
#elif defined(__GNUC__)
#define C_GNUC
#elif defined(_MSC_VER)
#define C_MSC
#endif

#endif
