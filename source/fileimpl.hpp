/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef FILEIMPLEMENTATION_HEADER
#define	FILEIMPLEMENTATION_HEADER

#include <file.hpp>
#include <map.hpp>
#include <atomicinteger.hpp>
#if defined(API_MSWINDOWS)
#include <windows.h>
#endif

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct LOCAL FileSpecific {
    explicit FileSpecific(const String&, AccessMode);
    ~FileSpecific();

    //static Map<String, Vector<FileSpecific*> > Map;

    AtomicInteger AI_Reference;
    String STR_Path;
    AccessMode ENUM_Mode;

#if defined(API_POSIX)
    integer FD_File;
#elif defined(API_MSWINDOWS)
    HFILE H_File;
#endif

    UNCOPYABLE(FileSpecific)
};

class LOCAL File::FileImplementation {
    UNCOPYABLE(FileImplementation)
public:
    FileImplementation();
    ~FileImplementation();

    boolean Open(const String&, AccessMode);
    boolean Close();
    
    size Size() const;
    
    size Read(void*, size);
    size Write(void*, size);
    size Seek(size, SeekPosition);

    FileSpecific* H_Specific;
};

END_WS_NAMESPACE

END_HEADER

#endif
