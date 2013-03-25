/*******************************************************************************
 * WayStudio GUI Library
 * Developer:Xu Waycell
*******************************************************************************/
#ifndef DEFINE_WINDOWSYSTEM_HEADER
#define	DEFINE_WINDOWSYSTEM_HEADER

#if defined(WSOS)
#define WS_WSOS
#elif defined(USING_X11)
#define WS_X11
#elif defined(__APPLE__)
#define WS_MACOSX
#elif defined(_WIN32) || defined(_WIN64)
#define WS_MSWINDOWS
#endif

#endif
