#ifndef CONTRACT_ERRORS_H
#define CONTRACT_ERRORS_H

/**
 * @brief POSIX error codes, grouped by historical layer of introduction.
 *
 * The `posix_error_t` enum defines standard error codes used in
 * POSIX-compliant systems. These values evolved incrementally across
 * decades of Unix development, from Version 7 (1979) through modern
 * threading and networking extensions.
 *
 * The enum is divided into chronological layers:
 * - Early Unix (V7, 1979)
 * - Structural Extensions (1980s–1990s)
 * - Networking Era (BSD, 1980s–1990s)
 * - Modern POSIX (2000s)
 *
 * Gaps in numbering reflect historical divergence and reserved ranges.
 * This layout aids understanding and supports efficient string mapping.
 */

typedef enum {
    /** Success */
    POSIX_SUCCESS = 0,               /**< No error; operation succeeded */

    /**
     * Early Unix (Version 7, 1979)
     * Core file, process, and memory errors. Standardised by POSIX.1-1988.
     */
    POSIX_EPERM = 1,                 /**< Operation not permitted */
    POSIX_ENOENT = 2,                /**< No such file or directory */
    POSIX_ESRCH = 3,                 /**< No such process */
    POSIX_EINTR = 4,                 /**< Interrupted system call */
    POSIX_EIO = 5,                   /**< Input/output error */
    POSIX_ENXIO = 6,                 /**< No such device or address */
    POSIX_E2BIG = 7,                 /**< Argument list too long */
    POSIX_ENOEXEC = 8,               /**< Executable file format error */
    POSIX_EBADF = 9,                 /**< Bad file descriptor */
    POSIX_ECHILD = 10,               /**< No child processes */
    POSIX_EAGAIN = 11,               /**< Resource unavailable, try again */
    POSIX_EWOULDBLOCK = 11,          /**< Operation would block (same as EAGAIN) */
    POSIX_ENOMEM = 12,               /**< Out of memory */
    POSIX_EACCES = 13,               /**< Permission denied */
    POSIX_EFAULT = 14,               /**< Bad address */
    POSIX_EBUSY = 16,                /**< Device or resource busy */
    POSIX_EEXIST = 17,               /**< File exists */
    POSIX_EXDEV = 18,                /**< Cross-device link */
    POSIX_ENODEV = 19,               /**< No such device */
    POSIX_ENOTDIR = 20,              /**< Not a directory */
    POSIX_EISDIR = 21,               /**< Is a directory */
    POSIX_EINVAL = 22,               /**< Invalid argument */
    POSIX_ENFILE = 23,               /**< Too many files open in system */
    POSIX_EMFILE = 24,               /**< Too many open files */
    POSIX_ENOTTY = 25,               /**< Inappropriate I/O control operation */
    POSIX_ETXTBSY = 26,              /**< Text file busy */
    POSIX_EFBIG = 27,                /**< File too large */
    POSIX_EPIPE = 32,                /**< Broken pipe */
    POSIX_EDOM = 33,                 /**< Numerical argument out of domain */
    POSIX_ERANGE = 34,               /**< Result too large */
    POSIX_EDEADLK = 35,              /**< Resource deadlock would occur */
    POSIX_ENAMETOOLONG = 36,         /**< File name too long */
    POSIX_ENOTEMPTY = 39,            /**< Directory not empty */
    POSIX_ELOOP = 40,                /**< Too many levels of symbolic links */
    POSIX_EROFS = 30,                /**< Read-only file system */
    POSIX_EMLINK = 31,               /**< Too many links */
    POSIX_EIDRM = 43,                /**< Identifier removed */

    /**
     * Structural Extensions (1980s–1990s)
     * IPC, real-time, and filesystem limits (e.g., timers, large files).
     */
    POSIX_ETIME = 62,                /**< Timer expired */
    POSIX_ENOLINK = 67,              /**< Link has been severed */
    POSIX_EPROTO = 71,               /**< Protocol error */
    POSIX_EOVERFLOW = 75,            /**< Value too large to be stored in data type */
    POSIX_ENOLCK = 77,               /**< No locks available */
    POSIX_EILSEQ = 84,               /**< Illegal byte sequence */

    /**
     * Networking Era (BSD 4.2+, 1980s–1990s)
     * Socket and network-specific errors from TCP/IP integration.
     */
    POSIX_EMSGSIZE = 90,             /**< Message too long */
    POSIX_EPROTOTYPE = 91,           /**< Protocol wrong type for socket */
    POSIX_EPROTONOSUPPORT = 93,      /**< Protocol not supported */
    POSIX_ENOTSUP = 95,              /**< Operation not supported */
    POSIX_EOPNOTSUPP = 95,           /**< Operation not supported on socket */
    POSIX_ENETDOWN = 100,            /**< Network is down */
    POSIX_ENETUNREACH = 101,         /**< Network is unreachable */
    POSIX_ETIMEDOUT = 110,           /**< Connection timed out */
    POSIX_EHOSTUNREACH = 113,        /**< No route to host */
    POSIX_EALREADY = 114,            /**< Connection already in progress */
    POSIX_EINPROGRESS = 115,         /**< Operation in progress */
    POSIX_ESTALE = 116,              /**< Stale file handle */

    /**
     * Modern POSIX (2000s, POSIX.1-2001)
     * Thread cancellation and robust mutex recovery.
     */
    POSIX_ECANCELED = 125,           /**< Operation canceled */
    POSIX_EOWNERDEAD = 130,          /**< Previous owner died */
    POSIX_ENOTRECOVERABLE = 131      /**< State not recoverable */

} posix_error_t;

// packed string array of error messages
static const char error_strings[] =
    "Success\0"                                   // 0: POSIX_SUCCESS
    "Operation not permitted\0"                   // 1: POSIX_EPERM
    "No such file or directory\0"                 // 2: POSIX_ENOENT
    "No such process\0"                           // 3: POSIX_ESRCH
    "Interrupted system call\0"                   // 4: POSIX_EINTR
    "Input/output error\0"                        // 5: POSIX_EIO
    "No such device or address\0"                 // 6: POSIX_ENXIO
    "Argument list too long\0"                    // 7: POSIX_E2BIG
    "Exec format error\0"                         // 8: POSIX_ENOEXEC
    "Bad file descriptor\0"                       // 9: POSIX_EBADF
    "No child processes\0"                        // 10: POSIX_ECHILD
    "Resource unavailable, try again\0"           // 11: POSIX_EAGAIN, POSIX_EWOULDBLOCK
    "Out of memory\0"                             // 12: POSIX_ENOMEM
    "Permission denied\0"                         // 13: POSIX_EACCES
    "Bad address\0"                               // 14: POSIX_EFAULT
    "Device or resource busy\0"                   // 16: POSIX_EBUSY
    "File exists\0"                               // 17: POSIX_EEXIST
    "Cross-device link\0"                         // 18: POSIX_EXDEV
    "No such device\0"                            // 19: POSIX_ENODEV
    "Not a directory\0"                           // 20: POSIX_ENOTDIR
    "Is a directory\0"                            // 21: POSIX_EISDIR
    "Invalid argument\0"                          // 22: POSIX_EINVAL
    "Too many files open in system\0"             // 23: POSIX_ENFILE
    "Too many open files\0"                       // 24: POSIX_EMFILE
    "Inappropriate ioctl for device\0"            // 25: POSIX_ENOTTY
    "Text file busy\0"                            // 26: POSIX_ETXTBSY
    "File too large\0"                            // 27: POSIX_EFBIG
    "Read-only file system\0"                     // 30: POSIX_EROFS
    "Too many links\0"                            // 31: POSIX_EMLINK
    "Broken pipe\0"                               // 32: POSIX_EPIPE
    "Numerical argument out of domain\0"          // 33: POSIX_EDOM
    "Result too large\0"                          // 34: POSIX_ERANGE
    "Resource deadlock would occur\0"             // 35: POSIX_EDEADLK
    "File name too long\0"                        // 36: POSIX_ENAMETOOLONG
    "Directory not empty\0"                       // 39: POSIX_ENOTEMPTY
    "Too many levels of symbolic links\0"         // 40: POSIX_ELOOP
    "Identifier removed\0"                        // 43: POSIX_EIDRM
    "Timer expired\0"                             // 62: POSIX_ETIME
    "Link has been severed\0"                     // 67: POSIX_ENOLINK
    "Protocol error\0"                            // 71: POSIX_EPROTO
    "Value too large to be stored in data type\0" // 75: POSIX_EOVERFLOW
    "No locks available\0"                        // 77: POSIX_ENOLCK
    "Illegal byte sequence\0"                     // 84: POSIX_EILSEQ
    "Message too long\0"                          // 90: POSIX_EMSGSIZE
    "Protocol wrong type for socket\0"            // 91: POSIX_EPROTOTYPE
    "Protocol not supported\0"                    // 93: POSIX_EPROTONOSUPPORT
    "Operation not supported\0"                   // 95: POSIX_ENOTSUP, POSIX_EOPNOTSUPP
    "Network is down\0"                           // 100: POSIX_ENETDOWN
    "Network is unreachable\0"                    // 101: POSIX_ENETUNREACH
    "Connection timed out\0"                      // 110: POSIX_ETIMEDOUT
    "No route to host\0"                          // 113: POSIX_EHOSTUNREACH
    "Connection already in progress\0"            // 114: POSIX_EALREADY
    "Operation in progress\0"                     // 115: POSIX_EINPROGRESS
    "Stale file handle\0"                         // 116: POSIX_ESTALE
    "Operation canceled\0"                        // 125: POSIX_ECANCELED
    "Previous owner died\0"                       // 130: POSIX_EOWNERDEAD
    "State not recoverable\0"                     // 131: POSIX_ENOTRECOVERABLE
    "\n";

    static const char* const errno_to_msg[132] = {
        [  0] = error_strings + 0,  // "Success"
        [  1] = error_strings + 8,  // "Operation not permitted"
        [  2] = error_strings + 32,  // "No such file or directory"
        [  3] = error_strings + 58,  // "No such process"
        [  4] = error_strings + 74,  // "Interrupted system call"
        [  5] = error_strings + 98,  // "Input/output error"
        [  6] = error_strings + 117,  // "No such device or address"
        [  7] = error_strings + 143,  // "Argument list too long"
        [  8] = error_strings + 166,  // "Exec format error"
        [  9] = error_strings + 184,  // "Bad file descriptor"
        [ 10] = error_strings + 204,  // "No child processes"
        [ 11] = error_strings + 223,  // "Resource unavailable, try again"
        [ 12] = error_strings + 255,  // "Out of memory"
        [ 13] = error_strings + 269,  // "Permission denied"
        [ 14] = error_strings + 287,  // "Bad address"
        [ 16] = error_strings + 299,  // "Device or resource busy"
        [ 17] = error_strings + 323,  // "File exists"
        [ 18] = error_strings + 335,  // "Cross-device link"
        [ 19] = error_strings + 353,  // "No such device"
        [ 20] = error_strings + 368,  // "Not a directory"
        [ 21] = error_strings + 384,  // "Is a directory"
        [ 22] = error_strings + 399,  // "Invalid argument"
        [ 23] = error_strings + 416,  // "Too many files open in system"
        [ 24] = error_strings + 446,  // "Too many open files"
        [ 25] = error_strings + 466,  // "Inappropriate ioctl for device"
        [ 26] = error_strings + 497,  // "Text file busy"
        [ 27] = error_strings + 512,  // "File too large"
        [ 30] = error_strings + 527,  // "Read-only file system"
        [ 31] = error_strings + 549,  // "Too many links"
        [ 32] = error_strings + 564,  // "Broken pipe"
        [ 33] = error_strings + 576,  // "Numerical argument out of domain"
        [ 34] = error_strings + 609,  // "Result too large"
        [ 35] = error_strings + 626,  // "Resource deadlock would occur"
        [ 36] = error_strings + 656,  // "File name too long"
        [ 39] = error_strings + 675,  // "Directory not empty"
        [ 40] = error_strings + 695,  // "Too many levels of symbolic links"
        [ 43] = error_strings + 729,  // "Identifier removed"
        [ 62] = error_strings + 748,  // "Timer expired"
        [ 67] = error_strings + 762,  // "Link has been severed"
        [ 71] = error_strings + 784,  // "Protocol error"
        [ 75] = error_strings + 799,  // "Value too large to be stored in data type"
        [ 77] = error_strings + 841,  // "No locks available"
        [ 84] = error_strings + 860,  // "Illegal byte sequence"
        [ 90] = error_strings + 882,  // "Message too long"
        [ 91] = error_strings + 899,  // "Protocol wrong type for socket"
        [ 93] = error_strings + 930,  // "Protocol not supported"
        [ 95] = error_strings + 953,  // "Operation not supported"
        [100] = error_strings + 977,  // "Network is down"
        [101] = error_strings + 993,  // "Network is unreachable"
        [110] = error_strings + 1016,  // "Connection timed out"
        [113] = error_strings + 1037,  // "No route to host"
        [114] = error_strings + 1054,  // "Connection already in progress"
        [115] = error_strings + 1085,  // "Operation in progress"
        [116] = error_strings + 1107,  // "Stale file handle"
        [125] = error_strings + 1125,  // "Operation canceled"
        [130] = error_strings + 1144,  // "Previous owner died"
        [131] = error_strings + 1164,  // "State not recoverable"
    };

    static const char* contract_strerror(int err) {
        return (*errno_to_msg[err] == '\0') ? "undefined" : errno_to_msg[err];
    }

#endif
