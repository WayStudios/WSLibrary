/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef FILE_HEADER
#define	FILE_HEADER

#include <streambuffer.hpp>
#include <object.hpp>
#include <document.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

class EXPORT File : public StreamBuffer {
    DECLARE_IMPLEMENTATION(File)
    UNCOPYABLE(File)
public:
    explicit File(Object* OBJ = 0);
//  File(const File&);
    ~File();

    AccessMode Mode() const;
    
    String Path() const;

    size Size() const;

//    size Capacity() const;

    boolean Open(const byte*, AccessMode);
    boolean Open(const String&, AccessMode);
    void Close();

    static boolean Access(const byte*, AccessMode);
    static boolean Create(const byte*);
    static boolean Remove(const byte*);

    static boolean Access(const String&, AccessMode);
    static boolean Create(const String&);
    static boolean Remove(const String&);
    
    size Read(void*, size);
    size Write(void*, size);
    size Seek(size, SeekPosition);
};

END_WS_NAMESPACE

END_HEADER

#endif
