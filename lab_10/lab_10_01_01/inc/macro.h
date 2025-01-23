#ifndef __MACRO_H__
#define __MACRO_H__

#include <stdio.h>
#include <string.h>

#ifdef LOCAL_BUILD

#define __SHORT_FILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define NEWLINE "\n"

#define DBG_LINE "DEBUG"

#define FILE_MESSAGE "FILE"
#define LINE_MESSAGE "LINE"
#define FUNC_MESSAGE "FUNC"
#define MESSAGE "MESSAGE"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

#define LOGS __SHORT_FILE__, __func__, __LINE__

#define MESSAGE_LOGS FILE_MESSAGE, FUNC_MESSAGE, LINE_MESSAGE, MESSAGE

#define LOGS_FMT "| %-20s | %-20s | %-10d | "

#define LOG_PRINT_OK(message, ...) \
    fprintf(stderr, GREEN LOGS_FMT message RESET NEWLINE, LOGS, ##__VA_ARGS__)

#define LOG_PRINT_ERR(message, ...) \
    fprintf(stderr, RED LOGS_FMT message RESET NEWLINE, LOGS, ##__VA_ARGS__)

#define LOG_PRINT_DEFAULT(message, ...) \
    fprintf(stderr,LOGS_FMT message NEWLINE, LOGS, ##__VA_ARGS__)

#define DEFAULT_PRINT(message, ...) \
    fprintf(stdout,message NEWLINE, ##__VA_ARGS__)

#define PRINT_ROAD(CNT) \
    do { \
        for (size_t i = 0; i < (CNT); i++) putchar('-'); \
        putchar('\n'); \
    } while (0)

#define PRINT_TABLE_HEADER() \
    do { \
        PRINT_ROAD(98); \
        printf("| %-20s | %-20s | %-10s | %-35s |\n", MESSAGE_LOGS); \
        PRINT_ROAD(98); \
    } while (0)

#define PRINT_END_TABLE() \
    PRINT_ROAD(98)

#else
#define LOG_PRINT_OK(message, ...) ((void)0)
#define LOG_PRINT_ERR(message, ...) ((void)0)
#define LOG_PRINT_DEFAULT(message, ...) ((void)0)
#define DEFAULT_PRINT(message, ...) ((void)0)
#define PRINT_TABLE_HEADER() ((void)0)
#define PRINT_END_TABLE() ((void)0)
#endif

#endif // __MACRO_H__
