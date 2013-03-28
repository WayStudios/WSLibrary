/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <file.hpp>
#include <fileimpl.hpp>
#if defined(API_POSIX)
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#endif

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

FileSpecific::FileSpecific(const String& PATH, AccessMode MODE) : path(PATH), mode(MODE)
#if defined(API_POSIX)
, FD_File(0)
#elif defined(API_MSWINDOWS)
, hFile(0)
#endif
{
}

FileSpecific::~FileSpecific() {
}

File::FileImplementation::FileImplementation() : specific(0) {
}

File::FileImplementation::~FileImplementation() {
}

BOOLEAN File::FileImplementation::open(const String& STR, AccessMode MODE) {
    if (!STR.empty() && MODE != UNDEFINED_MODE)
        if (specific) {
#if defined(API_POSIX)
            integer FLAG = 0;
            switch (MODE) {
                case READ_ONLY:
                    FLAG = O_RDONLY;
                    break;
                case WRITE_ONLY:
                    FLAG = O_WRONLY;
                    break;
                case READ_WRITE:
                    FLAG = O_RDWR;
                    break;
            }
            if (FLAG != 0) {
                integer FD = open(String(STR).CString(), FLAG);
                if (FD >= 0) {
                    specific = new FileSpecific(STR, MODE);
                    specific->FD_File = FD;
                    specific->mode = MODE;
                    ++(specific->reference);
                    return true;
                }
            }
#elif defined(API_MSWINDOWS)
#endif
        }
    return false;
}

BOOLEAN File::FileImplementation::close() {
    BOOLEAN RET = false;
    if (specific) {
#if defined(API_POSIX)
        if (specific->FD_File != 0)
            if (close(specific->FD_File) == 0)
                RET = true;
#elif defined(API_MSWINDOWS)
        if (specific->hFile != 0)
            if (CloseHandle(reinterpret_cast<HANDLE>(specific->hFile)))
                RET = true;
#endif
        if (RET == true)
            if ((--(specific->reference)) == 0) {
                delete specific;
                specific = 0;
            }
    }
    return RET;
}

SIZE File::FileImplementation::size() const {
    if (specific) {
#if defined(API_POSIX)
#elif defined(API_MSWINDOWS)
#endif
    }
    return 0;
}

SIZE File::FileImplementation::read(void* BUF, SIZE RD_SZ) {
    SIZE RET = 0;
    if (BUF && specific && RD_SZ != 0) {
#if defined(API_POSIX)
        RET = read(specific->FD_File, BUF, RD_SZ);
#elif defined(API_MSWINDOWS)
#endif
    }
    return RET;
}

SIZE File::FileImplementation::write(void* BUF, SIZE WR_SZ) {
    SIZE RET = 0;
    if (BUF && specific && WR_SZ != 0) {
#if defined(API_POSIX)
        RET = write(specific->FD_File, BUF, WR_SZ);
#elif defined(API_MSWINDOWS)
#endif
    }
    return RET;
}

SIZE File::FileImplementation::seek(SIZE OFFSET, SeekPosition SEEKPOS) {
    if (specific && SEEKPOS != UNDEFINED_POSITION) {
#if defined(API_POSIX)
        off_t WHENCE = 0;
        switch (SEEKPOS) {
            case BEGINNING:
                WHENCE = SEEK_SET;
                break;
            case CURRENT:
                WHENCE = SEEK_CUR;
                break;
            case END:
                WHENCE = SEEK_END;
                break;
        }
        return lseek(specific->FD_File, WHENCE, OFFSET);
#elif defined(API_MSWINDOWS)
#endif
    }
    return 0;
}

BOOLEAN File::access(const BYTE* C_STR, AccessMode MODE) {
    return File::access(String(C_STR), MODE);
}

BOOLEAN File::access(const String&, AccessMode) {
	return false;
}

File::File(Object* OBJ) : StreamBuffer(OBJ), implementation(0) {
    implementation = new FileImplementation();
}

//File::File(const File& REF):StreamBuffer(REF.GetMaster()), Implementation(0){}

File::~File() {
    close();
    if (implementation)
        delete implementation;
}

//SIZE File::Capacity() const{return 0;}

AccessMode File::mode() const {
    if (implementation)
        if (implementation->specific)
            return implementation->specific->mode;
    return UNDEFINED_MODE;
}

String File::path() const {
    if (implementation)
        if (implementation->specific)
            return implementation->specific->path;
    return String();
}

SIZE File::size() const {
    if (implementation)
        return implementation->size();
    return 0;
}

void File::close() {
    if (implementation)
        implementation->close();
}

SIZE File::read(void* BUF, SIZE RD_SZ) {
    if (implementation && BUF)
        return implementation->read(BUF, RD_SZ);
    return 0;
}

SIZE File::write(void* BUF, SIZE WR_SZ) {
    if (implementation && BUF)
        return implementation->write(BUF, WR_SZ);
    return 0;
}

SIZE File::seek(SIZE OFFSET, SeekPosition POSITION) {
    if (implementation && POSITION != UNDEFINED_POSITION)
        return implementation->seek(OFFSET, POSITION);
    return 0;
}

END_WS_NAMESPACE

END_SOURCECODE
