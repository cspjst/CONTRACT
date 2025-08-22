#include "contract.h" 
#include <time.h>
#include <string.h>

void _contract_fail(
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
            contract_strerror(errno),
            msg);
    abort();
}
