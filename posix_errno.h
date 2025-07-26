#ifndef POSIX_ERRNO_H
#define POSIX_ERRNO_H

typedef enum {
    POSIX_E2BIG = 7,                 // Argument list too long (0x07)
    POSIX_EACCES = 13,               // Permission denied (0x0D)
    POSIX_EAGAIN = 11,               // Resource unavailable, try again (0x0B)
    POSIX_EALREADY = 114,            // Connection already in progress (0x72)
    POSIX_EBADF = 9,                 // Bad file descriptor (0x09)
    POSIX_EBUSY = 16,                // Device or resource busy (0x10)
    POSIX_ECANCELED = 125,           // Operation canceled (0x7D)
    POSIX_ECHILD = 10,               // No child processes (0x0A)
    POSIX_EDEADLK = 35,              // Resource deadlock would occur (0x23)
    POSIX_EDOM = 33,                 // Numerical argument out of domain (0x21)
    POSIX_EEXIST = 17,               // File exists (0x11)
    POSIX_EFAULT = 14,               // Bad address (0x0E)
    POSIX_EFBIG = 27,                // File too large (0x1B)
    POSIX_EHOSTUNREACH = 113,        // No route to host (0x71)
    POSIX_EIDRM = 43,                // Identifier removed (0x2B)
    POSIX_EILSEQ = 84,               // Illegal byte sequence (0x54)
    POSIX_EINPROGRESS = 115,         // Operation in progress (0x73)
    POSIX_EINTR = 4,                 // Interrupted system call (0x04)
    POSIX_EINVAL = 22,               // Invalid argument (0x16)
    POSIX_EIO = 5,                   // Input/output error (0x05)
    POSIX_EISDIR = 21,               // Is a directory (0x15)
    POSIX_ELOOP = 40,                // Too many levels of symbolic links (0x28)
    POSIX_EMFILE = 24,               // Too many open files (0x18)
    POSIX_EMLINK = 31,               // Too many links (0x1F)
    POSIX_EMSGSIZE = 90,             // Message too long (0x5A)
    POSIX_ENAMETOOLONG = 36,         // File name too long (0x24)
    POSIX_ENETDOWN = 100,            // Network is down (0x64)
    POSIX_ENETUNREACH = 101,         // Network is unreachable (0x65)
    POSIX_ENFILE = 23,               // Too many files open in system (0x17)
    POSIX_ENODEV = 19,               // No such device (0x13)
    POSIX_ENOENT = 2,                // No such file or directory (0x02)
    POSIX_ENOEXEC = 8,               // POSIX_Executable file format error (0x08)
    POSIX_ENOLCK = 77,               // No locks available (0x4D)
    POSIX_ENOLINK = 67,              // Link has been severed (0x43)
    POSIX_ENOMEM = 12,               // Out of memory (0x0C)
    POSIX_ENOTDIR = 20,              // Not a directory (0x14)
    POSIX_ENOTEMPTY = 39,            // Directory not empty (0x27)
    POSIX_ENOTRECOVERABLE = 131,     // State not recoverable (0x83)
    POSIX_ENOTSUP = 95,              // Operation not supported (0x5F)
    POSIX_ENOTTY = 25,               // Inappropriate I/O control operation (0x19)
    POSIX_ENXIO = 6,                 // No such device or address (0x06)
    POSIX_EOPNOTSUPP = 95,           // Operation not supported on socket (0x5F)
    POSIX_EOVERFLOW = 75,            // Value too large to be stored in data type (0x4B)
    POSIX_EOWNERDEAD = 130,          // Previous owner died (0x82)
    POSIX_EPERM = 1,                 // Operation not permitted (0x01)
    POSIX_EPIPE = 32,                // Broken pipe (0x20)
    POSIX_EPROTO = 71,               // Protocol error (0x47)
    POSIX_EPROTONOSUPPORT = 93,      // Protocol not supported (0x5D)
    POSIX_EPROTOTYPE = 91,           // Protocol wrong type for socket (0x5B)
    POSIX_ERANGE = 34,               // Result too large (0x22)
    POSIX_EROFS = 30,                // Read-only file system (0x1E)
    POSIX_ESRCH = 3,                 // No such process (0x03)
    POSIX_ESTALE = 116,              // Stale file handle (0x74)
    POSIX_ETIME = 62,                // Timer expired (0x3E)
    POSIX_ETIMEDOUT = 110,           // Connection timed out (0x6E)
    POSIX_ETXTBSY = 26,              // Text file busy (0x1A)
    POSIX_EWOULDBLOCK = 11,          // Operation would block (0x0B)
    POSIX_EXDEV = 18                 // Cross-device link (0x12)
} posix_error_t;


static const char* posix_error_messages[] = {
    "Argument list too long",          // POSIX_E2BIG
    "Permission denied",                // POSIX_EACCES
    "Resource unavailable, try again",  // POSIX_EAGAIN
    "Connection already in progress",   // POSIX_EALREADY
    "Bad file descriptor",               // POSIX_EBADF
    "Device or resource busy",           // POSIX_EBUSY
    "Operation canceled",                // POSIX_ECANCELED
    "No child processes",                // POSIX_ECHILD
    "Resource deadlock would occur",     // POSIX_EDEADLK
    "Numerical argument out of domain",  // POSIX_EDOM
    "File exists",                       // POSIX_EEXIST
    "Bad address",                       // POSIX_EFAULT
    "File too large",                   // POSIX_EFBIG
    "No route to host",                 // POSIX_EHOSTUNREACH
    "Identifier removed",                // POSIX_EIDRM
    "Illegal byte sequence",             // POSIX_EILSEQ
    "Operation in progress",             // POSIX_EINPROGRESS
    "Interrupted system call",           // POSIX_EINTR
    "Invalid argument",                  // POSIX_EINVAL
    "Input/output error",                // POSIX_EIO
    "Is a directory",                    // POSIX_EISDIR
    "Too many levels of symbolic links", // POSIX_ELOOP
    "Too many open files",               // POSIX_EMFILE
    "Too many links",                    // POSIX_EMLINK
    "Message too long",                  // POSIX_EMSGSIZE
    "File name too long",                // POSIX_ENAMETOOLONG
    "Network is down",                   // POSIX_ENETDOWN
    "Network is unreachable",            // POSIX_ENETUNREACH
    "Too many files open in system",     // POSIX_ENFILE
    "No such device",                    // POSIX_ENODEV
    "No such file or directory",         // POSIX_ENOENT
    "Executable file format error",      // POSIX_ENOEXEC
    "No locks available",                 // POSIX_ENOLCK
    "Link has been severed",             // POSIX_ENOLINK
    "Out of memory",                     // POSIX_ENOMEM
    "Not a directory",                   // POSIX_ENOTDIR
    "Directory not empty",               // POSIX_ENOTEMPTY
    "State not recoverable",             // POSIX_ENOTRECOVERABLE
    "Operation not supported",           // POSIX_ENOTSUP
    "Inappropriate I/O control operation", // POSIX_ENOTTY
    "No such device or address",        // POSIX_ENXIO
    "Operation not supported on socket", // POSIX_EOPNOTSUPP
    "Value too large to be stored in data type", // POSIX_EOVERFLOW
    "Previous owner died",               // POSIX_EOWNERDEAD
    "Operation not permitted",            // POSIX_EPERM
    "Broken pipe",                        // POSIX_EPIPE
    "Protocol error",                     // POSIX_EPROTO
    "Protocol not supported",             // POSIX_EPROTONOSUPPORT
    "Protocol wrong type for socket",     // POSIX_EPROTOTYPE
    "Result too large",                  // POSIX_ERANGE
    "Read-only file system",             // POSIX_EROFS
    "No such process",                   // POSIX_ESRCH
    "Stale file handle",                 // POSIX_ESTALE
    "Timer expired",                     // POSIX_ETIME
    "Connection timed out",              // POSIX_ETIMEDOUT
    "Text file busy",                    // POSIX_ETXTBSY
    "Operation would block",             // POSIX_EWOULDBLOCK
    "Cross-device link"                  // POSIX_EXDEV
};

static const char* _contract_strerror(int err) {
    switch (err) {
        case POSIX_E2BIG: return "Argument list too long";
        case POSIX_EACCES: return "Permission denied";
        case POSIX_EAGAIN: return "Resource unavailable, try again";
        case POSIX_EALREADY: return "Connection already in progress";
        case POSIX_EBADF: return "Bad file descriptor";
        case POSIX_EBUSY: return "Device or resource busy";
        case POSIX_ECANCELED: return "Operation canceled";
        case POSIX_ECHILD: return "No child processes";
        case POSIX_EDEADLK: return "Resource deadlock would occur";
        case POSIX_EDOM: return "Numerical argument out of domain";
        case POSIX_EEXIST: return "File exists";
        case POSIX_EFAULT: return "Bad address";
        case POSIX_EFBIG: return "File too large";
        case POSIX_EHOSTUNREACH: return "No route to host";
        case POSIX_EIDRM: return "Identifier removed";
        case POSIX_EILSEQ: return "Illegal byte sequence";
        case POSIX_EINPROGRESS: return "Operation in progress";
        case POSIX_EINTR: return "Interrupted system call";
        case POSIX_EINVAL: return "Invalid argument";
        case POSIX_EIO: return "Input/output error";
        case POSIX_EISDIR: return "Is a directory";
        case POSIX_ELOOP: return "Too many levels of symbolic links";
        case POSIX_EMFILE: return "Too many open files";
        case POSIX_EMLINK: return "Too many links";
        case POSIX_EMSGSIZE: return "Message too long";
        case POSIX_ENAMETOOLONG: return "Filename too long";
        case POSIX_ENETDOWN: return "Network is down";
        case POSIX_ENETUNREACH: return "Network is unreachable";
        case POSIX_ENFILE: return "Too many files open in system";
        case POSIX_ENODEV: return "No such device";
        case POSIX_ENOENT: return "No such file or directory";
        case POSIX_ENOEXEC: return "Executable file format error";
        case POSIX_ENOLCK: return "No locks available";
        case POSIX_ENOLINK: return "Link has been severed";
        case POSIX_ENOMEM: return "Out of memory";
        case POSIX_ENOTDIR: return "Not a directory";
        case POSIX_ENOTEMPTY: return "Directory not empty";
        case POSIX_ENOTRECOVERABLE: return "State not recoverable";
        case POSIX_ENOTSUP: return "Operation not supported";
        case POSIX_ENOTTY: return "Inappropriate I/O control operation";
        case POSIX_ENXIO: return "No such device or address";
        //case POSIX_EOPNOTSUPP: return "Operation not supported on socket";
        case POSIX_EOVERFLOW: return "Value too large for data type";
        case POSIX_EOWNERDEAD: return "Previous owner died";
        case POSIX_EPERM: return "Operation not permitted";
        case POSIX_EPIPE: return "Broken pipe";
        case POSIX_EPROTO: return "Protocol error";
        case POSIX_EPROTONOSUPPORT: return "Protocol not supported";
        case POSIX_EPROTOTYPE: return "Protocol wrong type for socket";
        case POSIX_ERANGE: return "Result too large";
        case POSIX_EROFS: return "Read-only file system";
        case POSIX_ESRCH: return "No such process";
        case POSIX_ESTALE: return "Stale file handle";
        case POSIX_ETIME: return "Timer expired";
        case POSIX_ETIMEDOUT: return "Connection timed out";
        case POSIX_ETXTBSY: return "Text file busy";
        //case POSIX_EWOULDBLOCK: return "Operation would block";
        case POSIX_EXDEV: return "Cross-device link";
        default: return "Undefined error number";
    }
}

#endif
