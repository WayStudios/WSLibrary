/*******************************************************************************
 * Way Studios Library
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

    AccessMode mode() const;
    
    String path() const;

    SIZE size() const;

//    SIZE capacity() const;

    BOOLEAN open(const BYTE*, AccessMode);
    BOOLEAN open(const String&, AccessMode);
    void close();

    static BOOLEAN access(const BYTE*, AccessMode);
    static BOOLEAN create(const BYTE*);
    static BOOLEAN remove(const BYTE*);

    static BOOLEAN access(const String&, AccessMode);
    static BOOLEAN create(const String&);
    static BOOLEAN remove(const String&);
    
    SIZE read(void*, SIZE);
    SIZE write(void*, SIZE);
    SIZE seek(SIZE, SeekPosition);
};

END_WS_NAMESPACE

END_HEADER

#endif
