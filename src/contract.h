/**
 * @file contract.h
 * @brief Design-by-Contract macros leverages POSIX.1-2001 errno values
 * @version 0.1.3
 * @license MIT
 * @author Jeremy Thornton
 */
#ifndef CONTRACT_H
#define CONTRACT_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "posix_errno.h"

/**
 * @brief Handles contract violation by printing detailed error information and terminating the program
 *
 * This function is called when a contract condition fails. It prints a formatted error message
 * including timestamp, file location, failed condition, errno value, and descriptive message,
 * then terminates the program with abort().
 *
 * @param cond The failed condition expression as a string
 * @param msg Custom error message describing the contract violation
 * @param file Source file name where the contract violation occurred
 * @param line Line number where the contract violation occurred
 *
 * @note This function sets errno to the appropriate POSIX error code before terminating
 * @note The error output format is: [YYYY-MM-DD HH:MM:SS] filename:line|condition|errno(errno_name)|message
 */
static inline void _contract_fail(
    const char *cond,
    const char *msg,
    const char *file,
    int line
) {
    time_t now = time(NULL);
    struct tm *tm_info;
    char datetime[20]; // YYYY-MM-DD HH:MM:SS\0
    const char *filename = file;

    // Extract just the filename portion
    const char *last_slash = strrchr(file, '\\');
    if (!last_slash) last_slash = strrchr(file, '/');
    if (last_slash) filename = last_slash + 1;

    tm_info = localtime(&now);
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(stderr, "[%s] %s:%d|%s|%d(%s)|%s\n",
            datetime,
            filename,
            line,
            cond,
            errno,
            _contract_strerror(errno),
            msg);
    abort();
}

/**
 * @brief Core contract enforcement macro that evaluates a condition and handles violations
 *
 * This macro tests a boolean condition and if it evaluates to false, it sets the specified
 * errno value and calls _contract_fail() to report the violation and terminate the program.
 * The condition expression is stringified for inclusion in the error report.
 *
 * @param cond Boolean condition to evaluate - contract passes if true
 * @param msg Custom error message to display if contract is violated
 * @param err POSIX error code to set in errno when contract is violated
 */
#define _CONTRACT_ENFORCE(cond, msg, err) \
    do { \
        if (!(cond)) { \
            errno = (err); \
            _contract_fail(#cond, msg, __FILE__, __LINE__); \
        } \
    } while (0)

// Default Contract
#define require(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EINVAL)       // Caller's fault
#define ensure(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EINVAL)        // Function's fault
#define invariant(cond, msg)  _CONTRACT_ENFORCE(cond, msg, POSIX_EINVAL)    // Object's fault

// Contract specialisations ensure_*
// Memory/Validity Guards
#define ensure_address(ptr, msg) _CONTRACT_ENFORCE((ptr) != NULL, msg, POSIX_EFAULT)  /// @example ensure_address(result_ptr, "Function failed to allocate memory");
#define ensure_valid_encoding(valid_cond, msg) _CONTRACT_ENFORCE(valid_cond, msg, POSIX_EILSEQ)  /// @example ensure_valid_encoding(is_valid_utf8(result_str), "Function returned invalid UTF-8");

// Mathematical Guarantees
#define ensure_in_range(val, min, max, msg) _CONTRACT_ENFORCE((val) >= (min) && (val) <= (max), msg, POSIX_ERANGE)  /// @example ensure_in_range(returned_value, 0, 100, "Function result out of expected bounds");
#define ensure_no_overflow(val, msg) _CONTRACT_ENFORCE((val) != INT_MAX && (val) != LONG_MAX, msg, POSIX_EOVERFLOW)  /// @example ensure_no_overflow(result, "Function computation overflowed");

// State Consistency
#define ensure_resource_available(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EBUSY)  /// @example ensure_resource_available(sem_trywait(&sem) == 0, "Function failed to acquire required resource");
#define ensure_mutex_consistent(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EDEADLK)  /// @example ensure_mutex_consistent(pthread_mutex_consistent(&mutex) == 0, "Mutex state inconsistent after function call");

// Contract specialisations require_*
// Process/System Contracts
#define require_arg_list(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_E2BIG)  /// @example require_arg_list(argv_size < 4096, "Argument list exceeds system limit");
#define require_id_valid(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EIDRM)  /// @example require_id_valid(shm_id != -1, "Invalid shared memory ID");
#define require_process(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ESRCH)  /// @example require_process(kill(pid, 0) == 0, "Target process does not exist");
#define require_no_deadlock(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EDEADLK)  /// @example require_no_deadlock(!mutex_locked, "Potential deadlock detected");
#define require_not_canceled(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ECANCELED)  /// @example require_not_canceled(!thread_canceled, "Operation canceled by thread termination");

// Filesystem Contracts
#define require_fd(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EBADF)  /// @example require_fd(fd >= 0, "Invalid file descriptor");
#define require_exists(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ENOENT)  /// @example require_exists(access(path, F_OK) == 0, "File does not exist");
#define require_not_dir(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EISDIR)  /// @example require_not_dir(!S_ISDIR(st.st_mode), "Path must not be a directory");
#define require_is_dir(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ENOTDIR)  /// @example require_is_dir(S_ISDIR(st.st_mode), "Path must be a directory");
#define require_no_loops(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ELOOP)  /// @example require_no_loops(symlink_depth < 10, "Symbolic link recursion detected");
#define require_writable(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EROFS)  /// @example require_writable(access(path, W_OK) == 0, "Filesystem is read-only");
#define require_empty_dir(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ENOTEMPTY)  /// @example require_empty_dir(is_dir_empty(dir), "Directory must be empty");
#define require_regular_file(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EINVAL)  /// @example require_regular_file(S_ISREG(st.st_mode), "Must be a regular file");
#define require_not_fifo(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ENXIO)  /// @example require_not_fifo(!S_ISFIFO(st.st_mode), "Cannot operate on named pipes");
#define require_permission(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EPERM)  /// @example require_permission(geteuid() == 0, "Root privileges required");
#define require_io_success(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EIO)  /// @example require_io_success(bytes_written == expected, "Disk write failed");
#define require_device(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ENODEV)  /// @example require_device(S_ISBLK(st.st_mode), "Not a block device");
#define require_not_busy(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ETXTBSY)  /// @example require_not_busy(flock(fd, LOCK_EX|LOCK_NB) == 0, "File is locked by another process");
#define require_file_size(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EFBIG)  /// @example require_file_size(st.st_size <= MAX_SIZE, "File exceeds size limit");
#define require_name_length(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ENAMETOOLONG)  /// @example require_name_length(strlen(name) < 255, "Filename too long");
#define require_same_device(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EXDEV)  /// @example require_same_device(st1.st_dev == st2.st_dev, "Cross-device operation not allowed");
#define require_fresh_handle(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ESTALE)  /// @example require_fresh_handle(fstat(fd, &st) == 0, "File handle is stale");
#define require_pipe_ready(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EPIPE)  /// @example require_pipe_ready(write(pipefd[1], &c, 1) != -1, "Pipe broken");
#define require_valid_encoding(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EILSEQ)  /// @example require_valid_encoding(mblen(str, MB_CUR_MAX) != -1, "Invalid multibyte sequence");
#define require_supported(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ENOTSUP)  /// @example require_supported(has_feature_X(), "Feature not supported");
#define require_recoverable(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ENOTRECOVERABLE)  /// @example require_recoverable(state != CORRUPTED, "Unrecoverable state detected");
#define require_owner_alive(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EOWNERDEAD)  /// @example require_owner_alive(check_owner(lock), "Lock owner terminated");

// Memory/Address Contracts
#define require_address(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EFAULT)  /// @example require_address(ptr != NULL, "Null pointer dereference");
#define require_mem(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ENOMEM)  /// @example require_mem(ptr = malloc(size), "Memory allocation failed");
#define require_aligned(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EINVAL)  /// @example require_aligned((uintptr_t)ptr % 8 == 0, "Pointer not 8-byte aligned");

// Math/Domain Contracts
#define require_domain(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EDOM)  /// @example require_domain(x >= 0, "Square root of negative number");
#define require_range(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ERANGE)  /// @example require_range(result <= INT_MAX, "Integer overflow detected");


// Network Contracts
#define require_not_already_connecting(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EALREADY)  /// @example require_not_already_connecting(!connecting, "Already connecting to host");
#define require_host_reachable(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EHOSTUNREACH)  /// @example require_host_reachable(ping(host) == 0, "Host unreachable");
#define require_network_up(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ENETDOWN)  /// @example require_network_up(is_interface_up("eth0"), "Network interface down");
#define require_no_timeout(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ETIMEDOUT)  /// @example require_no_timeout(select(fd+1, &readfds, NULL, NULL, &tv) > 0, "Connection timeout");
#define require_proto_available(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EPROTONOSUPPORT)  /// @example require_proto_available(socket(AF_INET, SOCK_RAW, proto) != -1, "Protocol not supported");

// Streams Contracts (Obscure POSIX)
#define require_stream_alive(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_ENODEV)  /// @example require_stream_alive(isatty(fileno(stdin)), "Standard input not a terminal");

#endif
