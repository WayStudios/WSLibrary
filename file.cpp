/*******************************************************************************
 * WayStudio Library
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

USING_WS_NAMESPACE

FileSpecific::FileSpecific(const String& PATH, AccessMode MODE) : STR_Path(PATH), ENUM_Mode(MODE)
#if defined(API_POSIX)
, FD_File(0)
#elif defined(API_MSWINDOWS)
, H_File(0)
#endif
{
}

FileSpecific::~FileSpecific() {
}

File::FileImplementation::FileImplementation() : H_Specific(0) {
}

File::FileImplementation::~FileImplementation() {
}

boolean File::FileImplementation::Open(const String& STR, AccessMode MODE) {
    if (!STR.Empty() && MODE != UNDEFINED_MODE)
        if (H_Specific) {
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
                    H_Specific = new FileSpecific(STR, MODE);
                    H_Specific->FD_File = FD;
                    H_Specific->ENUM_Mode = MODE;
                    ++(H_Specific->AI_Reference);
                    return true;
                }
            }
#elif defined(API_MSWINDOWS)
#endif
        }
    return false;
}

boolean File::FileImplementation::Close() {
    boolean RET = false;
    if (H_Specific) {
#if defined(API_POSIX)
        if (H_Specific->FD_File != 0)
            if (close(H_Specific->FD_File) == 0)
                RET = true;
#elif defined(API_MSWINDOWS)
        if (H_Specific->H_File != 0)
            if (CloseHandle(H_Specific->H_File))
                RET = true;
#endif
        if (RET == true)
            if ((--(H_Specific->AI_Reference)) == 0) {
                delete H_Specific;
                H_Specific = 0;
            }
    }
    return RET;
}

size File::FileImplementation::Size() const {
    if (H_Specific) {
#if defined(API_POSIX)
#elif defined(API_MSWINDOWS)
#endif
    }
    return 0;
}

size File::FileImplementation::Read(void* BUF, size RD_SZ) {
    size RET = 0;
    if (BUF && H_Specific && RD_SZ != 0) {
#if defined(API_POSIX)
        RET = read(H_Specific->FD_File, BUF, RD_SZ);
#elif defined(API_MSWINDOWS)
#endif
    }
    return RET;
}

size File::FileImplementation::Write(void* BUF, size WR_SZ) {
    size RET = 0;
    if (BUF && H_Specific && WR_SZ != 0) {
#if defined(API_POSIX)
        RET = write(H_Specific->FD_File, BUF, WR_SZ);
#elif defined(API_MSWINDOWS)
#endif
    }
    return RET;
}

size File::FileImplementation::Seek(size OFFSET, SeekPosition SEEKPOS) {
    if (H_Specific && SEEKPOS != UNDEFINED_POSITION) {
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
        return lseek(H_Specific->FD_File, WHENCE, OFFSET);
#elif defined(API_MSWINDOWS)
#endif
    }
    return 0;
}

boolean File::Access(const byte* C_STR, AccessMode MODE) {
    return File::Access(String(C_STR), MODE);
}

boolean File::Access(const String&, AccessMode) {
}

File::File(Object* OBJ) : StreamBuffer(OBJ), Implementation(0) {
    Implementation = new FileImplementation();
}

//File::File(const File& REF):StreamBuffer(REF.GetMaster()), Implementation(0){}

File::~File() {
    Close();
    if (Implementation)
        delete Implementation;
}

//size File::Capacity() const{return 0;}

AccessMode File::Mode() const {
    if (Implementation)
        if (Implementation->H_Specific)
            return Implementation->H_Specific->ENUM_Mode;
    return UNDEFINED_MODE;
}

String File::Path() const {
    if (Implementation)
        if (Implementation->H_Specific)
            return Implementation->H_Specific->STR_Path;
    return String();
}

size File::Size() const {
    if (Implementation)
        return Implementation->Size();
    return 0;
}

void File::Close() {
    if (Implementation)
        Implementation->Close();
}

size File::Read(void* BUF, size RD_SZ) {
    if (Implementation && BUF)
        return Implementation->Read(BUF, RD_SZ);
    return 0;
}

size File::Write(void* BUF, size WR_SZ) {
    if (Implementation && BUF)
        return Implementation->Write(BUF, WR_SZ);
    return 0;
}

size File::Seek(size OFFSET, SeekPosition POSITION) {
    if (Implementation && POSITION != UNDEFINED_POSITION)
        return Implementation->Seek(OFFSET, POSITION);
    return 0;
}

END_SOURCECODE
