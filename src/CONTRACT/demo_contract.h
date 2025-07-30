#ifndef DEMO_CONTRACTS_H
#define DEMO_CONTRACTS_H

#include "contract.h"
#include "contract_tools.h"
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Demonstrates all Design-by-Contract macros grouped by semantic domain.
 *
 * This function provides a comprehensive demonstration of every contract macro
 * defined in contract.h. It triggers each macro with a failing condition to
 * produce a visible contract violation, allowing developers to verify:
 * - Error message formatting
 * - Errno code mapping
 * - Source location reporting
 * - Overall contract enforcement behavior
 *
 * The demo is organized into logical groups (e.g., Memory, Filesystem, Network)
 * with a pause after each section, allowing the user to review output before
 * continuing. This makes it ideal for debugging, onboarding, and validation
 * of the contract system in new environments (e.g., DOS with Open Watcom C).
 *
 * @note This function is intended for testing and demonstration purposes only.
 *       In production builds, it can be compiled out or omitted.
 *
 * @note Design and implementation support from an AI assistant (based on Llama 3 / OpenWatcom C best practices).
 *         No license restrictions; contribution is part of the public domain.
 *
 * @see contract.h
 * @see validate_error_strings()
 */
void demo_contracts(void) {
    printf("DESIGN-BY-CONTRACT MACROS DEMO\n");
    printf("Each group will fail and print error\n");

    #define PAUSE() do { \
        printf(">>> Press Enter to continue..."); \
        while (getchar() != '\n') { } \
        printf("\n"); \
    } while (0)

    // Dummy values
    int zero = 0;
    int one = 1;
    int ptr = 0;
    int val = 150;

    printf("1. DEFAULT CONTRACTS require, ensure, invariant\n");
    require(zero, "General pre-condition failed");
    ensure(zero, "General post-condition failed");
    invariant(zero, "Object state invariant violated");

    PAUSE();

    printf("2. MEMORY & ADDRESS CONTRACTS\n");
    require_address(ptr == 0, "Null pointer not allowed");
    require_mem(zero, "Memory allocation failed");
    ensure_address(ptr, "Function returned null pointer");
    require_aligned(zero, "Pointer not properly aligned");

    PAUSE();

    printf("3. MATHEMATICAL & RANGE CONTRACTS\n");
    require_domain(zero, "Argument outside mathematical domain (e.g., sqrt(-1))");
    require_range(zero, "Result exceeds representable range");
    ensure_in_range(val, 0, 100, "Value out of valid bounds [0..100]");
    ensure_no_overflow(32767, "Computation hit INT_MAX");
    ensure_fail(one, "Operation unexpectedly succeeded");

    PAUSE();

    printf("4. FILESYSTEM CONTRACTS\n");

    require_fd(zero, "Invalid file descriptor");
    require_exists(zero, "Required file or path does not exist");
    require_is_dir(zero, "Path is not a directory");
    require_not_dir(one, "Path must not be a directory");
    require_empty_dir(zero, "Directory is not empty");
    require_writable(zero, "Filesystem is read-only");
    require_file_size(zero, "File exceeds maximum size");
    require_name_length(zero, "Filename too long");
    require_same_device(zero, "Cross-device link not allowed");
    require_not_busy(zero, "Resource is busy or locked");
    require_fresh_handle(zero, "File handle is stale");
    require_pipe_ready(zero, "Pipe is broken");
    require_regular_file(zero, "Not a regular file");
    require_not_fifo(one, "Operation not allowed on pipe");

    PAUSE();

    printf("5. PROCESS & SYSTEM STATE CONTRACTS\n");
    require_process(zero, "Target process does not exist");
    require_no_deadlock(zero, "Deadlock condition detected");
    require_not_canceled(zero, "Operation was canceled");
    require_id_valid(zero, "Shared memory or semaphore ID invalid");

    ensure_resource_available(zero, "Resource unavailable");
    ensure_mutex_consistent(zero, "Mutex in inconsistent state");

    PAUSE();

    printf("6. NETWORK & COMMUNICATION CONTRACTS\n");
    require_network_up(zero, "Network is down");
    require_host_reachable(zero, "Host is unreachable");
    require_no_timeout(zero, "Operation timed out");
    require_not_already_connecting(one, "Connection already in progress");
    require_proto_available(zero, "Protocol not supported");

    PAUSE();

    printf("7. DATA & ENCODING CONTRACTS\n");
    require_valid_encoding(zero, "Input contains invalid byte sequence");
    ensure_valid_encoding(zero, "Output contains invalid encoding");

    PAUSE();

    printf("8. PERMISSION & ACCESS CONTRACTS\n");
    require_permission(zero, "Insufficient privileges");
    require_io_success(zero, "I/O operation failed");
    require_device(zero, "Device not found");

    PAUSE();

    printf("9. MISCELLANEOUS & CUSTOM GUARANTEES\n");
    require_supported(zero, "Feature not supported");
    require_recoverable(zero, "State is unrecoverable");
    require_owner_alive(zero, "Mutex owner died");

    PAUSE();

    printf("DEMO COMPLETE.\n");
    printf("All contract macros have been exercised.\n");
    printf("Now you can enable 'abort()' in _contract_fail to terminate on failure.\n");
}

#endif
