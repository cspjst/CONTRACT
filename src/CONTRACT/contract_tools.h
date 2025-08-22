#ifndef CONTRACT_TOOLS_H
#define CONTRACT_TOOLS_H

#include "contract_errors.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Validates and generates a correct errno-to-message mapping by analyzing the packed error string blob.
 *
 * This function walks through the `error_strings` constant character array, which contains
 * null-terminated error messages in the same order as their corresponding POSIX error codes.
 * It prints a fully initialized, correct version of the `errno_to_msg` lookup table,
 * ensuring that each errno value points to the correct message start offset.
 *
 * The output is intended to be copied back into the source to eliminate manual offset errors
 * and guarantee consistency between the string blob and the pointer array.
 *
 * Example output:
 *     [ 22] = error_strings + 401,  // "Invalid argument"
 *
 * @note This function assumes that the order of strings in `error_strings[]` matches
 *       the expected sequence of errno values defined in `posix_error_t`.
 *
 * @note Design and implementation support from an AI assistant (based on Llama 3).
 *         No license restrictions; contribution is part of the public domain.
 */
void validate_error_strings(void);

#endif
