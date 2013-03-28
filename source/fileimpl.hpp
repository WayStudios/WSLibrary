/*******************************************************************************
 * Way Studios Library
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

    //static Map<String, Vector<FileSpecific*> > map;

    AtomicInteger reference;
    String path;
    AccessMode mode;

#if defined(API_POSIX)
    integer FD_File;
#elif defined(API_MSWINDOWS)
    HFILE hFile;
#endif

    UNCOPYABLE(FileSpecific)
};

class LOCAL File::FileImplementation {
    UNCOPYABLE(FileImplementation)
public:
    FileImplementation();
    ~FileImplementation();

    BOOLEAN open(const String&, AccessMode);
    BOOLEAN close();
    
    SIZE size() const;
    
    SIZE read(void*, SIZE);
    SIZE write(void*, SIZE);
    SIZE seek(SIZE, SeekPosition);

    FileSpecific* specific;
};

END_WS_NAMESPACE

END_HEADER

#endif
