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

static const char* contract_strerror(int err);

#endif
