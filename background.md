
# The Evolution of Errors in Unix and POSIX Systems

Examines the historical development of `errno` values across Unix and POSIX-compliant systems. Rather than a designed enumeration, the `errno.h` list of defined errors has evolved incrementally over decades, reflecting changes in operating system design, hardware capabilities, and standardisation efforts.

By analysing the distribution and semantics of `errno` values, it is possible to identify distinct phases in systems evolution, each introducing new error conditions in response to emerging requirements.

## Overview of the errno Mechanism

The `errno` variable is a global (or thread-local) integer used to report error conditions from system calls and library functions. It is defined by the C standard and extended by POSIX to support a broader range of error codes.

Although `errno` values are central to error reporting they are not contiguous, and were never intended to be. Their distribution reflects the organic growth across multiple implementation lineages, including BSD, System V, and later standardised POSIX.

## Phases in the Development of errno

The defined `errno` values can be grouped into chronological layers, each corresponding to a major shift in system capabilities.

### Phase 1: Early Unix (1970s–1980s)

The earliest `errno` values originated in Version 7 Unix (1979) and were later adopted in System III and System V. These cover fundamental operations involving files, processes, and memory.

Key values in this phase:
- `EPERM` (1): Operation not permitted
- `ENOENT` (2): No such file or directory
- `ESRCH` (3): No such process
- `EINTR` (4): Interrupted system call
- `EIO` (5): Input/output error
- `ENXIO` (6): No such device or address
- `E2BIG` (7): Argument list too long
- `ENOEXEC` (8): Exec format error
- `EBADF` (9): Bad file descriptor
- `ECHILD` (10): No child processes
- `EAGAIN` (11): Resource temporarily unavailable
- `ENOMEM` (12): Cannot allocate memory
- `EACCES` (13): Permission denied
- `EFAULT` (14): Bad address
- `EBUSY` (16): Device or resource busy
- `EEXIST` (17): File exists
- `EXDEV` (18): Cross-device link
- `ENODEV` (19): No such device
- `ENOTDIR` (20): Not a directory
- `EISDIR` (21): Is a directory
- `EINVAL` (22): Invalid argument
- `ENFILE` (23): Too many open files in system
- `EMFILE` (24): Too many open files
- `ENOTTY` (25): Inappropriate ioctl for device
- `ETXTBSY` (26): Text file busy
- `EFBIG` (27): File too large
- `EROFS` (30): Read-only file system
- `EMLINK` (31): Too many links
- `EPIPE` (32): Broken pipe
- `EDOM` (33): Numerical argument out of domain
- `ERANGE` (34): Result too large
- `EDEADLK` (35): Resource deadlock avoided
- `ENAMETOOLONG` (36): File name too long

These values were present in early Unix systems and were largely standardised by the time of POSIX.1-1988.

Source: *The Unix Programmer’s Manual, Seventh Edition* (1979), and *The Design of the UNIX Operating System* by M. J. Bach (1986).

### Phase 2: Filesystem and IPC Extensions (1980s–1990s)

As Unix systems grew more complex, new subsystems such as advanced filesystems, inter-process communication (IPC), and real-time extensions introduced additional error conditions.

Key additions:
- `ENOTEMPTY` (39): Directory not empty
- `ELOOP` (40): Too many levels of symbolic links
- `EIDRM` (43): Identifier removed (System V IPC)
- `ETIME` (62): Timer expired (POSIX.1b real-time extensions)
- `EPROTO` (71): Protocol error
- `EOVERFLOW` (75): Value too large to be stored in data type (introduced for large file support)

This phase reflects the divergence between BSD and System V implementations, with some values appearing in one but not the other. POSIX later harmonised many of these.

Source: IEEE Std 1003.1b-1993 (POSIX.1b), *The Design and Implementation of the 4.4BSD Operating System* by McKusick et al.

### Phase 3: Networking Support (Late 1980s–1990s)

The integration of TCP/IP into Unix systems, particularly through 4.2BSD, introduced a new class of distributed errors. These reflect network-specific failure modes such as unreachable hosts, refused connections, and routing failures.

Key values:
- `ENETDOWN` (100): Network is down
- `ENETUNREACH` (101): Network is unreachable
- `ECONNABORTED` (103): Software caused connection abort
- `ECONNRESET` (104): Connection reset by peer
- `ENOBUFS` (105): No buffer space available
- `EISCONN` (106): Transport endpoint is already connected
- `ENOTCONN` (107): Transport endpoint is not connected
- `ESHUTDOWN` (108): Cannot send after transport endpoint shutdown
- `ETOOMANYREFS` (109): Too many references: cannot splice
- `ETIMEDOUT` (110): Connection timed out
- `ECONNREFUSED` (111): Connection refused
- `EHOSTDOWN` (112): Host is down
- `EHOSTUNREACH` (113): No route to host
- `EALREADY` (114): Operation already in progress
- `EINPROGRESS` (115): Operation now in progress
- `ESTALE` (116): Stale NFS file handle

These errors are defined in the context of socket programming and are now standard across POSIX systems.

Source: *TCP/IP Illustrated, Volume 1* by W. Richard Stevens, and RFC 1122.

### Phase 4: Modern POSIX (2000s)

The 2001 revision of POSIX (IEEE Std 1003.1-2001) introduced new errors to support thread cancellation and robust mutexes, particularly for applications requiring recovery from thread failure.

Key additions:
- `ECANCELED` (125): Operation canceled
- `EOWNERDEAD` (130): Previous owner died
- `ENOTRECOVERABLE` (131): State not recoverable

These values enable applications to detect and recover from partial failures in multithreaded environments, marking a shift from simple error reporting to state management.

Source: IEEE Std 1003.1-2001, The Open Group Base Specifications Issue 6.

## Observations on Distribution and Gaps of error number values

The `errno` space is not contiguous. Large gaps exist between defined values, such as:
- 44–61: No standard errors defined
- 63–70: Similarly sparse
- 78–83, 85–89, 96–99, 102–109 (partial), 117–124

### Missing Ranges in errno (1–131)

The following contiguous ranges are undefined in the standard errno namespace:

- **44–61** (18 values) — IPC, streams, and legacy networking (e.g., XTI, TLI)
- **78–83** (6 values)  — Unused or reserved across major implementations
- **85–89** (5 values)  — Obsolete XTI/streams codes, not adopted widely
- **96–99** (4 values)  — Partially defined address family errors (e.g., `EAFNOSUPPORT` at 97)
- **102–109** (8 values) — Sparse connection state errors (e.g., `ECONNABORTED`, `ESHUTDOWN`)
- **117–124** (8 values) — Async I/O and recovery-related codes (mostly unused)

These gaps reflect historical divergence between BSD, System V, and POSIX, as well as reserved space that was never standardised. Therefore, the non-contiguity is not a defect, but rather a consequence of incremental, consensus-driven development.

## Conclusion

The `errno` namespace is best understood as a historical artefact, shaped by decades of system development. Its structure reflects the evolution of Unix from a single-user operating system to a networked, multi-threaded platform.

Understanding this evolution aids in designing robust error-handling mechanisms without assuming contiguity or completeness.

## References

- *The Unix Programmer’s Manual, Seventh Edition* (1979)  
  https://man.cat-v.org/unix-7th/

- Bach, M. J. (1986). *The Design of the UNIX Operating System*. Prentice Hall.

- IEEE Std 1003.1-2001. *Portable Operating System Interface (POSIX)*.  
  https://pubs.opengroup.org/onlinepubs/009695399/

- Stevens, W. R. (1990). *Unix Network Programming*. Prentice Hall.

- McKusick, M. K., et al. (1996). *The Design and Implementation of the 4.4BSD Operating System*. Addison-Wesley.

- RFC 1122: *Requirements for Internet Hosts* (1989)  
  https://tools.ietf.org/html/rfc1122
